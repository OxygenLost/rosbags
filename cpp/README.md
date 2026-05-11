# rosbags C++ raw API

This directory contains a first C++ API for reading and writing raw serialized
rosbag messages from C++17 projects. It embeds Python with `pybind11::embed`
and reuses the existing Python `rosbags` package internally.

The API intentionally exposes raw bytes only. Typed message deserialization,
field access, message migration, and pure C++ storage backends remain Python
features for this first version.

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
