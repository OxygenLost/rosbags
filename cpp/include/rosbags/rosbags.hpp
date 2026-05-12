// Copyright 2020-2026 Ternaris
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <cstdint>
#include <initializer_list>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace rosbags {

class Connection;
class TypedMessage;
class TypedValue;
class Typestore;

namespace detail {
struct ConnectionState;
struct MessageStreamState;
struct ReaderState;
struct TypedMessageState;
struct TypedValueState;
struct TypestoreState;
struct WriterState;

auto connection_state(const Connection& connection)
    -> const std::shared_ptr<ConnectionState>&;
auto make_connection(std::shared_ptr<ConnectionState> state) -> Connection;
auto typed_message_state(const TypedMessage& message)
    -> const std::shared_ptr<TypedMessageState>&;
auto make_typed_message(std::shared_ptr<TypedMessageState> state) -> TypedMessage;
auto typestore_state(const Typestore& typestore)
    -> const std::shared_ptr<TypestoreState>&;
auto make_typestore(std::shared_ptr<TypestoreState> state) -> Typestore;
}  // namespace detail

class Error : public std::runtime_error {
 public:
  explicit Error(const std::string& message);
  explicit Error(const char* message);
};

enum class BagFormat {
  Rosbag1,
  Rosbag2,
};

enum class StoragePlugin {
  Sqlite3,
  Mcap,
};

enum class CompressionMode {
  None,
  File,
  Message,
  Storage,
};

enum class CompressionFormat {
  None,
  Bz2,
  Lz4,
  Zstd,
};

enum class MessageDefinitionFormat {
  None = 0,
  Msg = 1,
  Idl = 2,
};

enum class TypestorePreset {
  Empty,
  Latest,
  Ros1Noetic,
  Ros2Dashing,
  Ros2Eloquent,
  Ros2Foxy,
  Ros2Galactic,
  Ros2Humble,
  Ros2Iron,
  Ros2Jazzy,
  Ros2Kilted,
};

enum class TypedValueKind {
  None,
  Bool,
  Int,
  UInt,
  Float,
  String,
  Message,
  Array,
};

struct ReaderOptions {
  TypestorePreset default_typestore = TypestorePreset::Latest;
};

class Connection {
 public:
  Connection() = default;

  [[nodiscard]] auto valid() const noexcept -> bool;
  [[nodiscard]] auto id() const -> int;
  [[nodiscard]] auto topic() const -> const std::string&;
  [[nodiscard]] auto msgtype() const -> const std::string&;
  [[nodiscard]] auto msgdef_format() const -> MessageDefinitionFormat;
  [[nodiscard]] auto msgdef_data() const -> const std::string&;
  [[nodiscard]] auto digest() const -> const std::string&;
  [[nodiscard]] auto serialization_format() const -> const std::string&;
  [[nodiscard]] auto offered_qos_profiles() const -> const std::string&;
  [[nodiscard]] auto callerid() const -> const std::optional<std::string>&;
  [[nodiscard]] auto latching() const -> const std::optional<int>&;
  [[nodiscard]] auto msgcount() const -> std::int64_t;
  [[nodiscard]] auto bag_format() const -> BagFormat;

 private:
  friend class MessageStream;
  friend class Reader;
  friend class Writer;
  friend auto detail::connection_state(const Connection& connection)
      -> const std::shared_ptr<detail::ConnectionState>&;
  friend auto detail::make_connection(std::shared_ptr<detail::ConnectionState> state)
      -> Connection;

  explicit Connection(std::shared_ptr<detail::ConnectionState> state);

  std::shared_ptr<detail::ConnectionState> state_;
};

struct ConnectionSpec {
  std::string topic;
  std::string msgtype;
  MessageDefinitionFormat msgdef_format = MessageDefinitionFormat::Msg;
  std::string msgdef_data;
  std::string digest;
  std::string serialization_format = "cdr";
  std::string offered_qos_profiles;
  std::optional<std::string> callerid;
  std::optional<int> latching;
};

struct Message {
  Connection connection;
  std::int64_t timestamp = 0;
  std::vector<std::uint8_t> data;
};

class TypedValue {
 public:
  TypedValue();
  ~TypedValue();

  TypedValue(const TypedValue&);
  auto operator=(const TypedValue&) -> TypedValue&;

  TypedValue(TypedValue&&) noexcept;
  auto operator=(TypedValue&&) noexcept -> TypedValue&;

  [[nodiscard]] static auto from_bool(bool value) -> TypedValue;
  [[nodiscard]] static auto from_int(std::int64_t value) -> TypedValue;
  [[nodiscard]] static auto from_uint(std::uint64_t value) -> TypedValue;
  [[nodiscard]] static auto from_double(double value) -> TypedValue;
  [[nodiscard]] static auto from_string(std::string value) -> TypedValue;
  [[nodiscard]] static auto from_message(TypedMessage value) -> TypedValue;
  [[nodiscard]] static auto from_array(std::vector<TypedValue> values) -> TypedValue;

  [[nodiscard]] auto kind() const noexcept -> TypedValueKind;
  [[nodiscard]] auto as_bool() const -> bool;
  [[nodiscard]] auto as_int() const -> std::int64_t;
  [[nodiscard]] auto as_uint() const -> std::uint64_t;
  [[nodiscard]] auto as_double() const -> double;
  [[nodiscard]] auto as_string() const -> std::string;
  [[nodiscard]] auto as_message() const -> TypedMessage;
  [[nodiscard]] auto as_array() const -> std::vector<TypedValue>;

 private:
  explicit TypedValue(std::shared_ptr<detail::TypedValueState> state);

  std::shared_ptr<detail::TypedValueState> state_;
};

class TypedMessage {
 public:
  TypedMessage();
  ~TypedMessage();

  TypedMessage(const TypedMessage&);
  auto operator=(const TypedMessage&) -> TypedMessage&;

  TypedMessage(TypedMessage&&) noexcept;
  auto operator=(TypedMessage&&) noexcept -> TypedMessage&;

  [[nodiscard]] auto valid() const noexcept -> bool;
  [[nodiscard]] auto msgtype() const -> const std::string&;
  [[nodiscard]] auto field_names() const -> std::vector<std::string>;
  [[nodiscard]] auto fields() const -> std::vector<std::pair<std::string, TypedValue>>;
  [[nodiscard]] auto get(const std::string& field_name) const -> TypedValue;
  void set(const std::string& field_name, const TypedValue& value);

 private:
  friend class Reader;
  friend class Typestore;
  friend class TypedValue;
  friend class Writer;
  friend auto detail::typed_message_state(const TypedMessage& message)
      -> const std::shared_ptr<detail::TypedMessageState>&;
  friend auto detail::make_typed_message(std::shared_ptr<detail::TypedMessageState> state)
      -> TypedMessage;

  explicit TypedMessage(std::shared_ptr<detail::TypedMessageState> state);

  std::shared_ptr<detail::TypedMessageState> state_;
};

class Typestore {
 public:
  explicit Typestore(TypestorePreset preset = TypestorePreset::Latest);
  ~Typestore();

  Typestore(const Typestore&);
  auto operator=(const Typestore&) -> Typestore&;

  Typestore(Typestore&&) noexcept;
  auto operator=(Typestore&&) noexcept -> Typestore&;

  void register_msg(const std::string& msgtype, const std::string& msgdef);
  void register_idl(const std::string& idl_text);

  [[nodiscard]] auto create(
      const std::string& msgtype,
      std::vector<std::pair<std::string, TypedValue>> fields = {}) const
      -> TypedMessage;
  [[nodiscard]] auto deserialize_cdr(
      const std::vector<std::uint8_t>& data,
      const std::string& msgtype) const -> TypedMessage;
  [[nodiscard]] auto serialize_cdr(
      const TypedMessage& message,
      bool little_endian = true) const -> std::vector<std::uint8_t>;
  [[nodiscard]] auto deserialize_ros1(
      const std::vector<std::uint8_t>& data,
      const std::string& msgtype) const -> TypedMessage;
  [[nodiscard]] auto serialize_ros1(const TypedMessage& message) const
      -> std::vector<std::uint8_t>;
  [[nodiscard]] auto deserialize_raw(
      const std::vector<std::uint8_t>& data,
      const std::string& msgtype,
      BagFormat format) const -> TypedMessage;
  [[nodiscard]] auto serialize_raw(const TypedMessage& message, BagFormat format) const
      -> std::vector<std::uint8_t>;
  [[nodiscard]] auto ros1_to_cdr(
      const std::vector<std::uint8_t>& data,
      const std::string& msgtype) const -> std::vector<std::uint8_t>;
  [[nodiscard]] auto cdr_to_ros1(
      const std::vector<std::uint8_t>& data,
      const std::string& msgtype) const -> std::vector<std::uint8_t>;
  [[nodiscard]] auto connection_spec(
      std::string topic,
      std::string msgtype,
      BagFormat format,
      std::string serialization_format = "cdr") const -> ConnectionSpec;

 private:
  friend class Reader;
  friend class Writer;
  friend auto detail::typestore_state(const Typestore& typestore)
      -> const std::shared_ptr<detail::TypestoreState>&;
  friend auto detail::make_typestore(std::shared_ptr<detail::TypestoreState> state)
      -> Typestore;

  explicit Typestore(std::shared_ptr<detail::TypestoreState> state);

  std::shared_ptr<detail::TypestoreState> state_;
};

struct ReaderMessageOptions {
  std::vector<int> connection_ids;
  std::optional<std::int64_t> start_time;
  std::optional<std::int64_t> stop_time;
};

class MessageStream {
 public:
  MessageStream();
  ~MessageStream();

  MessageStream(const MessageStream&) = delete;
  auto operator=(const MessageStream&) -> MessageStream& = delete;

  MessageStream(MessageStream&&) noexcept;
  auto operator=(MessageStream&&) noexcept -> MessageStream&;

  [[nodiscard]] auto next(Message& message) -> bool;

 private:
  friend class Reader;

  explicit MessageStream(std::shared_ptr<detail::MessageStreamState> state);

  std::shared_ptr<detail::MessageStreamState> state_;
};

class Reader {
 public:
  explicit Reader(std::vector<std::string> paths, ReaderOptions options = {});
  Reader(std::initializer_list<std::string> paths, ReaderOptions options = {});
  explicit Reader(std::string path, ReaderOptions options = {});
  ~Reader();

  Reader(const Reader&) = delete;
  auto operator=(const Reader&) -> Reader& = delete;

  Reader(Reader&&) noexcept;
  auto operator=(Reader&&) noexcept -> Reader&;

  void open();
  void close();

  [[nodiscard]] auto is_open() const noexcept -> bool;
  [[nodiscard]] auto bag_format() const -> BagFormat;
  [[nodiscard]] auto connections() const -> std::vector<Connection>;
  [[nodiscard]] auto messages(ReaderMessageOptions options = {}) -> MessageStream;
  [[nodiscard]] auto typestore() const -> Typestore;
  [[nodiscard]] auto deserialize(const Message& message) const -> TypedMessage;
  [[nodiscard]] auto duration() const -> std::int64_t;
  [[nodiscard]] auto start_time() const -> std::int64_t;
  [[nodiscard]] auto end_time() const -> std::int64_t;
  [[nodiscard]] auto message_count() const -> std::int64_t;

 private:
  std::shared_ptr<detail::ReaderState> state_;
};

struct WriterOptions {
  BagFormat format = BagFormat::Rosbag2;
  int rosbag2_version = 9;
  StoragePlugin storage = StoragePlugin::Sqlite3;
  CompressionMode compression_mode = CompressionMode::None;
  CompressionFormat compression_format = CompressionFormat::None;
  std::size_t chunk_threshold = 1U << 20U;
};

class Writer {
 public:
  explicit Writer(std::string path, WriterOptions options = {});
  ~Writer();

  Writer(const Writer&) = delete;
  auto operator=(const Writer&) -> Writer& = delete;

  Writer(Writer&&) noexcept;
  auto operator=(Writer&&) noexcept -> Writer&;

  void open();
  void close();

  [[nodiscard]] auto is_open() const noexcept -> bool;
  [[nodiscard]] auto add_connection(const Connection& connection) -> Connection;
  [[nodiscard]] auto add_connection(const ConnectionSpec& spec) -> Connection;
  [[nodiscard]] auto add_connection(
      std::string topic,
      std::string msgtype,
      const Typestore& typestore,
      std::string serialization_format = "cdr") -> Connection;
  void write(
      const Connection& connection,
      std::int64_t timestamp,
      const std::vector<std::uint8_t>& data);
  void write(
      const Connection& connection,
      std::int64_t timestamp,
      const TypedMessage& message,
      const Typestore& typestore);

 private:
  std::shared_ptr<detail::WriterState> state_;
};

}  // namespace rosbags
