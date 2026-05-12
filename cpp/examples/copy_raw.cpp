// Copyright 2020-2026 Ternaris
// SPDX-License-Identifier: Apache-2.0

#include <iostream>
#include <map>
#include <string>

#include <rosbags/rosbags.hpp>

auto main(int argc, char** argv) -> int {
  if (argc < 3) {
    std::cerr << "usage: copy_raw <src bag> <dst bag>\n";
    return 2;
  }

  try {
    rosbags::Reader reader({argv[1]});
    reader.open();

    rosbags::WriterOptions writer_options;
    writer_options.format = reader.bag_format();
    rosbags::Writer writer(argv[2], writer_options);
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
