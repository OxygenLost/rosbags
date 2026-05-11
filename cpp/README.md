# rosbags C++ API

This directory contains a first C++ API for reading and writing rosbag messages
from C++17 projects. It embeds Python with `pybind11::embed` and reuses the
existing Python `rosbags` package internally.

The API exposes both raw serialized bytes and a dynamic typed message layer.
The typed layer is designed for correctness and convenience. High-throughput
bag copying should continue to use the raw byte API. Message migration and pure
C++ storage backends remain Python features for this first version.

## Build

```sh
cmake -S cpp -B build/cpp
cmake --build build/cpp
cmake --install build/cpp
```

The build requires a Python interpreter with the `rosbags` runtime dependencies
available, Python development headers, and a CMake package for `pybind11`.

When using an editable source checkout, pass the Python source directory to the
runtime:

```cpp
rosbags::RuntimeOptions options;
options.python_paths = {"/path/to/rosbags/src"};
rosbags::Runtime runtime(options);
```

Installed use can rely on normal Python import resolution as long as
`import rosbags` works in the embedded interpreter.

## Typed messages

Use `Typestore` for typed serialization and deserialization. Messages are
dynamic objects with field-name based access:

```cpp
rosbags::Typestore store(runtime, rosbags::TypestorePreset::Latest);

auto message = store.deserialize_cdr(
    {0, 1, 0, 0, 1},
    "std_msgs/msg/Int8");
auto value = message.get("data").as_int();

message.set("data", rosbags::TypedValue::from_int(value + 1));
auto raw = store.serialize_cdr(message);
```

Create and write typed messages directly:

```cpp
rosbags::WriterOptions writer_options;
writer_options.format = rosbags::BagFormat::Rosbag2;

rosbags::Writer writer(runtime, "/tmp/typed_bag", writer_options);
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

Readers expose the typestore built from bag metadata:

```cpp
rosbags::Reader reader(runtime, {"/tmp/typed_bag"});
reader.open();

rosbags::MessageStream stream = reader.messages();
rosbags::Message raw_message;
while (stream.next(raw_message)) {
  auto typed = reader.deserialize(raw_message);
  auto count = typed.get("data").as_int();
}

reader.close();
```

Register custom message definitions before creating or deserializing custom
types:

```cpp
rosbags::Typestore custom(runtime, rosbags::TypestorePreset::Empty);
custom.register_msg(
    "example_msgs/msg/Counter",
    "int32 count\nstring label\n");

auto message = custom.create(
    "example_msgs/msg/Counter",
    {
        {"count", rosbags::TypedValue::from_int(5)},
        {"label", rosbags::TypedValue::from_string("five")},
    });
```

## Examples

Configure with examples enabled:

```sh
cmake -S cpp -B build/cpp -DROSBAGS_CPP_BUILD_EXAMPLES=ON
cmake --build build/cpp
```

Read raw messages:

```sh
./build/cpp/rosbags_cpp_read_raw /path/to/bag /path/to/rosbags/src
```

Copy a bag without converting serialization formats:

```sh
./build/cpp/rosbags_cpp_copy_raw /path/to/src.bag /path/to/dst.bag /path/to/rosbags/src
```

Raw copying only supports source and destination bags with the same wire format.
For rosbag1 to rosbag2 conversion, continue using the Python converter.
