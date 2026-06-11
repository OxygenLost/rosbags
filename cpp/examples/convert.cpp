// Copyright 2020-2026 Ternaris
// SPDX-License-Identifier: Apache-2.0

#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include <rosbags/rosbags.hpp>

namespace fs = std::filesystem;

namespace {

auto read_text(const fs::path& path) -> std::string {
  std::ifstream stream(path);
  if (!stream) {
    throw rosbags::Error("Could not open message definition '" + path.string() + "'");
  }
  std::ostringstream out;
  out << stream.rdbuf();
  return out.str();
}

auto parse_limit(const char* value) -> std::int64_t {
  char* end = nullptr;
  const auto result = std::strtoll(value, &end, 10);
  return end != value && *end == '\0' ? result : -1;
}

void register_extra_msg(rosbags::Typestore& store, const std::string& spec) {
  const auto pos = spec.find('=');
  if (pos == std::string::npos || pos == 0 || pos + 1 >= spec.size()) {
    throw rosbags::Error("Custom type arguments must use msgtype=path.msg");
  }
  store.register_msg(spec.substr(0, pos), read_text(spec.substr(pos + 1)));
}

}  // namespace

auto main(int argc, char** argv) -> int {
  if (argc < 3) {
    std::cerr << "usage: convert <src rosbag1.bag> <dst rosbag2 dir> [limit] [msgtype=path.msg ...]\n";
    return 2;
  }

  try {
    const std::string src = argv[1];
    const std::string dst = argv[2];
    std::int64_t limit = 0;
    int extra_start = 3;
    if (argc > 3) {
      const auto parsed_limit = parse_limit(argv[3]);
      if (parsed_limit >= 0) {
        limit = parsed_limit;
        extra_start = 4;
      }
    }

    rosbags::Typestore dst_store(rosbags::TypestorePreset::Ros2Humble);
    for (int idx = extra_start; idx < argc; ++idx) {
      register_extra_msg(dst_store, argv[idx]);
    }

    const auto start = std::chrono::steady_clock::now();
    rosbags::ReaderOptions reader_options;
    reader_options.default_typestore = rosbags::TypestorePreset::Ros1Noetic;
    rosbags::Reader reader({src}, reader_options);
    reader.open();
    if (reader.bag_format() != rosbags::BagFormat::Rosbag1) {
      throw rosbags::Error("Only ROS1 to ROS2 conversion is supported by this example");
    }
    auto src_store = reader.typestore();

    rosbags::WriterOptions writer_options;
    writer_options.format = rosbags::BagFormat::Rosbag2;
    writer_options.storage = rosbags::StoragePlugin::Sqlite3;
    rosbags::Writer writer(dst, writer_options);
    writer.open();

    std::map<int, rosbags::Connection> connection_map;
    for (const auto& connection : reader.connections()) {
      connection_map.emplace(
          connection.id(),
          writer.add_connection(connection.topic(), connection.msgtype(), dst_store));
    }
    const auto opened = std::chrono::steady_clock::now();

    std::int64_t messages = 0;
    std::uint64_t input_bytes = 0;
    std::uint64_t output_bytes = 0;
    rosbags::MessageStream stream = reader.messages();
    rosbags::Message message;
    while (stream.next(message)) {
      auto converted = dst_store.convert_raw(
          message.data,
          message.connection.msgtype(),
          src_store,
          rosbags::BagFormat::Rosbag1,
          message.connection.msgtype(),
          rosbags::BagFormat::Rosbag2);
      input_bytes += message.data.size();
      output_bytes += converted.size();
      writer.write(connection_map.at(message.connection.id()), message.timestamp, converted);
      ++messages;
      if (limit > 0 && messages >= limit) {
        break;
      }
    }

    writer.close();
    reader.close();
    const auto stop = std::chrono::steady_clock::now();

    std::cout << "messages=" << messages << "\n";
    std::cout << "input_bytes=" << input_bytes << "\n";
    std::cout << "output_bytes=" << output_bytes << "\n";
    std::cout << "setup_seconds=" << std::chrono::duration<double>(opened - start).count() << "\n";
    std::cout << "convert_seconds=" << std::chrono::duration<double>(stop - opened).count() << "\n";
    std::cout << "elapsed_seconds=" << std::chrono::duration<double>(stop - start).count() << "\n";
  } catch (const rosbags::Error& err) {
    std::cerr << "rosbags error: " << err.what() << "\n";
    return 1;
  } catch (const std::exception& err) {
    std::cerr << "error: " << err.what() << "\n";
    return 1;
  }

  return 0;
}
