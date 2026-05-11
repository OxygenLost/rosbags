// Copyright 2020-2026 Ternaris
// SPDX-License-Identifier: Apache-2.0

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include <rosbags/rosbags.hpp>

auto main(int argc, char** argv) -> int {
  if (argc < 3) {
    std::cerr << "usage: copy_raw <src bag> <dst bag> [python source path]\n";
    return 2;
  }

  rosbags::RuntimeOptions runtime_options;
  if (argc >= 4) {
    runtime_options.python_paths.push_back(argv[3]);
  } else if (const char* path = std::getenv("ROSBAGS_PYTHONPATH")) {
    runtime_options.python_paths.emplace_back(path);
  }

  try {
    rosbags::Runtime runtime(runtime_options);
    rosbags::Reader reader(runtime, {argv[1]});
    reader.open();

    rosbags::WriterOptions writer_options;
    writer_options.format = reader.bag_format();
    rosbags::Writer writer(runtime, argv[2], writer_options);
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
  } catch (const rosbags::Error& err) {
    std::cerr << "rosbags error: " << err.what() << "\n";
    return 1;
  }

  return 0;
}
