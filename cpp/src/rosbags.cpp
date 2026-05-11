// Copyright 2020-2026 Ternaris
// SPDX-License-Identifier: Apache-2.0

#include "rosbags/rosbags.hpp"

#include <algorithm>
#include <cstddef>
#include <exception>
#include <set>
#include <sstream>
#include <utility>

#include <pybind11/embed.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace rosbags {
namespace {

auto to_error(const py::error_already_set& err) -> Error {
  return Error(err.what());
}

auto format_name(BagFormat format) -> const char* {
  return format == BagFormat::Rosbag1 ? "rosbag1" : "rosbag2";
}

auto optional_int(std::optional<std::int64_t> value) -> py::object {
  if (value) {
    return py::int_(*value);
  }
  return py::none();
}

auto to_bytes(const std::vector<std::uint8_t>& data) -> py::bytes {
  const auto* ptr = data.empty() ? "" : reinterpret_cast<const char*>(data.data());
  return py::bytes(ptr, data.size());
}

auto to_vector(py::handle value) -> std::vector<std::uint8_t> {
  const py::bytes bytes = py::module_::import("builtins").attr("bytes")(value);
  const std::string raw = bytes.cast<std::string>();
  return {raw.begin(), raw.end()};
}

auto msgdef_format_from_python(py::handle value) -> MessageDefinitionFormat {
  const auto raw = value.attr("value").cast<int>();
  switch (raw) {
    case 0:
      return MessageDefinitionFormat::None;
    case 1:
      return MessageDefinitionFormat::Msg;
    case 2:
      return MessageDefinitionFormat::Idl;
    default:
      throw Error("Unknown rosbags message definition format");
  }
}

auto require_connection_state(const std::shared_ptr<detail::ConnectionState>& state)
    -> const detail::ConnectionState&;
auto require_typed_message_state(const std::shared_ptr<detail::TypedMessageState>& state)
    -> const detail::TypedMessageState&;
auto require_typestore_state(const std::shared_ptr<detail::TypestoreState>& state)
    -> const detail::TypestoreState&;

}  // namespace

namespace detail {

struct RuntimeState {
  explicit RuntimeState(const RuntimeOptions& options) {
    try {
      guard = std::make_unique<py::scoped_interpreter>();
      py::gil_scoped_acquire gil;
      py::list sys_path = py::module_::import("sys").attr("path");
      for (auto it = options.python_paths.rbegin(); it != options.python_paths.rend(); ++it) {
        sys_path.attr("insert")(0, *it);
      }
      py::module_::import("rosbags");
    } catch (const py::error_already_set& err) {
      throw to_error(err);
    }
  }

  ~RuntimeState() = default;

  std::unique_ptr<py::scoped_interpreter> guard;
};

struct ConnectionState {
  ConnectionState(
      std::shared_ptr<RuntimeState> runtime_,
      py::object object_,
      BagFormat bag_format_,
      int id_,
      std::string topic_,
      std::string msgtype_,
      MessageDefinitionFormat msgdef_format_,
      std::string msgdef_data_,
      std::string digest_,
      std::int64_t msgcount_)
      : runtime(std::move(runtime_)),
        object(std::move(object_)),
        bag_format(bag_format_),
        id(id_),
        topic(std::move(topic_)),
        msgtype(std::move(msgtype_)),
        msgdef_format(msgdef_format_),
        msgdef_data(std::move(msgdef_data_)),
        digest(std::move(digest_)),
        msgcount(msgcount_) {}

  ~ConnectionState() {
    if (Py_IsInitialized()) {
      py::gil_scoped_acquire gil;
      object = py::object();
    }
  }

  std::shared_ptr<RuntimeState> runtime;
  py::object object;
  BagFormat bag_format;
  int id;
  std::string topic;
  std::string msgtype;
  MessageDefinitionFormat msgdef_format;
  std::string msgdef_data;
  std::string digest;
  std::int64_t msgcount;
};

struct ReaderState {
  ReaderState(std::shared_ptr<RuntimeState> runtime_, std::vector<std::string> paths_)
      : runtime(std::move(runtime_)), paths(std::move(paths_)) {}

  ~ReaderState() {
    if (Py_IsInitialized()) {
      py::gil_scoped_acquire gil;
      connections.clear();
      reader = py::object();
    }
  }

  std::shared_ptr<RuntimeState> runtime;
  py::object reader = py::none();
  std::vector<std::string> paths;
  std::vector<Connection> connections;
  bool is_open = false;
  BagFormat bag_format = BagFormat::Rosbag2;
};

struct MessageStreamState {
  MessageStreamState(
      std::shared_ptr<RuntimeState> runtime_,
      std::shared_ptr<ReaderState> reader_state_,
      py::object iterator_)
      : runtime(std::move(runtime_)),
        reader_state(std::move(reader_state_)),
        iterator(std::move(iterator_)) {}

  ~MessageStreamState() {
    if (Py_IsInitialized()) {
      py::gil_scoped_acquire gil;
      iterator = py::object();
      reader_state.reset();
    }
  }

  std::shared_ptr<RuntimeState> runtime;
  std::shared_ptr<ReaderState> reader_state;
  py::object iterator;
};

struct TypestoreState {
  TypestoreState(std::shared_ptr<RuntimeState> runtime_, py::object object_)
      : runtime(std::move(runtime_)), object(std::move(object_)) {}

  ~TypestoreState() {
    if (Py_IsInitialized()) {
      py::gil_scoped_acquire gil;
      object = py::object();
    }
  }

  std::shared_ptr<RuntimeState> runtime;
  py::object object;
};

struct TypedMessageState {
  TypedMessageState(
      std::shared_ptr<RuntimeState> runtime_,
      py::object typestore_,
      py::object object_,
      std::string msgtype_)
      : runtime(std::move(runtime_)),
        typestore(std::move(typestore_)),
        object(std::move(object_)),
        msgtype(std::move(msgtype_)) {}

  ~TypedMessageState() {
    if (Py_IsInitialized()) {
      py::gil_scoped_acquire gil;
      object = py::object();
      typestore = py::object();
    }
  }

  std::shared_ptr<RuntimeState> runtime;
  py::object typestore;
  py::object object;
  std::string msgtype;
};

struct TypedValueState {
  explicit TypedValueState(TypedValueKind kind_) : kind(kind_) {}

  TypedValueKind kind = TypedValueKind::None;
  bool bool_value = false;
  std::int64_t int_value = 0;
  std::uint64_t uint_value = 0;
  double double_value = 0.0;
  std::string string_value;
  TypedMessage message_value;
  std::vector<TypedValue> array_value;
};

struct WriterState {
  WriterState(std::shared_ptr<RuntimeState> runtime_, std::string path_, WriterOptions options_)
      : runtime(std::move(runtime_)), path(std::move(path_)), options(options_) {}

  ~WriterState() {
    if (Py_IsInitialized()) {
      py::gil_scoped_acquire gil;
      writer = py::object();
      connections.clear();
    }
  }

  std::shared_ptr<RuntimeState> runtime;
  py::object writer = py::none();
  std::string path;
  WriterOptions options;
  std::vector<Connection> connections;
  bool is_open = false;
};

auto connection_state(const Connection& connection)
    -> const std::shared_ptr<ConnectionState>& {
  return connection.state_;
}

auto make_connection(std::shared_ptr<ConnectionState> state) -> Connection {
  return Connection(std::move(state));
}

auto typed_message_state(const TypedMessage& message)
    -> const std::shared_ptr<TypedMessageState>& {
  return message.state_;
}

auto make_typed_message(std::shared_ptr<TypedMessageState> state) -> TypedMessage {
  return TypedMessage(std::move(state));
}

auto typestore_state(const Typestore& typestore)
    -> const std::shared_ptr<TypestoreState>& {
  return typestore.state_;
}

auto make_typestore(std::shared_ptr<TypestoreState> state) -> Typestore {
  return Typestore(std::move(state));
}

}  // namespace detail

namespace {

auto require_connection_state(const std::shared_ptr<detail::ConnectionState>& state)
    -> const detail::ConnectionState& {
  if (!state) {
    throw Error("Invalid rosbags connection");
  }
  return *state;
}

auto require_typed_message_state(const std::shared_ptr<detail::TypedMessageState>& state)
    -> const detail::TypedMessageState& {
  if (!state) {
    throw Error("Invalid rosbags typed message");
  }
  return *state;
}

auto require_typestore_state(const std::shared_ptr<detail::TypestoreState>& state)
    -> const detail::TypestoreState& {
  if (!state) {
    throw Error("Invalid rosbags typestore");
  }
  return *state;
}

auto preset_name(TypestorePreset preset) -> const char* {
  switch (preset) {
    case TypestorePreset::Empty:
      return "EMPTY";
    case TypestorePreset::Latest:
      return "LATEST";
    case TypestorePreset::Ros1Noetic:
      return "ROS1_NOETIC";
    case TypestorePreset::Ros2Dashing:
      return "ROS2_DASHING";
    case TypestorePreset::Ros2Eloquent:
      return "ROS2_ELOQUENT";
    case TypestorePreset::Ros2Foxy:
      return "ROS2_FOXY";
    case TypestorePreset::Ros2Galactic:
      return "ROS2_GALACTIC";
    case TypestorePreset::Ros2Humble:
      return "ROS2_HUMBLE";
    case TypestorePreset::Ros2Iron:
      return "ROS2_IRON";
    case TypestorePreset::Ros2Jazzy:
      return "ROS2_JAZZY";
    case TypestorePreset::Ros2Kilted:
      return "ROS2_KILTED";
  }
  throw Error("Unknown rosbags typestore preset");
}

auto as_tuple(py::handle value) -> py::tuple {
  return py::reinterpret_borrow<py::tuple>(value);
}

auto tuple_item(py::handle value, std::size_t index) -> py::object {
  return py::reinterpret_borrow<py::object>(as_tuple(value)[index]);
}

auto desc_node(py::handle desc) -> int {
  return tuple_item(desc, 0).cast<int>();
}

auto desc_payload(py::handle desc) -> py::object {
  return tuple_item(desc, 1);
}

auto base_name(py::handle desc) -> std::string {
  return tuple_item(desc_payload(desc), 0).cast<std::string>();
}

auto array_subdesc(py::handle desc) -> py::object {
  return tuple_item(desc_payload(desc), 0);
}

auto array_bound(py::handle desc) -> int {
  return tuple_item(desc_payload(desc), 1).cast<int>();
}

auto is_bool_base(const std::string& base) -> bool {
  return base == "bool";
}

auto is_string_base(const std::string& base) -> bool {
  return base == "string";
}

auto is_float_base(const std::string& base) -> bool {
  return base == "float32" || base == "float64" || base == "float128";
}

auto is_unsigned_base(const std::string& base) -> bool {
  return base == "byte" || base == "char" || base == "uint8" || base == "uint16" ||
         base == "uint32" || base == "uint64";
}

auto numpy_dtype(const std::string& base) -> py::object {
  py::object numpy = py::module_::import("numpy");
  if (base == "bool") {
    return numpy.attr("bool_");
  }
  if (base == "byte" || base == "char") {
    return numpy.attr("uint8");
  }
  if (base == "float128") {
    return numpy.attr("longdouble");
  }
  return numpy.attr(base.c_str());
}

auto field_list(py::handle typestore, const std::string& msgtype) -> py::list {
  py::object fielddefs = typestore.attr("fielddefs");
  py::object type_entry = fielddefs[py::str(msgtype)];
  return tuple_item(type_entry, 1).cast<py::list>();
}

auto find_field_desc(py::handle typestore, const std::string& msgtype, const std::string& field)
    -> py::object {
  for (py::handle item : field_list(typestore, msgtype)) {
    py::tuple field_entry = py::reinterpret_borrow<py::tuple>(item);
    if (field_entry[0].cast<std::string>() == field) {
      return py::reinterpret_borrow<py::object>(field_entry[1]);
    }
  }

  std::ostringstream stream;
  stream << "Unknown field '" << field << "' for message type '" << msgtype << "'";
  throw Error(stream.str());
}

auto message_from_python(
    const std::shared_ptr<detail::RuntimeState>& runtime,
    py::handle typestore,
    py::handle object,
    std::string msgtype = {}) -> TypedMessage {
  if (msgtype.empty()) {
    msgtype = object.attr("__msgtype__").cast<std::string>();
  }

  auto state = std::make_shared<detail::TypedMessageState>(
      runtime,
      py::reinterpret_borrow<py::object>(typestore),
      py::reinterpret_borrow<py::object>(object),
      std::move(msgtype));
  return detail::make_typed_message(std::move(state));
}

auto value_from_python(
    const std::shared_ptr<detail::RuntimeState>& runtime,
    py::handle typestore,
    py::handle desc,
    py::handle value) -> TypedValue {
  if (value.is_none()) {
    return TypedValue();
  }

  switch (desc_node(desc)) {
    case 1: {
      const auto base = base_name(desc);
      if (is_bool_base(base)) {
        return TypedValue::from_bool(value.cast<bool>());
      }
      if (is_string_base(base)) {
        return TypedValue::from_string(value.cast<std::string>());
      }
      if (is_float_base(base)) {
        return TypedValue::from_double(value.cast<double>());
      }
      if (is_unsigned_base(base)) {
        return TypedValue::from_uint(value.cast<std::uint64_t>());
      }
      return TypedValue::from_int(value.cast<std::int64_t>());
    }
    case 2:
      return TypedValue::from_message(
          message_from_python(runtime, typestore, value, desc_payload(desc).cast<std::string>()));
    case 3:
    case 4: {
      py::object builtins = py::module_::import("builtins");
      py::object list_obj = builtins.attr("list")(value);
      const py::list values = list_obj.cast<py::list>();
      std::vector<TypedValue> result;
      result.reserve(values.size());
      py::object subdesc = array_subdesc(desc);
      for (py::handle item : values) {
        result.push_back(value_from_python(runtime, typestore, subdesc, item));
      }
      return TypedValue::from_array(std::move(result));
    }
    default:
      throw Error("Unknown rosbags field descriptor node");
  }
}

auto expect_kind(const TypedValue& value, TypedValueKind kind, const std::string& context)
    -> void {
  if (value.kind() != kind) {
    std::ostringstream stream;
    stream << "Unexpected typed value kind for " << context;
    throw Error(stream.str());
  }
}

auto value_to_python(py::handle typestore, py::handle desc, const TypedValue& value) -> py::object;

auto default_value_for_desc(
    const std::shared_ptr<detail::RuntimeState>& runtime,
    py::handle typestore,
    py::handle desc) -> TypedValue {
  switch (desc_node(desc)) {
    case 1: {
      const auto base = base_name(desc);
      if (is_bool_base(base)) {
        return TypedValue::from_bool(false);
      }
      if (is_string_base(base)) {
        return TypedValue::from_string("");
      }
      if (is_float_base(base)) {
        return TypedValue::from_double(0.0);
      }
      if (is_unsigned_base(base)) {
        return TypedValue::from_uint(0);
      }
      return TypedValue::from_int(0);
    }
    case 2: {
      const auto nested_type = desc_payload(desc).cast<std::string>();
      py::list nested_fields = field_list(typestore, nested_type);
      py::tuple args(nested_fields.size());
      std::size_t index = 0;
      for (py::handle item : nested_fields) {
        py::tuple field_entry = py::reinterpret_borrow<py::tuple>(item);
        py::object nested_desc = py::reinterpret_borrow<py::object>(field_entry[1]);
        TypedValue nested_default = default_value_for_desc(runtime, typestore, nested_desc);
        args[index++] = value_to_python(typestore, nested_desc, nested_default);
      }
      py::object cls = typestore.attr("types")[py::str(nested_type)];
      return TypedValue::from_message(message_from_python(runtime, typestore, cls(*args), nested_type));
    }
    case 3: {
      std::vector<TypedValue> values;
      const auto count = array_bound(desc);
      values.reserve(static_cast<std::size_t>(count));
      py::object subdesc = array_subdesc(desc);
      for (int idx = 0; idx < count; ++idx) {
        values.push_back(default_value_for_desc(runtime, typestore, subdesc));
      }
      return TypedValue::from_array(std::move(values));
    }
    case 4:
      return TypedValue::from_array({});
    default:
      throw Error("Unknown rosbags field descriptor node");
  }
}

auto value_to_python(py::handle typestore, py::handle desc, const TypedValue& value) -> py::object {
  switch (desc_node(desc)) {
    case 1: {
      const auto base = base_name(desc);
      if (is_bool_base(base)) {
        expect_kind(value, TypedValueKind::Bool, base);
        return py::bool_(value.as_bool());
      }
      if (is_string_base(base)) {
        expect_kind(value, TypedValueKind::String, base);
        return py::str(value.as_string());
      }
      if (is_float_base(base)) {
        expect_kind(value, TypedValueKind::Float, base);
        return py::float_(value.as_double());
      }
      if (is_unsigned_base(base)) {
        expect_kind(value, TypedValueKind::UInt, base);
        return py::int_(value.as_uint());
      }
      expect_kind(value, TypedValueKind::Int, base);
      return py::int_(value.as_int());
    }
    case 2: {
      const auto expected = desc_payload(desc).cast<std::string>();
      expect_kind(value, TypedValueKind::Message, expected);
      TypedMessage message = value.as_message();
      const auto& message_state = require_typed_message_state(
          detail::typed_message_state(message));
      if (message_state.msgtype != expected) {
        std::ostringstream stream;
        stream << "Expected typed message '" << expected << "', got '" << message_state.msgtype
               << "'";
        throw Error(stream.str());
      }
      return message_state.object;
    }
    case 3:
    case 4: {
      expect_kind(value, TypedValueKind::Array, "array or sequence");
      const auto& values = value.as_array();
      if (desc_node(desc) == 3 && values.size() != static_cast<std::size_t>(array_bound(desc))) {
        throw Error("Unexpected array length");
      }

      py::object subdesc = array_subdesc(desc);
      py::list result;
      for (const auto& item : values) {
        result.append(value_to_python(typestore, subdesc, item));
      }

      if (desc_node(subdesc) == 1) {
        const auto base = base_name(subdesc);
        if (!is_string_base(base)) {
          py::object numpy = py::module_::import("numpy");
          return numpy.attr("array")(result, py::arg("dtype") = numpy_dtype(base));
        }
      }
      return std::move(result);
    }
    default:
      throw Error("Unknown rosbags field descriptor node");
  }
}

auto connection_from_python(
    const std::shared_ptr<detail::RuntimeState>& runtime,
    py::handle connection,
    BagFormat bag_format) -> Connection {
  const py::object msgdef = connection.attr("msgdef");
  auto state = std::make_shared<detail::ConnectionState>(
      runtime,
      py::reinterpret_borrow<py::object>(connection),
      bag_format,
      connection.attr("id").cast<int>(),
      connection.attr("topic").cast<std::string>(),
      connection.attr("msgtype").cast<std::string>(),
      msgdef_format_from_python(msgdef.attr("format")),
      msgdef.attr("data").cast<std::string>(),
      connection.attr("digest").cast<std::string>(),
      connection.attr("msgcount").cast<std::int64_t>());
  return detail::make_connection(std::move(state));
}

auto require_reader_open(const detail::ReaderState& state) -> void {
  if (!state.is_open) {
    throw Error("Rosbag reader is not open");
  }
}

auto require_writer_open(const detail::WriterState& state) -> void {
  if (!state.is_open) {
    throw Error("Rosbag writer is not open");
  }
}

auto connection_ids_to_python(
    const std::vector<Connection>& connections,
    const std::vector<int>& ids) -> py::list {
  py::list result;
  if (ids.empty()) {
    return result;
  }

  const std::set<int> wanted(ids.begin(), ids.end());
  for (const auto& connection : connections) {
    const auto& state = require_connection_state(detail::connection_state(connection));
    if (wanted.count(state.id) != 0) {
      result.append(state.object);
    }
  }
  return result;
}

auto validate_manual_connection(const ConnectionSpec& spec, BagFormat format) -> void {
  if (spec.topic.empty()) {
    throw Error("ConnectionSpec.topic is required");
  }
  if (spec.msgtype.empty()) {
    throw Error("ConnectionSpec.msgtype is required");
  }
  if (spec.msgdef_data.empty()) {
    throw Error("ConnectionSpec.msgdef_data is required for raw writes");
  }
  if (spec.digest.empty()) {
    throw Error("ConnectionSpec.digest is required for raw writes");
  }
  if (format == BagFormat::Rosbag2 && spec.serialization_format.empty()) {
    throw Error("ConnectionSpec.serialization_format is required for rosbag2 raw writes");
  }
}

auto source_spec_from_connection(const Connection& connection) -> ConnectionSpec {
  const auto& source = require_connection_state(detail::connection_state(connection));
  ConnectionSpec spec;
  spec.topic = source.topic;
  spec.msgtype = source.msgtype;
  spec.msgdef_format = source.msgdef_format;
  spec.msgdef_data = source.msgdef_data;
  spec.digest = source.digest;
  return spec;
}

auto derive_rosbag2_digest(const ConnectionSpec& spec) -> std::string {
  py::object typesys = py::module_::import("rosbags.typesys");
  py::object typs;
  if (spec.msgdef_format == MessageDefinitionFormat::Idl) {
    typs = typesys.attr("get_types_from_idl")(spec.msgdef_data);
  } else {
    typs = typesys.attr("get_types_from_msg")(spec.msgdef_data, spec.msgtype);
  }

  py::object stores = typesys.attr("Stores");
  py::object store = typesys.attr("get_typestore")(stores.attr("EMPTY"));
  store.attr("register")(typs);
  return store.attr("hash_rihs01")(spec.msgtype).cast<std::string>();
}

}  // namespace

Error::Error(const std::string& message) : std::runtime_error(message) {}
Error::Error(const char* message) : std::runtime_error(message) {}

Runtime::Runtime(RuntimeOptions options)
    : state_(std::make_shared<detail::RuntimeState>(options)) {}
Runtime::~Runtime() = default;
Runtime::Runtime(Runtime&&) noexcept = default;
auto Runtime::operator=(Runtime&&) noexcept -> Runtime& = default;

Connection::Connection(std::shared_ptr<detail::ConnectionState> state) : state_(std::move(state)) {}

auto Connection::valid() const noexcept -> bool {
  return static_cast<bool>(state_);
}

auto Connection::id() const -> int {
  return require_connection_state(state_).id;
}

auto Connection::topic() const -> const std::string& {
  return require_connection_state(state_).topic;
}

auto Connection::msgtype() const -> const std::string& {
  return require_connection_state(state_).msgtype;
}

auto Connection::msgdef_format() const -> MessageDefinitionFormat {
  return require_connection_state(state_).msgdef_format;
}

auto Connection::msgdef_data() const -> const std::string& {
  return require_connection_state(state_).msgdef_data;
}

auto Connection::digest() const -> const std::string& {
  return require_connection_state(state_).digest;
}

auto Connection::msgcount() const -> std::int64_t {
  return require_connection_state(state_).msgcount;
}

auto Connection::bag_format() const -> BagFormat {
  return require_connection_state(state_).bag_format;
}

TypedValue::TypedValue() = default;
TypedValue::~TypedValue() = default;
TypedValue::TypedValue(const TypedValue&) = default;
auto TypedValue::operator=(const TypedValue&) -> TypedValue& = default;
TypedValue::TypedValue(TypedValue&&) noexcept = default;
auto TypedValue::operator=(TypedValue&&) noexcept -> TypedValue& = default;
TypedValue::TypedValue(std::shared_ptr<detail::TypedValueState> state)
    : state_(std::move(state)) {}

auto TypedValue::from_bool(bool value) -> TypedValue {
  auto state = std::make_shared<detail::TypedValueState>(TypedValueKind::Bool);
  state->bool_value = value;
  return TypedValue(std::move(state));
}

auto TypedValue::from_int(std::int64_t value) -> TypedValue {
  auto state = std::make_shared<detail::TypedValueState>(TypedValueKind::Int);
  state->int_value = value;
  return TypedValue(std::move(state));
}

auto TypedValue::from_uint(std::uint64_t value) -> TypedValue {
  auto state = std::make_shared<detail::TypedValueState>(TypedValueKind::UInt);
  state->uint_value = value;
  return TypedValue(std::move(state));
}

auto TypedValue::from_double(double value) -> TypedValue {
  auto state = std::make_shared<detail::TypedValueState>(TypedValueKind::Float);
  state->double_value = value;
  return TypedValue(std::move(state));
}

auto TypedValue::from_string(std::string value) -> TypedValue {
  auto state = std::make_shared<detail::TypedValueState>(TypedValueKind::String);
  state->string_value = std::move(value);
  return TypedValue(std::move(state));
}

auto TypedValue::from_message(TypedMessage value) -> TypedValue {
  auto state = std::make_shared<detail::TypedValueState>(TypedValueKind::Message);
  state->message_value = std::move(value);
  return TypedValue(std::move(state));
}

auto TypedValue::from_array(std::vector<TypedValue> values) -> TypedValue {
  auto state = std::make_shared<detail::TypedValueState>(TypedValueKind::Array);
  state->array_value = std::move(values);
  return TypedValue(std::move(state));
}

auto TypedValue::kind() const noexcept -> TypedValueKind {
  return state_ ? state_->kind : TypedValueKind::None;
}

auto TypedValue::as_bool() const -> bool {
  expect_kind(*this, TypedValueKind::Bool, "bool");
  return state_->bool_value;
}

auto TypedValue::as_int() const -> std::int64_t {
  expect_kind(*this, TypedValueKind::Int, "int");
  return state_->int_value;
}

auto TypedValue::as_uint() const -> std::uint64_t {
  expect_kind(*this, TypedValueKind::UInt, "uint");
  return state_->uint_value;
}

auto TypedValue::as_double() const -> double {
  expect_kind(*this, TypedValueKind::Float, "float");
  return state_->double_value;
}

auto TypedValue::as_string() const -> std::string {
  expect_kind(*this, TypedValueKind::String, "string");
  return state_->string_value;
}

auto TypedValue::as_message() const -> TypedMessage {
  expect_kind(*this, TypedValueKind::Message, "message");
  return state_->message_value;
}

auto TypedValue::as_array() const -> std::vector<TypedValue> {
  expect_kind(*this, TypedValueKind::Array, "array");
  return state_->array_value;
}

TypedMessage::TypedMessage() = default;
TypedMessage::~TypedMessage() = default;
TypedMessage::TypedMessage(const TypedMessage&) = default;
auto TypedMessage::operator=(const TypedMessage&) -> TypedMessage& = default;
TypedMessage::TypedMessage(TypedMessage&&) noexcept = default;
auto TypedMessage::operator=(TypedMessage&&) noexcept -> TypedMessage& = default;
TypedMessage::TypedMessage(std::shared_ptr<detail::TypedMessageState> state)
    : state_(std::move(state)) {}

auto TypedMessage::valid() const noexcept -> bool {
  return static_cast<bool>(state_);
}

auto TypedMessage::msgtype() const -> const std::string& {
  return require_typed_message_state(state_).msgtype;
}

auto TypedMessage::field_names() const -> std::vector<std::string> {
  const auto& state = require_typed_message_state(state_);
  try {
    py::gil_scoped_acquire gil;
    std::vector<std::string> result;
    for (py::handle item : field_list(state.typestore, state.msgtype)) {
      result.push_back(tuple_item(item, 0).cast<std::string>());
    }
    return result;
  } catch (const py::error_already_set& err) {
    throw to_error(err);
  }
}

auto TypedMessage::fields() const -> std::vector<std::pair<std::string, TypedValue>> {
  const auto& state = require_typed_message_state(state_);
  try {
    py::gil_scoped_acquire gil;
    std::vector<std::pair<std::string, TypedValue>> result;
    for (py::handle item : field_list(state.typestore, state.msgtype)) {
      const auto name = tuple_item(item, 0).cast<std::string>();
      py::object desc = tuple_item(item, 1);
      result.emplace_back(
          name,
          value_from_python(state.runtime, state.typestore, desc, state.object.attr(name.c_str())));
    }
    return result;
  } catch (const py::error_already_set& err) {
    throw to_error(err);
  }
}

auto TypedMessage::get(const std::string& field_name) const -> TypedValue {
  const auto& state = require_typed_message_state(state_);
  try {
    py::gil_scoped_acquire gil;
    py::object desc = find_field_desc(state.typestore, state.msgtype, field_name);
    return value_from_python(
        state.runtime, state.typestore, desc, state.object.attr(field_name.c_str()));
  } catch (const py::error_already_set& err) {
    throw to_error(err);
  }
}

void TypedMessage::set(const std::string& field_name, const TypedValue& value) {
  const auto& state = require_typed_message_state(state_);
  try {
    py::gil_scoped_acquire gil;
    py::object desc = find_field_desc(state.typestore, state.msgtype, field_name);
    py::setattr(state.object, field_name.c_str(), value_to_python(state.typestore, desc, value));
  } catch (const py::error_already_set& err) {
    throw to_error(err);
  }
}

Typestore::Typestore(Runtime& runtime, TypestorePreset preset) {
  if (!runtime.state_) {
    throw Error("Runtime is not initialized");
  }

  try {
    py::gil_scoped_acquire gil;
    py::object typesys = py::module_::import("rosbags.typesys");
    py::object stores = typesys.attr("Stores");
    py::object store = typesys.attr("get_typestore")(stores.attr(preset_name(preset)));
    state_ = std::make_shared<detail::TypestoreState>(runtime.state_, std::move(store));
  } catch (const py::error_already_set& err) {
    throw to_error(err);
  }
}

Typestore::Typestore(std::shared_ptr<detail::TypestoreState> state)
    : state_(std::move(state)) {}
Typestore::~Typestore() = default;
Typestore::Typestore(const Typestore&) = default;
auto Typestore::operator=(const Typestore&) -> Typestore& = default;
Typestore::Typestore(Typestore&&) noexcept = default;
auto Typestore::operator=(Typestore&&) noexcept -> Typestore& = default;

void Typestore::register_msg(const std::string& msgtype, const std::string& msgdef) {
  const auto& state = require_typestore_state(state_);
  try {
    py::gil_scoped_acquire gil;
    py::object typesys = py::module_::import("rosbags.typesys");
    state.object.attr("register")(typesys.attr("get_types_from_msg")(msgdef, msgtype));
  } catch (const py::error_already_set& err) {
    throw to_error(err);
  }
}

void Typestore::register_idl(const std::string& idl_text) {
  const auto& state = require_typestore_state(state_);
  try {
    py::gil_scoped_acquire gil;
    py::object typesys = py::module_::import("rosbags.typesys");
    state.object.attr("register")(typesys.attr("get_types_from_idl")(idl_text));
  } catch (const py::error_already_set& err) {
    throw to_error(err);
  }
}

auto Typestore::create(
    const std::string& msgtype,
    std::vector<std::pair<std::string, TypedValue>> fields) const -> TypedMessage {
  const auto& state = require_typestore_state(state_);
  try {
    py::gil_scoped_acquire gil;
    for (const auto& field : fields) {
      (void)find_field_desc(state.object, msgtype, field.first);
    }

    py::list definitions = field_list(state.object, msgtype);
    py::tuple args(definitions.size());
    std::size_t index = 0;
    for (py::handle item : definitions) {
      const auto name = tuple_item(item, 0).cast<std::string>();
      py::object desc = tuple_item(item, 1);
      const TypedValue* selected = nullptr;
      for (const auto& field : fields) {
        if (field.first == name) {
          selected = &field.second;
        }
      }

      TypedValue fallback;
      if (!selected) {
        fallback = default_value_for_desc(state.runtime, state.object, desc);
        selected = &fallback;
      }
      args[index++] = value_to_python(state.object, desc, *selected);
    }

    py::object cls = state.object.attr("types")[py::str(msgtype)];
    return message_from_python(state.runtime, state.object, cls(*args), msgtype);
  } catch (const py::error_already_set& err) {
    throw to_error(err);
  }
}

auto Typestore::deserialize_cdr(
    const std::vector<std::uint8_t>& data,
    const std::string& msgtype) const -> TypedMessage {
  const auto& state = require_typestore_state(state_);
  try {
    py::gil_scoped_acquire gil;
    py::object message = state.object.attr("deserialize_cdr")(to_bytes(data), msgtype);
    return message_from_python(state.runtime, state.object, std::move(message), msgtype);
  } catch (const py::error_already_set& err) {
    throw to_error(err);
  }
}

auto Typestore::serialize_cdr(const TypedMessage& message, bool little_endian) const
    -> std::vector<std::uint8_t> {
  const auto& state = require_typestore_state(state_);
  const auto& message_state = require_typed_message_state(detail::typed_message_state(message));
  try {
    py::gil_scoped_acquire gil;
    return to_vector(state.object.attr("serialize_cdr")(
        message_state.object,
        message_state.msgtype,
        py::arg("little_endian") = little_endian));
  } catch (const py::error_already_set& err) {
    throw to_error(err);
  }
}

auto Typestore::deserialize_ros1(
    const std::vector<std::uint8_t>& data,
    const std::string& msgtype) const -> TypedMessage {
  const auto& state = require_typestore_state(state_);
  try {
    py::gil_scoped_acquire gil;
    py::object message = state.object.attr("deserialize_ros1")(to_bytes(data), msgtype);
    return message_from_python(state.runtime, state.object, std::move(message), msgtype);
  } catch (const py::error_already_set& err) {
    throw to_error(err);
  }
}

auto Typestore::serialize_ros1(const TypedMessage& message) const -> std::vector<std::uint8_t> {
  const auto& state = require_typestore_state(state_);
  const auto& message_state = require_typed_message_state(detail::typed_message_state(message));
  try {
    py::gil_scoped_acquire gil;
    return to_vector(state.object.attr("serialize_ros1")(message_state.object, message_state.msgtype));
  } catch (const py::error_already_set& err) {
    throw to_error(err);
  }
}

auto Typestore::deserialize_raw(
    const std::vector<std::uint8_t>& data,
    const std::string& msgtype,
    BagFormat format) const -> TypedMessage {
  return format == BagFormat::Rosbag1 ? deserialize_ros1(data, msgtype)
                                      : deserialize_cdr(data, msgtype);
}

auto Typestore::serialize_raw(const TypedMessage& message, BagFormat format) const
    -> std::vector<std::uint8_t> {
  return format == BagFormat::Rosbag1 ? serialize_ros1(message) : serialize_cdr(message);
}

auto Typestore::ros1_to_cdr(
    const std::vector<std::uint8_t>& data,
    const std::string& msgtype) const -> std::vector<std::uint8_t> {
  const auto& state = require_typestore_state(state_);
  try {
    py::gil_scoped_acquire gil;
    return to_vector(state.object.attr("ros1_to_cdr")(to_bytes(data), msgtype));
  } catch (const py::error_already_set& err) {
    throw to_error(err);
  }
}

auto Typestore::cdr_to_ros1(
    const std::vector<std::uint8_t>& data,
    const std::string& msgtype) const -> std::vector<std::uint8_t> {
  const auto& state = require_typestore_state(state_);
  try {
    py::gil_scoped_acquire gil;
    return to_vector(state.object.attr("cdr_to_ros1")(to_bytes(data), msgtype));
  } catch (const py::error_already_set& err) {
    throw to_error(err);
  }
}

auto Typestore::connection_spec(
    std::string topic,
    std::string msgtype,
    BagFormat format,
    std::string serialization_format) const -> ConnectionSpec {
  const auto& state = require_typestore_state(state_);
  try {
    py::gil_scoped_acquire gil;
    const auto ros_version = format == BagFormat::Rosbag1 ? 1 : 2;
    const py::tuple generated = state.object.attr("generate_msgdef")(
        msgtype, py::arg("ros_version") = ros_version);

    ConnectionSpec spec;
    spec.topic = std::move(topic);
    spec.msgtype = std::move(msgtype);
    spec.msgdef_format = MessageDefinitionFormat::Msg;
    spec.msgdef_data = generated[0].cast<std::string>();
    spec.digest = format == BagFormat::Rosbag1
                      ? generated[1].cast<std::string>()
                      : state.object.attr("hash_rihs01")(spec.msgtype).cast<std::string>();
    spec.serialization_format = std::move(serialization_format);
    return spec;
  } catch (const py::error_already_set& err) {
    throw to_error(err);
  }
}

MessageStream::MessageStream() = default;
MessageStream::~MessageStream() = default;
MessageStream::MessageStream(std::shared_ptr<detail::MessageStreamState> state)
    : state_(std::move(state)) {}
MessageStream::MessageStream(MessageStream&&) noexcept = default;
auto MessageStream::operator=(MessageStream&&) noexcept -> MessageStream& = default;

auto MessageStream::next(Message& message) -> bool {
  if (!state_) {
    return false;
  }

  try {
    py::gil_scoped_acquire gil;
    py::object item = state_->iterator.attr("__next__")();
    const py::tuple tuple = item.cast<py::tuple>();
    if (tuple.size() != 3) {
      throw Error("rosbags message iterator yielded an unexpected tuple");
    }

    const auto format = state_->reader_state->bag_format;
    message.connection = connection_from_python(state_->runtime, tuple[0], format);
    message.timestamp = tuple[1].cast<std::int64_t>();
    message.data = to_vector(tuple[2]);
    return true;
  } catch (const py::stop_iteration&) {
    return false;
  } catch (const py::error_already_set& err) {
    if (err.matches(PyExc_StopIteration)) {
      return false;
    }
    throw to_error(err);
  }
}

Reader::Reader(Runtime& runtime, std::vector<std::string> paths)
    : state_(std::make_shared<detail::ReaderState>(runtime.state_, std::move(paths))) {
  if (!state_->runtime) {
    throw Error("Runtime is not initialized");
  }
  if (state_->paths.empty()) {
    throw Error("Reader requires at least one path");
  }

  try {
    py::gil_scoped_acquire gil;
    py::object path_cls = py::module_::import("pathlib").attr("Path");
    py::list py_paths;
    for (const auto& path : state_->paths) {
      py_paths.append(path_cls(path));
    }

    py::object any_reader = py::module_::import("rosbags.highlevel").attr("AnyReader");
    py::object typesys = py::module_::import("rosbags.typesys");
    py::object stores = typesys.attr("Stores");
    py::object default_typestore = typesys.attr("get_typestore")(stores.attr("LATEST"));

    state_->reader = any_reader(py_paths, py::arg("default_typestore") = default_typestore);
    state_->bag_format = state_->reader.attr("is2").cast<bool>() ? BagFormat::Rosbag2
                                                                 : BagFormat::Rosbag1;
  } catch (const py::error_already_set& err) {
    throw to_error(err);
  }
}

Reader::Reader(Runtime& runtime, std::initializer_list<std::string> paths)
    : Reader(runtime, std::vector<std::string>(paths)) {}

Reader::~Reader() = default;
Reader::Reader(Reader&&) noexcept = default;
auto Reader::operator=(Reader&&) noexcept -> Reader& = default;

void Reader::open() {
  try {
    py::gil_scoped_acquire gil;
    state_->reader.attr("open")();
    state_->is_open = true;
    state_->connections.clear();
    for (py::handle connection : state_->reader.attr("connections")) {
      state_->connections.push_back(
          connection_from_python(state_->runtime, connection, state_->bag_format));
    }
  } catch (const py::error_already_set& err) {
    throw to_error(err);
  }
}

void Reader::close() {
  if (!state_->is_open) {
    return;
  }

  try {
    py::gil_scoped_acquire gil;
    state_->reader.attr("close")();
    state_->is_open = false;
  } catch (const py::error_already_set& err) {
    throw to_error(err);
  }
}

auto Reader::is_open() const noexcept -> bool {
  return state_ && state_->is_open;
}

auto Reader::bag_format() const -> BagFormat {
  return state_->bag_format;
}

auto Reader::connections() const -> std::vector<Connection> {
  require_reader_open(*state_);
  return state_->connections;
}

auto Reader::messages(ReaderMessageOptions options) -> MessageStream {
  require_reader_open(*state_);

  try {
    py::gil_scoped_acquire gil;
    py::list py_connections = connection_ids_to_python(state_->connections, options.connection_ids);
    py::object generator = state_->reader.attr("messages")(
        py::arg("connections") = py_connections,
        py::arg("start") = optional_int(options.start_time),
        py::arg("stop") = optional_int(options.stop_time));

    return MessageStream(std::make_shared<detail::MessageStreamState>(
        state_->runtime, state_, std::move(generator)));
  } catch (const py::error_already_set& err) {
    throw to_error(err);
  }
}

auto Reader::typestore() const -> Typestore {
  require_reader_open(*state_);
  try {
    py::gil_scoped_acquire gil;
    return detail::make_typestore(std::make_shared<detail::TypestoreState>(
        state_->runtime, py::reinterpret_borrow<py::object>(state_->reader.attr("typestore"))));
  } catch (const py::error_already_set& err) {
    throw to_error(err);
  }
}

auto Reader::deserialize(const Message& message) const -> TypedMessage {
  require_reader_open(*state_);
  const auto& connection = require_connection_state(detail::connection_state(message.connection));
  try {
    py::gil_scoped_acquire gil;
    py::object py_message = state_->reader.attr("deserialize")(
        to_bytes(message.data), connection.msgtype);
    return message_from_python(
        state_->runtime, state_->reader.attr("typestore"), std::move(py_message), connection.msgtype);
  } catch (const py::error_already_set& err) {
    throw to_error(err);
  }
}

auto Reader::duration() const -> std::int64_t {
  require_reader_open(*state_);
  try {
    py::gil_scoped_acquire gil;
    return state_->reader.attr("duration").cast<std::int64_t>();
  } catch (const py::error_already_set& err) {
    throw to_error(err);
  }
}

auto Reader::start_time() const -> std::int64_t {
  require_reader_open(*state_);
  try {
    py::gil_scoped_acquire gil;
    return state_->reader.attr("start_time").cast<std::int64_t>();
  } catch (const py::error_already_set& err) {
    throw to_error(err);
  }
}

auto Reader::end_time() const -> std::int64_t {
  require_reader_open(*state_);
  try {
    py::gil_scoped_acquire gil;
    return state_->reader.attr("end_time").cast<std::int64_t>();
  } catch (const py::error_already_set& err) {
    throw to_error(err);
  }
}

auto Reader::message_count() const -> std::int64_t {
  require_reader_open(*state_);
  try {
    py::gil_scoped_acquire gil;
    return state_->reader.attr("message_count").cast<std::int64_t>();
  } catch (const py::error_already_set& err) {
    throw to_error(err);
  }
}

Writer::Writer(Runtime& runtime, std::string path, WriterOptions options)
    : state_(std::make_shared<detail::WriterState>(
          runtime.state_, std::move(path), std::move(options))) {
  if (!state_->runtime) {
    throw Error("Runtime is not initialized");
  }

  try {
    py::gil_scoped_acquire gil;
    if (state_->options.format == BagFormat::Rosbag1) {
      state_->writer = py::module_::import("rosbags.rosbag1").attr("Writer")(state_->path);
    } else {
      py::object rosbag2 = py::module_::import("rosbags.rosbag2");
      py::object storage_plugin = rosbag2.attr("StoragePlugin").attr(
          state_->options.storage == StoragePlugin::Mcap ? "MCAP" : "SQLITE3");
      state_->writer = rosbag2.attr("Writer")(
          state_->path,
          py::arg("version") = state_->options.rosbag2_version,
          py::arg("storage_plugin") = storage_plugin);
    }
  } catch (const py::error_already_set& err) {
    throw to_error(err);
  }
}

Writer::~Writer() = default;
Writer::Writer(Writer&&) noexcept = default;
auto Writer::operator=(Writer&&) noexcept -> Writer& = default;

void Writer::open() {
  try {
    py::gil_scoped_acquire gil;
    state_->writer.attr("open")();
    state_->is_open = true;
  } catch (const py::error_already_set& err) {
    throw to_error(err);
  }
}

void Writer::close() {
  if (!state_->is_open) {
    return;
  }

  try {
    py::gil_scoped_acquire gil;
    state_->writer.attr("close")();
    state_->is_open = false;
  } catch (const py::error_already_set& err) {
    throw to_error(err);
  }
}

auto Writer::is_open() const noexcept -> bool {
  return state_ && state_->is_open;
}

auto Writer::add_connection(const Connection& connection) -> Connection {
  require_writer_open(*state_);
  const auto& source = require_connection_state(detail::connection_state(connection));
  if (source.bag_format != state_->options.format) {
    std::ostringstream stream;
    stream << "Cannot add raw " << format_name(source.bag_format) << " connection to "
           << format_name(state_->options.format) << " writer";
    throw Error(stream.str());
  }

  ConnectionSpec spec = source_spec_from_connection(connection);
  try {
    py::gil_scoped_acquire gil;
    py::object result;
    if (state_->options.format == BagFormat::Rosbag1) {
      validate_manual_connection(spec, state_->options.format);
      py::object ext = source.object.attr("ext");
      result = state_->writer.attr("add_connection")(
          spec.topic,
          spec.msgtype,
          py::arg("msgdef") = spec.msgdef_data,
          py::arg("md5sum") = spec.digest,
          py::arg("callerid") = ext.attr("callerid"),
          py::arg("latching") = ext.attr("latching"));
    } else {
      if (spec.digest.empty() && !spec.msgdef_data.empty()) {
        spec.digest = derive_rosbag2_digest(spec);
      }
      validate_manual_connection(spec, state_->options.format);
      py::object ext = source.object.attr("ext");
      result = state_->writer.attr("add_connection")(
          spec.topic,
          spec.msgtype,
          py::arg("msgdef") = spec.msgdef_data,
          py::arg("rihs01") = spec.digest,
          py::arg("serialization_format") = ext.attr("serialization_format"),
          py::arg("offered_qos_profiles") = ext.attr("offered_qos_profiles"));
    }
    Connection added = connection_from_python(state_->runtime, result, state_->options.format);
    state_->connections.push_back(added);
    return added;
  } catch (const py::error_already_set& err) {
    throw to_error(err);
  }
}

auto Writer::add_connection(const ConnectionSpec& spec) -> Connection {
  require_writer_open(*state_);
  validate_manual_connection(spec, state_->options.format);

  try {
    py::gil_scoped_acquire gil;
    py::object result;
    if (state_->options.format == BagFormat::Rosbag1) {
      py::object callerid = spec.callerid ? py::cast(*spec.callerid) : py::none();
      py::object latching = spec.latching ? py::cast(*spec.latching) : py::none();
      result = state_->writer.attr("add_connection")(
          spec.topic,
          spec.msgtype,
          py::arg("msgdef") = spec.msgdef_data,
          py::arg("md5sum") = spec.digest,
          py::arg("callerid") = callerid,
          py::arg("latching") = latching);
    } else {
      py::tuple empty_qos;
      result = state_->writer.attr("add_connection")(
          spec.topic,
          spec.msgtype,
          py::arg("msgdef") = spec.msgdef_data,
          py::arg("rihs01") = spec.digest,
          py::arg("serialization_format") = spec.serialization_format,
          py::arg("offered_qos_profiles") = empty_qos);
    }
    Connection added = connection_from_python(state_->runtime, result, state_->options.format);
    state_->connections.push_back(added);
    return added;
  } catch (const py::error_already_set& err) {
    throw to_error(err);
  }
}

auto Writer::add_connection(
    std::string topic,
    std::string msgtype,
    const Typestore& typestore,
    std::string serialization_format) -> Connection {
  require_writer_open(*state_);
  return add_connection(typestore.connection_spec(
      std::move(topic), std::move(msgtype), state_->options.format, std::move(serialization_format)));
}

void Writer::write(
    const Connection& connection,
    std::int64_t timestamp,
    const std::vector<std::uint8_t>& data) {
  require_writer_open(*state_);
  const auto& conn = require_connection_state(detail::connection_state(connection));

  try {
    py::gil_scoped_acquire gil;
    state_->writer.attr("write")(conn.object, timestamp, to_bytes(data));
  } catch (const py::error_already_set& err) {
    throw to_error(err);
  }
}

void Writer::write(
    const Connection& connection,
    std::int64_t timestamp,
    const TypedMessage& message,
    const Typestore& typestore) {
  write(connection, timestamp, typestore.serialize_raw(message, state_->options.format));
}

}  // namespace rosbags
