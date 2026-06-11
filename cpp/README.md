<!--
Copyright 2020-2026 Ternaris
SPDX-License-Identifier: Apache-2.0
-->

# rosbags C++ API

This directory contains a native C++17 API for reading and writing rosbag
messages from C++ projects. It does not embed Python, include Python headers, or
link against the Python runtime.

The API exposes raw serialized bytes for high-throughput workflows and a dynamic
typed message layer for schema-aware serialization and deserialization.

## Dependencies

The C++ library requires:

- CMake 3.18 or newer
- A C++17 compiler
- `pkg-config`
- `SQLite3`
- `yaml-cpp`
- `OpenSSL::Crypto`
- `BZip2`
- `lz4`
- `zstd`

On macOS with Homebrew:

```sh
brew install cmake pkg-config yaml-cpp openssl@3 lz4 zstd
```

`sqlite3` and `bzip2` are usually available from the macOS SDK. Install
`sqlite` or `bzip2` separately if your toolchain does not provide them.

## Build

```sh
cmake -S cpp -B build/cpp -DCMAKE_BUILD_TYPE=Release
cmake --build build/cpp
cmake --install build/cpp
```

Build examples and tests:

```sh
cmake -S cpp -B build/cpp \
  -DCMAKE_BUILD_TYPE=Release \
  -DROSBAGS_CPP_BUILD_EXAMPLES=ON \
  -DROSBAGS_CPP_BUILD_TESTS=ON
cmake --build build/cpp
ctest --test-dir build/cpp --output-on-failure
```

## Core Types

- `rosbags::Reader`: opens rosbag1 files, rosbag2 directories, `.db3`, and
  `.mcap` files.
- `rosbags::Writer`: writes rosbag1 files and rosbag2 sqlite3 or MCAP
  directories.
- `rosbags::Typestore`: owns message schemas and serializes/deserializes typed
  messages.
- `rosbags::Connection`: immutable connection/topic metadata returned by
  readers and writers.
- `rosbags::Message`: one raw message with a connection, timestamp, and bytes.
- `rosbags::TypedMessage` / `rosbags::TypedValue`: dynamic typed message values.

No `Runtime` object is needed.

## Reading Raw Messages

```cpp
#include <iostream>
#include <rosbags/rosbags.hpp>

int main() {
  rosbags::Reader reader({"/data/input.bag"});
  reader.open();

  std::cout << "messages=" << reader.message_count() << "\n";
  for (const auto& connection : reader.connections()) {
    std::cout << connection.id() << " "
              << connection.topic() << " "
              << connection.msgtype() << " "
              << connection.msgcount() << "\n";
  }

  rosbags::MessageStream stream = reader.messages();
  rosbags::Message message;
  while (stream.next(message)) {
    std::cout << message.timestamp << " "
              << message.connection.topic() << " "
              << message.data.size() << " bytes\n";
  }

  reader.close();
}
```

Filter by connection and time:

```cpp
rosbags::ReaderMessageOptions options;
options.connection_ids = {0};
options.start_time = 1'700'000'000'000'000'000LL;
options.stop_time = 1'700'000'010'000'000'000LL;

auto stream = reader.messages(options);
```

`stop_time` is exclusive.

## Copying Raw Bags

Raw copying preserves serialized bytes and connection metadata. It does not
convert between ROS1 and CDR wire formats.

```cpp
#include <map>
#include <rosbags/rosbags.hpp>

rosbags::Reader reader({"/data/input.bag"});
reader.open();

rosbags::WriterOptions options;
options.format = reader.bag_format();

rosbags::Writer writer("/data/output.bag", options);
writer.open();

std::map<int, rosbags::Connection> connections;
for (const auto& connection : reader.connections()) {
  connections.emplace(connection.id(), writer.add_connection(connection));
}

rosbags::MessageStream stream = reader.messages();
rosbags::Message message;
while (stream.next(message)) {
  writer.write(
      connections.at(message.connection.id()),
      message.timestamp,
      message.data);
}

writer.close();
reader.close();
```

## Writing Raw Messages

Use `ConnectionSpec` when you already have the message definition and digest:

```cpp
rosbags::WriterOptions options;
options.format = rosbags::BagFormat::Rosbag2;
options.storage = rosbags::StoragePlugin::Sqlite3;

rosbags::Writer writer("/tmp/raw_bag", options);
writer.open();

rosbags::ConnectionSpec spec;
spec.topic = "/count";
spec.msgtype = "std_msgs/msg/Int8";
spec.msgdef_format = rosbags::MessageDefinitionFormat::Msg;
spec.msgdef_data = "int8 data\n";
spec.digest =
    "RIHS01_26525065a403d972cb672f0777e333f0c799ad444ae5fcd79e43d1e73bd0f440";

auto connection = writer.add_connection(spec);
writer.write(connection, 123, {0, 1, 0, 0, 42});
writer.close();
```

For rosbag1, `digest` must be the ROS1 MD5. For rosbag2, it must be the
`RIHS01_` type hash.

## Typed Messages

Use `Typestore` for schema-aware messages:

```cpp
rosbags::Typestore store(rosbags::TypestorePreset::Latest);

auto message = store.deserialize_cdr(
    {0, 1, 0, 0, 1},
    "std_msgs/msg/Int8");

auto value = message.get("data").as_int();
message.set("data", rosbags::TypedValue::from_int(value + 1));

auto raw_cdr = store.serialize_cdr(message);
auto raw_ros1 = store.serialize_ros1(message);
```

Create typed messages:

```cpp
auto message = store.create(
    "std_msgs/msg/Int8",
    {{"data", rosbags::TypedValue::from_int(42)}});
```

Nested messages and arrays use `TypedValue::from_message()` and
`TypedValue::from_array()`.

## Reading Typed Messages From A Bag

`Reader` builds a typestore from bag metadata. The configured default preset is
loaded lazily when typed deserialization is requested, so raw reads do not pay
for the full built-in typestore.

```cpp
rosbags::Reader reader({"/data/input.bag"});
reader.open();

auto stream = reader.messages();
rosbags::Message raw;
while (stream.next(raw)) {
  if (raw.connection.topic() == "/imu") {
    auto typed = reader.deserialize(raw);
    auto header = typed.get("header").as_message();
    auto frame_id = header.get("frame_id").as_string();
  }
}

reader.close();
```

To change the default preset:

```cpp
rosbags::ReaderOptions options;
options.default_typestore = rosbags::TypestorePreset::Ros1Noetic;
rosbags::Reader reader({"/data/input.bag"}, options);
```

## Registering Custom Types

Register MSG:

```cpp
rosbags::Typestore store(rosbags::TypestorePreset::Empty);
store.register_msg(
    "example_msgs/msg/Counter",
    "int32 count\nstring label\nuint8[] values\n");
```

Register IDL:

```cpp
store.register_idl(R"(
module example_msgs {
  module msg {
    struct Counter {
      int32 count;
      string label;
    };
  };
};
)");
```

Generate connection metadata from a typestore:

```cpp
auto spec = store.connection_spec(
    "/counter",
    "example_msgs/msg/Counter",
    rosbags::BagFormat::Rosbag2);
```

## Writing Typed Messages

```cpp
rosbags::Typestore store(rosbags::TypestorePreset::Latest);

rosbags::WriterOptions options;
options.format = rosbags::BagFormat::Rosbag2;
options.storage = rosbags::StoragePlugin::Mcap;

rosbags::Writer writer("/tmp/typed_bag", options);
writer.open();

auto connection = writer.add_connection(
    "/count",
    "std_msgs/msg/Int8",
    store);

auto message = store.create(
    "std_msgs/msg/Int8",
    {{"data", rosbags::TypedValue::from_int(42)}});

writer.write(connection, 123, message, store);
writer.close();
```

`Writer::write(connection, timestamp, typed_message, typestore)` serializes as
ROS1 bytes for rosbag1 writers and CDR bytes for rosbag2 writers.

## Writer Options

```cpp
rosbags::WriterOptions options;
options.format = rosbags::BagFormat::Rosbag2;
options.storage = rosbags::StoragePlugin::Sqlite3;
options.rosbag2_version = 9;
options.compression_mode = rosbags::CompressionMode::None;
options.compression_format = rosbags::CompressionFormat::None;
options.chunk_threshold = 1U << 20U;
```

Supported storage:

- rosbag1: `.bag` file
- rosbag2 sqlite3: directory containing `.db3` and `metadata.yaml`
- rosbag2 MCAP: directory containing `.mcap` and `metadata.yaml`

Supported compression:

- rosbag1: `None`, `Bz2`, `Lz4`
- rosbag2 sqlite3: zstd `File` and `Message`
- rosbag2 MCAP: zstd `File`, zstd `Message`, and `Storage` with `Lz4` or `Zstd`

Writing defaults to no compression.

## Examples

Configure with examples enabled:

```sh
cmake -S cpp -B build/cpp \
  -DCMAKE_BUILD_TYPE=Release \
  -DROSBAGS_CPP_BUILD_EXAMPLES=ON
cmake --build build/cpp
```

Read raw messages:

```sh
./build/cpp/rosbags_cpp_read_raw /path/to/bag
```

Copy a bag without converting serialization formats:

```sh
./build/cpp/rosbags_cpp_copy_raw /path/to/src.bag /path/to/dst.bag
```

Convert a ROS1 bag to a ROS2 sqlite3 bag, registering custom ROS2 message
definitions when needed:

```sh
./build/cpp/rosbags_cpp_convert \
  /path/to/src.bag \
  /path/to/dst_ros2 \
  0 \
  livox_ros_driver2/msg/CustomPoint=msg/livox_ros_driver2/CustomPoint.msg \
  livox_ros_driver2/msg/CustomMsg=msg/livox_ros_driver2/CustomMsg.msg
```

Benchmark raw iteration, optionally forcing typed deserialization for selected
topics:

```sh
./build/cpp/rosbags_cpp_bench_raw /path/to/bag /topic/name
```

## Notes And Limits

- The C++ API intentionally does not run the Python CLI converter.
- Raw copying keeps the source wire format. Use `Typestore::convert_raw()` or
  `rosbags_cpp_convert` if you need to convert ROS1 bytes to CDR bytes.
- Built-in typestore presets are compiled into
  `cpp/src/generated_typestores.inc`; normal builds do not generate this file.
