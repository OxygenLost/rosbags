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

namespace detail {
struct RuntimeState;
struct ConnectionState;
struct MessageStreamState;
struct ReaderState;
struct WriterState;

auto connection_state(const Connection& connection)
    -> const std::shared_ptr<ConnectionState>&;
auto make_connection(std::shared_ptr<ConnectionState> state) -> Connection;
}  // namespace detail

class Error : public std::runtime_error {
 public:
  explicit Error(const std::string& message);
  explicit Error(const char* message);
};

struct RuntimeOptions {
  std::vector<std::string> python_paths;
};

class Runtime {
 public:
  explicit Runtime(RuntimeOptions options = {});
  ~Runtime();

  Runtime(const Runtime&) = delete;
  auto operator=(const Runtime&) -> Runtime& = delete;

  Runtime(Runtime&&) noexcept;
  auto operator=(Runtime&&) noexcept -> Runtime&;

 private:
  friend class Reader;
  friend class Writer;

  std::shared_ptr<detail::RuntimeState> state_;
};

enum class BagFormat {
  Rosbag1,
  Rosbag2,
};

enum class StoragePlugin {
  Sqlite3,
  Mcap,
};

enum class MessageDefinitionFormat {
  None = 0,
  Msg = 1,
  Idl = 2,
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
  std::optional<std::string> callerid;
  std::optional<int> latching;
};

struct Message {
  Connection connection;
  std::int64_t timestamp = 0;
  std::vector<std::uint8_t> data;
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
  Reader(Runtime& runtime, std::vector<std::string> paths);
  Reader(Runtime& runtime, std::initializer_list<std::string> paths);
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
};

class Writer {
 public:
  Writer(Runtime& runtime, std::string path, WriterOptions options = {});
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
  void write(
      const Connection& connection,
      std::int64_t timestamp,
      const std::vector<std::uint8_t>& data);

 private:
  std::shared_ptr<detail::WriterState> state_;
};

}  // namespace rosbags
