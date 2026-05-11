// Copyright 2020-2026 Ternaris
// SPDX-License-Identifier: Apache-2.0

#include <cstdlib>
#include <iostream>
#include <string>

#include <rosbags/rosbags.hpp>

auto main(int argc, char** argv) -> int {
  if (argc < 2) {
    std::cerr << "usage: read_raw <bag path> [python source path]\n";
    return 2;
  }

  rosbags::RuntimeOptions runtime_options;
  if (argc >= 3) {
    runtime_options.python_paths.push_back(argv[2]);
  } else if (const char* path = std::getenv("ROSBAGS_PYTHONPATH")) {
    runtime_options.python_paths.emplace_back(path);
  }

  try {
    rosbags::Runtime runtime(runtime_options);
    rosbags::Reader reader(runtime, {argv[1]});
    reader.open();

    std::cout << "messages=" << reader.message_count() << "\n";
    for (const auto& connection : reader.connections()) {
      std::cout << connection.id() << " " << connection.topic() << " "
                << connection.msgtype() << " count=" << connection.msgcount() << "\n";
    }

    rosbags::MessageStream stream = reader.messages();
    rosbags::Message message;
    while (stream.next(message)) {
      std::cout << message.timestamp << " " << message.connection.topic() << " "
                << message.data.size() << " bytes\n";
    }

    reader.close();
  } catch (const rosbags::Error& err) {
    std::cerr << "rosbags error: " << err.what() << "\n";
    return 1;
  }

  return 0;
}
