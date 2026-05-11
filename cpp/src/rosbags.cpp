// Copyright 2020-2026 Ternaris
// SPDX-License-Identifier: Apache-2.0

#include "rosbags/rosbags.hpp"

#include <algorithm>
#include <cstddef>
#include <exception>
#include <set>
#include <sstream>

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

}  // namespace detail

namespace {

auto require_connection_state(const std::shared_ptr<detail::ConnectionState>& state)
    -> const detail::ConnectionState& {
  if (!state) {
    throw Error("Invalid rosbags connection");
  }
  return *state;
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

}  // namespace rosbags
