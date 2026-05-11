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

auto make_int8_message(rosbags::Typestore& store, std::int64_t value) -> rosbags::TypedMessage {
  return store.create(kMsgtype, {{"data", rosbags::TypedValue::from_int(value)}});
}

void test_typestore_scalar(rosbags::Runtime& runtime) {
  rosbags::Typestore store(runtime, rosbags::TypestorePreset::Latest);

  auto message = store.deserialize_cdr({0, 1, 0, 0, 1}, kMsgtype);
  require(message.valid(), "typed message should be valid");
  require(message.msgtype() == kMsgtype, "typed message type mismatch");
  require(message.get("data").as_int() == 1, "typed int8 value mismatch");

  message.set("data", rosbags::TypedValue::from_int(2));
  require(store.serialize_cdr(message) == std::vector<std::uint8_t>({0, 1, 0, 0, 2}), "typed cdr serialize mismatch");
  require(store.serialize_ros1(message) == std::vector<std::uint8_t>({2}), "typed ros1 serialize mismatch");

  require(store.cdr_to_ros1({0, 1, 0, 0, 3}, kMsgtype) == std::vector<std::uint8_t>({3}), "cdr_to_ros1 mismatch");
  require(store.ros1_to_cdr({4}, kMsgtype) == std::vector<std::uint8_t>({0, 1, 0, 0, 4}), "ros1_to_cdr mismatch");
}

void test_nested_message(rosbags::Runtime& runtime) {
  rosbags::Typestore store(runtime, rosbags::TypestorePreset::Latest);

  auto stamp = store.create(
      "builtin_interfaces/msg/Time",
      {
          {"sec", rosbags::TypedValue::from_int(708)},
          {"nanosec", rosbags::TypedValue::from_uint(256)},
      });
  auto header = store.create(
      "std_msgs/msg/Header",
      {
          {"stamp", rosbags::TypedValue::from_message(stamp)},
          {"frame_id", rosbags::TypedValue::from_string("foo42")},
      });
  auto vector = store.create(
      "geometry_msgs/msg/Vector3",
      {
          {"x", rosbags::TypedValue::from_double(128.0)},
          {"y", rosbags::TypedValue::from_double(128.0)},
          {"z", rosbags::TypedValue::from_double(128.0)},
      });

  std::vector<rosbags::TypedValue> covariance;
  covariance.reserve(9);
  for (int idx = 0; idx < 9; ++idx) {
    covariance.push_back(rosbags::TypedValue::from_double(idx % 4 == 0 ? 1.0 : 0.0));
  }

  auto magnetic = store.create(
      "sensor_msgs/msg/MagneticField",
      {
          {"header", rosbags::TypedValue::from_message(header)},
          {"magnetic_field", rosbags::TypedValue::from_message(vector)},
          {"magnetic_field_covariance", rosbags::TypedValue::from_array(covariance)},
      });

  auto copied = store.deserialize_cdr(store.serialize_cdr(magnetic), magnetic.msgtype());
  const auto& copied_header = copied.get("header").as_message();
  const auto& copied_stamp = copied_header.get("stamp").as_message();
  require(copied_stamp.get("sec").as_int() == 708, "nested timestamp sec mismatch");
  require(copied_stamp.get("nanosec").as_uint() == 256, "nested timestamp nanosec mismatch");
  require(copied_header.get("frame_id").as_string() == "foo42", "nested string mismatch");
  require(copied.get("magnetic_field").as_message().get("x").as_double() == 128.0, "nested float mismatch");
  require(copied.get("magnetic_field_covariance").as_array().size() == 9, "fixed array size mismatch");
  require(!copied.field_names().empty(), "field names should not be empty");
  require(!copied.fields().empty(), "fields should not be empty");
}

void test_custom_msg_roundtrip(rosbags::Runtime& runtime) {
  rosbags::Typestore store(runtime, rosbags::TypestorePreset::Empty);
  const std::string msgtype = "test_msgs/msg/Dynamic";
  store.register_msg(msgtype, "int32 count\nstring label\nuint8[] values\n");

  auto message = store.create(
      msgtype,
      {
          {"count", rosbags::TypedValue::from_int(5)},
          {"label", rosbags::TypedValue::from_string("five")},
          {"values",
           rosbags::TypedValue::from_array(
               {rosbags::TypedValue::from_uint(1), rosbags::TypedValue::from_uint(2)})},
      });

  auto cdr_copy = store.deserialize_cdr(store.serialize_cdr(message), msgtype);
  require(cdr_copy.get("count").as_int() == 5, "custom cdr count mismatch");
  require(cdr_copy.get("label").as_string() == "five", "custom cdr string mismatch");
  require(cdr_copy.get("values").as_array()[1].as_uint() == 2, "custom cdr sequence mismatch");

  auto ros1_copy = store.deserialize_ros1(store.serialize_ros1(message), msgtype);
  require(ros1_copy.get("values").as_array()[0].as_uint() == 1, "custom ros1 sequence mismatch");

  const std::string idl_type = "test_msgs/msg/IdlCounter";
  store.register_idl(R"(
module test_msgs {
  module msg {
    struct IdlCounter {
      int32 count;
      string label;
    };
  };
};
)");
  auto idl_message = store.create(
      idl_type,
      {
          {"count", rosbags::TypedValue::from_int(9)},
          {"label", rosbags::TypedValue::from_string("nine")},
      });
  auto idl_copy = store.deserialize_cdr(store.serialize_cdr(idl_message), idl_type);
  require(idl_copy.get("count").as_int() == 9, "custom idl count mismatch");
  require(idl_copy.get("label").as_string() == "nine", "custom idl string mismatch");
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

void test_typed_write_read(
    rosbags::Runtime& runtime,
    const fs::path& path,
    rosbags::WriterOptions options) {
  rosbags::Typestore store(
      runtime,
      options.format == rosbags::BagFormat::Rosbag1 ? rosbags::TypestorePreset::Ros1Noetic
                                                    : rosbags::TypestorePreset::Latest);

  rosbags::Writer writer(runtime, path.string(), options);
  writer.open();
  auto connection = writer.add_connection("/typed", kMsgtype, store);
  writer.write(connection, 10, make_int8_message(store, 7), store);
  writer.write(connection, 20, make_int8_message(store, 8), store);
  writer.close();

  rosbags::Reader reader(runtime, {path.string()});
  reader.open();
  const auto messages = read_all(reader);
  require(messages.size() == 2, "typed bag message count mismatch");
  require(reader.deserialize(messages[0]).get("data").as_int() == 7, "reader typed deserialize mismatch");

  auto reader_store = reader.typestore();
  auto typed = reader_store.deserialize_raw(
      messages[1].data, messages[1].connection.msgtype(), reader.bag_format());
  require(typed.get("data").as_int() == 8, "reader typestore deserialize mismatch");
  reader.close();
}

void test_typed_error_paths(rosbags::Runtime& runtime) {
  rosbags::Typestore store(runtime, rosbags::TypestorePreset::Latest);

  bool raised = false;
  try {
    (void)store.create("std_msgs/msg/Int8", {{"missing", rosbags::TypedValue::from_int(1)}});
  } catch (const rosbags::Error&) {
    raised = true;
  }
  require(raised, "unknown field should raise rosbags::Error");

  raised = false;
  try {
    (void)store.create("missing_msgs/msg/Missing");
  } catch (const rosbags::Error&) {
    raised = true;
  }
  require(raised, "unknown type should raise rosbags::Error");

  raised = false;
  try {
    (void)store.create(
        "shape_msgs/msg/Plane",
        {{"coef", rosbags::TypedValue::from_array({rosbags::TypedValue::from_double(1.0)})}});
  } catch (const rosbags::Error&) {
    raised = true;
  }
  require(raised, "fixed array length mismatch should raise rosbags::Error");

  raised = false;
  try {
    (void)store.create(
        "builtin_interfaces/msg/Time",
        {{"sec", rosbags::TypedValue::from_string("bad")}});
  } catch (const rosbags::Error&) {
    raised = true;
  }
  require(raised, "wrong typed value kind should raise rosbags::Error");
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

    test_typestore_scalar(runtime);
    test_nested_message(runtime);
    test_custom_msg_roundtrip(runtime);

    rosbags::WriterOptions rosbag1_options;
    rosbag1_options.format = rosbags::BagFormat::Rosbag1;
    test_write_read(runtime, tmp / "raw1.bag", rosbag1_options, {1}, {2});
    test_typed_write_read(runtime, tmp / "typed1.bag", rosbag1_options);

    rosbags::WriterOptions sqlite_options;
    sqlite_options.format = rosbags::BagFormat::Rosbag2;
    sqlite_options.storage = rosbags::StoragePlugin::Sqlite3;
    test_write_read(runtime, tmp / "raw2_sqlite", sqlite_options, {0, 1, 0, 0, 1}, {0, 1, 0, 0, 2});
    test_typed_write_read(runtime, tmp / "typed2_sqlite", sqlite_options);

    rosbags::WriterOptions mcap_options;
    mcap_options.format = rosbags::BagFormat::Rosbag2;
    mcap_options.storage = rosbags::StoragePlugin::Mcap;
    test_write_read(runtime, tmp / "raw2_mcap", mcap_options, {0, 1, 0, 0, 1}, {0, 1, 0, 0, 2});
    test_typed_write_read(runtime, tmp / "typed2_mcap", mcap_options);

    test_copy_roundtrip(runtime, tmp / "raw2_sqlite", tmp / "raw2_copy");
    test_error_path(runtime, tmp / "bad_manual");
    test_typed_error_paths(runtime);
  } catch (const std::exception& err) {
    std::cerr << err.what() << "\n";
    return 1;
  }

  return 0;
}
