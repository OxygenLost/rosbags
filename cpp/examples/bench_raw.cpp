// Copyright 2020-2026 Ternaris
// SPDX-License-Identifier: Apache-2.0

#include <chrono>
#include <cstdint>
#include <iostream>
#include <set>
#include <string>

#include <rosbags/rosbags.hpp>

auto main(int argc, char** argv) -> int {
  if (argc < 2) {
    std::cerr << "usage: bench_raw <bag path> [typed topic...]\n";
    return 2;
  }

  std::set<std::string> typed_topics;
  for (int idx = 2; idx < argc; ++idx) {
    typed_topics.emplace(argv[idx]);
  }

  try {
    const auto start = std::chrono::steady_clock::now();
    rosbags::Reader reader({argv[1]});
    reader.open();
    const auto opened = std::chrono::steady_clock::now();

    std::int64_t messages = 0;
    std::uint64_t payload_bytes = 0;
    std::int64_t typed_messages = 0;

    rosbags::MessageStream stream = reader.messages();
    rosbags::Message message;
    while (stream.next(message)) {
      ++messages;
      payload_bytes += message.data.size();
      if (typed_topics.count(message.connection.topic()) != 0) {
        (void)reader.deserialize(message);
        ++typed_messages;
      }
    }
    reader.close();

    const auto stop = std::chrono::steady_clock::now();
    const auto open_elapsed = std::chrono::duration<double>(opened - start).count();
    const auto iterate_elapsed = std::chrono::duration<double>(stop - opened).count();
    const auto elapsed = std::chrono::duration<double>(stop - start).count();
    std::cout << "messages=" << messages << "\n";
    std::cout << "payload_bytes=" << payload_bytes << "\n";
    std::cout << "typed_messages=" << typed_messages << "\n";
    std::cout << "open_seconds=" << open_elapsed << "\n";
    std::cout << "iterate_seconds=" << iterate_elapsed << "\n";
    std::cout << "elapsed_seconds=" << elapsed << "\n";
  } catch (const rosbags::Error& err) {
    std::cerr << "rosbags error: " << err.what() << "\n";
    return 1;
  }

  return 0;
}
