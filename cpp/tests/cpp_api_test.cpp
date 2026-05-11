// Copyright 2020-2026 Ternaris
// SPDX-License-Identifier: Apache-2.0

#include <cstdint>
#include <filesystem>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include <rosbags/rosbags.hpp>

namespace fs = std::filesystem;

namespace {

constexpr const char* kMsgtype = "std_msgs/msg/Int8";
constexpr const char* kMsgdef = "int8 data\n";
constexpr const char* kMd5 = "27ffa0c9c4b8fb8492252bcad9e5c57b";
constexpr const char* kRihs =
    "RIHS01_26525065a403d972cb672f0777e333f0c799ad444ae5fcd79e43d1e73bd0f440";

void require(bool condition, const std::string& message) {
  if (!condition) {
    throw std::runtime_error(message);
  }
}

auto int8_spec(rosbags::BagFormat format) -> rosbags::ConnectionSpec {
  rosbags::ConnectionSpec spec;
  spec.topic = "/test";
  spec.msgtype = kMsgtype;
  spec.msgdef_format = rosbags::MessageDefinitionFormat::Msg;
  spec.msgdef_data = kMsgdef;
  spec.digest = format == rosbags::BagFormat::Rosbag1 ? kMd5 : kRihs;
  return spec;
}

auto read_all(rosbags::Reader& reader) -> std::vector<rosbags::Message> {
  std::vector<rosbags::Message> messages;
  rosbags::MessageStream stream = reader.messages();
  rosbags::Message message;
  while (stream.next(message)) {
    messages.push_back(message);
  }
  return messages;
}

void check_read_filters(rosbags::Reader& reader, int connection_id) {
  rosbags::ReaderMessageOptions options;
  options.connection_ids = {connection_id};
  options.start_time = 10;
  options.stop_time = 20;

  rosbags::MessageStream stream = reader.messages(options);
  rosbags::Message message;
  require(stream.next(message), "filtered stream should contain one message");
  require(message.timestamp == 10, "filtered stream timestamp mismatch");
  require(!stream.next(message), "filtered stream should be exhausted");
}

void test_write_read(
    rosbags::Runtime& runtime,
    const fs::path& path,
    rosbags::WriterOptions options,
    std::vector<std::uint8_t> first,
    std::vector<std::uint8_t> second) {
  rosbags::Writer writer(runtime, path.string(), options);
  writer.open();
  rosbags::Connection connection = writer.add_connection(int8_spec(options.format));
  writer.write(connection, 10, first);
  writer.write(connection, 30, second);
  writer.close();

  rosbags::Reader reader(runtime, {path.string()});
  reader.open();
  require(reader.bag_format() == options.format, "reader format mismatch");
  require(reader.message_count() == 2, "message count mismatch");
  const auto connections = reader.connections();
  require(connections.size() == 1, "connection count mismatch");
  require(connections.front().topic() == "/test", "topic mismatch");
  require(connections.front().msgtype() == kMsgtype, "msgtype mismatch");

  const auto messages = read_all(reader);
  require(messages.size() == 2, "read message count mismatch");
  require(messages[0].timestamp == 10, "first timestamp mismatch");
  require(messages[0].data == first, "first payload mismatch");
  require(messages[1].timestamp == 30, "second timestamp mismatch");
  require(messages[1].data == second, "second payload mismatch");
  check_read_filters(reader, connections.front().id());
  reader.close();
}

void test_copy_roundtrip(rosbags::Runtime& runtime, const fs::path& src, const fs::path& dst) {
  rosbags::Reader reader(runtime, {src.string()});
  reader.open();

  rosbags::WriterOptions options;
  options.format = reader.bag_format();
  rosbags::Writer writer(runtime, dst.string(), options);
  writer.open();

  std::map<int, rosbags::Connection> connection_map;
  for (const auto& connection : reader.connections()) {
    connection_map.emplace(connection.id(), writer.add_connection(connection));
  }

  rosbags::MessageStream stream = reader.messages();
  rosbags::Message message;
  while (stream.next(message)) {
    writer.write(connection_map.at(message.connection.id()), message.timestamp, message.data);
  }
  writer.close();
  reader.close();

  rosbags::Reader copied(runtime, {dst.string()});
  copied.open();
  const auto messages = read_all(copied);
  require(messages.size() == 2, "copied message count mismatch");
  require(
      messages[0].data == std::vector<std::uint8_t>({0, 1, 0, 0, 1}),
      "copied payload mismatch");
  copied.close();
}

void test_error_path(rosbags::Runtime& runtime, const fs::path& dst) {
  rosbags::WriterOptions options;
  options.format = rosbags::BagFormat::Rosbag2;
  rosbags::Writer writer(runtime, dst.string(), options);
  writer.open();

  rosbags::ConnectionSpec spec;
  spec.topic = "/bad";
  spec.msgtype = kMsgtype;
  spec.msgdef_data = kMsgdef;

  bool raised = false;
  try {
    (void)writer.add_connection(spec);
  } catch (const rosbags::Error&) {
    raised = true;
  }
  writer.close();
  require(raised, "missing digest should raise rosbags::Error");
}

}  // namespace

auto main(int argc, char** argv) -> int {
  try {
    require(argc == 3, "usage: cpp_api_test <python source path> <tmp dir>");
    require(std::string(argv[1]).size() > 0, "python source path must not be empty");

    fs::path tmp = argv[2];
    fs::remove_all(tmp);
    fs::create_directories(tmp);

    rosbags::RuntimeOptions runtime_options;
    runtime_options.python_paths.emplace_back(argv[1]);
    rosbags::Runtime runtime(runtime_options);

    rosbags::WriterOptions rosbag1_options;
    rosbag1_options.format = rosbags::BagFormat::Rosbag1;
    test_write_read(runtime, tmp / "raw1.bag", rosbag1_options, {1}, {2});

    rosbags::WriterOptions sqlite_options;
    sqlite_options.format = rosbags::BagFormat::Rosbag2;
    sqlite_options.storage = rosbags::StoragePlugin::Sqlite3;
    test_write_read(runtime, tmp / "raw2_sqlite", sqlite_options, {0, 1, 0, 0, 1}, {0, 1, 0, 0, 2});

    rosbags::WriterOptions mcap_options;
    mcap_options.format = rosbags::BagFormat::Rosbag2;
    mcap_options.storage = rosbags::StoragePlugin::Mcap;
    test_write_read(runtime, tmp / "raw2_mcap", mcap_options, {0, 1, 0, 0, 1}, {0, 1, 0, 0, 2});

    test_copy_roundtrip(runtime, tmp / "raw2_sqlite", tmp / "raw2_copy");
    test_error_path(runtime, tmp / "bad_manual");
  } catch (const std::exception& err) {
    std::cerr << err.what() << "\n";
    return 1;
  }

  return 0;
}
