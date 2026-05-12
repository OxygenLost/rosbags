// Copyright 2020-2026 Ternaris
// SPDX-License-Identifier: Apache-2.0

#include "rosbags/rosbags.hpp"

#include <bzlib.h>
#include <lz4frame.h>
#include <openssl/evp.h>
#include <sqlite3.h>
#include <yaml-cpp/yaml.h>
#include <zstd.h>

#include <algorithm>
#include <array>
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cmath>
#include <cstring>
#include <filesystem>
#include <functional>
#include <fstream>
#include <iomanip>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <regex>
#include <set>
#include <sstream>
#include <unordered_map>
#include <utility>

namespace fs = std::filesystem;

namespace rosbags {
namespace {

constexpr std::int64_t kMaxTime = std::numeric_limits<std::int64_t>::max();

enum class NodeKind {
  Base,
  Name,
  Array,
  Sequence,
};

struct FieldDesc {
  NodeKind kind = NodeKind::Base;
  std::string value;
  int bound = 0;
  std::shared_ptr<FieldDesc> sub;
};

struct ConstDef {
  std::string type;
  std::string name;
  std::string value;
};

struct FieldDef {
  std::string name;
  FieldDesc desc;
};

struct TypeDef {
  std::vector<ConstDef> constants;
  std::vector<FieldDef> fields;
};

struct IndexEntry {
  std::int64_t timestamp = 0;
  std::uint64_t chunk_pos = 0;
  std::uint32_t offset = 0;
};

struct Ros1Chunk {
  std::uint32_t uncompressed_size = 0;
  std::uint64_t data_pos = 0;
  std::uint32_t data_size = 0;
  std::string compression = "none";
};

struct Ros1ChunkInfo {
  std::uint64_t pos = 0;
  std::int64_t start_time = kMaxTime;
  std::int64_t end_time = 0;
  std::map<int, int> counts;
};

struct Ros1MessageHeader {
  std::uint8_t op = 0;
  int connection_id = -1;
  std::int64_t timestamp = 0;
};

struct NativeMessage {
  Connection connection;
  std::int64_t timestamp = 0;
  std::vector<std::uint8_t> data;
};

auto trim(std::string value) -> std::string {
  auto first = value.begin();
  while (first != value.end() && std::isspace(static_cast<unsigned char>(*first)) != 0) {
    ++first;
  }
  auto last = value.end();
  while (last != first && std::isspace(static_cast<unsigned char>(*(last - 1))) != 0) {
    --last;
  }
  return {first, last};
}

auto split_words(const std::string& text) -> std::vector<std::string> {
  std::istringstream stream(text);
  std::vector<std::string> result;
  std::string word;
  while (stream >> word) {
    result.push_back(word);
  }
  return result;
}

auto starts_with(const std::string& text, const std::string& prefix) -> bool {
  return text.size() >= prefix.size() &&
         std::equal(prefix.begin(), prefix.end(), text.begin());
}

auto ends_with(const std::string& text, const std::string& suffix) -> bool {
  return text.size() >= suffix.size() &&
         std::equal(suffix.rbegin(), suffix.rend(), text.rbegin());
}

auto hex_digest(const unsigned char* data, std::size_t size) -> std::string {
  std::ostringstream stream;
  stream << std::hex << std::setfill('0');
  for (std::size_t idx = 0; idx < size; ++idx) {
    stream << std::setw(2) << static_cast<int>(data[idx]);
  }
  return stream.str();
}

auto digest_hex(const EVP_MD* algorithm, const std::string& text) -> std::string {
  unsigned char digest[EVP_MAX_MD_SIZE];
  unsigned int digest_size = 0;
  if (EVP_Digest(
          text.data(),
          text.size(),
          digest,
          &digest_size,
          algorithm,
          nullptr) != 1) {
    throw Error("Could not compute message digest");
  }
  return hex_digest(digest, digest_size);
}

auto md5_hex(const std::string& text) -> std::string {
  return digest_hex(EVP_md5(), text);
}

auto sha256_hex(const std::string& text) -> std::string {
  return digest_hex(EVP_sha256(), text);
}

auto normalize_msgtype(std::string name) -> std::string {
  if (name == "time") {
    return "builtin_interfaces/msg/Time";
  }
  if (name == "duration") {
    return "builtin_interfaces/msg/Duration";
  }
  if (name == "Header") {
    return "std_msgs/msg/Header";
  }
  if (name.find('/') == std::string::npos) {
    return name;
  }
  if (name.find("/msg/") != std::string::npos || name.find("/action/") != std::string::npos) {
    return name;
  }
  const auto pos = name.rfind('/');
  if (pos == std::string::npos) {
    return name;
  }
  return name.substr(0, pos) + "/msg/" + name.substr(pos + 1);
}

auto normalize_fieldtype(const std::string& owner, const std::string& name) -> std::string {
  if (name == "time") {
    return "builtin_interfaces/msg/Time";
  }
  if (name == "duration") {
    return "builtin_interfaces/msg/Duration";
  }
  if (name == "Header") {
    return "std_msgs/msg/Header";
  }
  if (name.find('/') == std::string::npos) {
    const auto pos = owner.rfind("/msg/");
    if (pos == std::string::npos) {
      return name;
    }
    return owner.substr(0, pos + 5) + name;
  }
  return normalize_msgtype(name);
}

auto denormalize_msgtype(const std::string& name) -> std::string {
  const auto marker = name.find("/msg/");
  if (marker == std::string::npos) {
    return name;
  }
  return name.substr(0, marker) + "/" + name.substr(marker + 5);
}

auto is_base_type(const std::string& name) -> bool {
  static const std::set<std::string> bases = {
      "bool",   "byte",   "char",   "int8",   "uint8",  "int16",
      "uint16", "int32",  "uint32", "int64",  "uint64", "float32",
      "float64", "float128", "string"};
  return bases.count(name) != 0;
}

auto base_size(const std::string& name) -> std::size_t {
  if (name == "bool" || name == "byte" || name == "char" || name == "int8" ||
      name == "uint8") {
    return 1;
  }
  if (name == "int16" || name == "uint16") {
    return 2;
  }
  if (name == "int32" || name == "uint32" || name == "float32") {
    return 4;
  }
  if (name == "int64" || name == "uint64" || name == "float64") {
    return 8;
  }
  if (name == "float128") {
    return 16;
  }
  if (name == "string") {
    return 4;
  }
  throw Error("Unknown base type '" + name + "'");
}

auto base_is_unsigned(const std::string& name) -> bool {
  return name == "byte" || name == "char" || name == "uint8" || name == "uint16" ||
         name == "uint32" || name == "uint64";
}

auto read_file(const fs::path& path) -> std::vector<std::uint8_t> {
  std::ifstream stream(path, std::ios::binary);
  if (!stream) {
    throw Error("Could not open file '" + path.string() + "'");
  }
  stream.seekg(0, std::ios::end);
  const auto size = stream.tellg();
  stream.seekg(0, std::ios::beg);
  std::vector<std::uint8_t> data(static_cast<std::size_t>(size));
  if (!data.empty()) {
    stream.read(reinterpret_cast<char*>(data.data()), static_cast<std::streamsize>(data.size()));
  }
  return data;
}

void write_file(const fs::path& path, const std::vector<std::uint8_t>& data) {
  std::ofstream stream(path, std::ios::binary | std::ios::trunc);
  if (!stream) {
    throw Error("Could not write file '" + path.string() + "'");
  }
  if (!data.empty()) {
    stream.write(reinterpret_cast<const char*>(data.data()), static_cast<std::streamsize>(data.size()));
  }
}

template <typename T>
auto read_le(const std::vector<std::uint8_t>& data, std::size_t& pos) -> T {
  if (pos + sizeof(T) > data.size()) {
    throw Error("Unexpected end of byte stream");
  }
  T result{};
  std::memcpy(&result, data.data() + pos, sizeof(T));
  pos += sizeof(T);
  return result;
}

template <typename T>
void append_le(std::vector<std::uint8_t>& data, T value) {
  const auto* ptr = reinterpret_cast<const std::uint8_t*>(&value);
  data.insert(data.end(), ptr, ptr + sizeof(T));
}

auto host_is_little_endian() -> bool {
  const std::uint16_t value = 1;
  return *reinterpret_cast<const std::uint8_t*>(&value) == 1;
}

template <typename T>
void append_endian(std::vector<std::uint8_t>& data, T value, bool little_endian) {
  std::array<std::uint8_t, sizeof(T)> bytes{};
  std::memcpy(bytes.data(), &value, sizeof(T));
  if (little_endian != host_is_little_endian()) {
    std::reverse(bytes.begin(), bytes.end());
  }
  data.insert(data.end(), bytes.begin(), bytes.end());
}

template <typename T>
auto read_endian(const std::vector<std::uint8_t>& data, std::size_t& pos, bool little_endian) -> T {
  if (pos + sizeof(T) > data.size()) {
    throw Error("Unexpected end of byte stream");
  }
  std::array<std::uint8_t, sizeof(T)> bytes{};
  std::memcpy(bytes.data(), data.data() + pos, sizeof(T));
  pos += sizeof(T);
  if (little_endian != host_is_little_endian()) {
    std::reverse(bytes.begin(), bytes.end());
  }
  T result{};
  std::memcpy(&result, bytes.data(), sizeof(T));
  return result;
}

template <typename T>
void write_le(std::ostream& stream, T value) {
  stream.write(reinterpret_cast<const char*>(&value), sizeof(T));
}

template <typename T>
auto read_stream_le(std::istream& stream) -> T {
  T value{};
  stream.read(reinterpret_cast<char*>(&value), sizeof(T));
  if (!stream) {
    throw Error("Unexpected end of file");
  }
  return value;
}

auto read_u32_at(const std::vector<std::uint8_t>& data, std::size_t pos) -> std::uint32_t {
  if (pos + 4 > data.size()) {
    throw Error("Unexpected end of byte stream");
  }
  std::uint32_t value{};
  std::memcpy(&value, data.data() + pos, 4);
  return value;
}

auto read_u64_at(const std::vector<std::uint8_t>& data, std::size_t pos) -> std::uint64_t {
  if (pos + 8 > data.size()) {
    throw Error("Unexpected end of byte stream");
  }
  std::uint64_t value{};
  std::memcpy(&value, data.data() + pos, 8);
  return value;
}

auto read_string_raw(const std::vector<std::uint8_t>& data, std::size_t& pos) -> std::string {
  const auto size = read_le<std::uint32_t>(data, pos);
  if (pos + size > data.size()) {
    throw Error("Unexpected end of byte stream");
  }
  std::string result(reinterpret_cast<const char*>(data.data() + pos), size);
  pos += size;
  return result;
}

void append_string_raw(std::vector<std::uint8_t>& data, const std::string& value) {
  append_le<std::uint32_t>(data, static_cast<std::uint32_t>(value.size()));
  data.insert(data.end(), value.begin(), value.end());
}

auto serialize_time(std::int64_t timestamp) -> std::array<std::uint8_t, 8> {
  const auto sec = static_cast<std::uint32_t>(timestamp / 1000000000LL);
  const auto nsec = static_cast<std::uint32_t>(timestamp % 1000000000LL);
  std::array<std::uint8_t, 8> result{};
  std::memcpy(result.data(), &sec, 4);
  std::memcpy(result.data() + 4, &nsec, 4);
  return result;
}

auto deserialize_time(const std::vector<std::uint8_t>& value) -> std::int64_t {
  if (value.size() != 8) {
    throw Error("Could not read time field");
  }
  std::uint32_t sec{};
  std::uint32_t nsec{};
  std::memcpy(&sec, value.data(), 4);
  std::memcpy(&nsec, value.data() + 4, 4);
  return static_cast<std::int64_t>(sec) * 1000000000LL + nsec;
}

auto zstd_compress(const std::vector<std::uint8_t>& input) -> std::vector<std::uint8_t> {
  std::vector<std::uint8_t> output(ZSTD_compressBound(input.size()));
  const auto size = ZSTD_compress(output.data(), output.size(), input.data(), input.size(), 3);
  if (ZSTD_isError(size) != 0U) {
    throw Error(std::string("zstd compression failed: ") + ZSTD_getErrorName(size));
  }
  output.resize(size);
  return output;
}

auto zstd_decompress(const std::vector<std::uint8_t>& input) -> std::vector<std::uint8_t> {
  const auto expected = ZSTD_getFrameContentSize(input.data(), input.size());
  if (expected == ZSTD_CONTENTSIZE_ERROR || expected == ZSTD_CONTENTSIZE_UNKNOWN) {
    throw Error("zstd frame size is unavailable");
  }
  std::vector<std::uint8_t> output(static_cast<std::size_t>(expected));
  const auto size = ZSTD_decompress(output.data(), output.size(), input.data(), input.size());
  if (ZSTD_isError(size) != 0U) {
    throw Error(std::string("zstd decompression failed: ") + ZSTD_getErrorName(size));
  }
  output.resize(size);
  return output;
}

auto bz2_compress(const std::vector<std::uint8_t>& input) -> std::vector<std::uint8_t> {
  unsigned int dest_len = static_cast<unsigned int>(input.size() + input.size() / 100 + 601);
  std::vector<std::uint8_t> output(dest_len);
  const int err = BZ2_bzBuffToBuffCompress(
      reinterpret_cast<char*>(output.data()),
      &dest_len,
      const_cast<char*>(reinterpret_cast<const char*>(input.data())),
      static_cast<unsigned int>(input.size()),
      9,
      0,
      30);
  if (err != BZ_OK) {
    throw Error("bzip2 compression failed");
  }
  output.resize(dest_len);
  return output;
}

auto bz2_decompress(const std::vector<std::uint8_t>& input, std::size_t expected)
    -> std::vector<std::uint8_t> {
  unsigned int dest_len = static_cast<unsigned int>(expected);
  std::vector<std::uint8_t> output(dest_len);
  const int err = BZ2_bzBuffToBuffDecompress(
      reinterpret_cast<char*>(output.data()),
      &dest_len,
      const_cast<char*>(reinterpret_cast<const char*>(input.data())),
      static_cast<unsigned int>(input.size()),
      0,
      0);
  if (err != BZ_OK) {
    throw Error("bzip2 decompression failed");
  }
  output.resize(dest_len);
  return output;
}

auto lz4_compress(const std::vector<std::uint8_t>& input) -> std::vector<std::uint8_t> {
  const auto bound = LZ4F_compressFrameBound(input.size(), nullptr);
  std::vector<std::uint8_t> output(bound);
  const auto size = LZ4F_compressFrame(output.data(), output.size(), input.data(), input.size(), nullptr);
  if (LZ4F_isError(size) != 0U) {
    throw Error(std::string("lz4 compression failed: ") + LZ4F_getErrorName(size));
  }
  output.resize(size);
  return output;
}

auto lz4_decompress(const std::vector<std::uint8_t>& input, std::size_t expected)
    -> std::vector<std::uint8_t> {
  LZ4F_dctx* ctx = nullptr;
  if (LZ4F_isError(LZ4F_createDecompressionContext(&ctx, LZ4F_VERSION)) != 0U) {
    throw Error("Could not create lz4 decompressor");
  }
  std::vector<std::uint8_t> output(expected);
  std::size_t src_pos = 0;
  std::size_t dst_pos = 0;
  while (src_pos < input.size()) {
    std::size_t src_size = input.size() - src_pos;
    std::size_t dst_size = output.size() - dst_pos;
    const auto code = LZ4F_decompress(
        ctx,
        output.data() + dst_pos,
        &dst_size,
        input.data() + src_pos,
        &src_size,
        nullptr);
    if (LZ4F_isError(code) != 0U) {
      LZ4F_freeDecompressionContext(ctx);
      throw Error(std::string("lz4 decompression failed: ") + LZ4F_getErrorName(code));
    }
    src_pos += src_size;
    dst_pos += dst_size;
    if (code == 0) {
      break;
    }
  }
  LZ4F_freeDecompressionContext(ctx);
  output.resize(dst_pos);
  return output;
}

auto decompress_named(
    const std::string& compression,
    const std::vector<std::uint8_t>& input,
    std::size_t expected) -> std::vector<std::uint8_t> {
  if (compression.empty() || compression == "none") {
    return input;
  }
  if (compression == "bz2") {
    return bz2_decompress(input, expected);
  }
  if (compression == "lz4") {
    return lz4_decompress(input, expected);
  }
  if (compression == "zstd") {
    return zstd_decompress(input);
  }
  throw Error("Compression '" + compression + "' is not supported");
}

auto compress_named(const std::string& compression, const std::vector<std::uint8_t>& input)
    -> std::vector<std::uint8_t> {
  if (compression.empty() || compression == "none") {
    return input;
  }
  if (compression == "bz2") {
    return bz2_compress(input);
  }
  if (compression == "lz4") {
    return lz4_compress(input);
  }
  if (compression == "zstd") {
    return zstd_compress(input);
  }
  throw Error("Compression '" + compression + "' is not supported");
}

auto compression_name(CompressionFormat format, BagFormat bag_format) -> std::string {
  switch (format) {
    case CompressionFormat::None:
      return bag_format == BagFormat::Rosbag1 ? "none" : "";
    case CompressionFormat::Bz2:
      return "bz2";
    case CompressionFormat::Lz4:
      return "lz4";
    case CompressionFormat::Zstd:
      return "zstd";
  }
  return bag_format == BagFormat::Rosbag1 ? "none" : "";
}

struct RecordHeader {
  std::map<std::string, std::vector<std::uint8_t>> fields;

  auto has(const std::string& key) const -> bool {
    return fields.find(key) != fields.end();
  }

  auto string_value(const std::string& key) const -> std::string {
    auto it = fields.find(key);
    if (it == fields.end()) {
      throw Error("Could not read string field '" + key + "'");
    }
    return {reinterpret_cast<const char*>(it->second.data()), it->second.size()};
  }

  auto uint8_value(const std::string& key) const -> std::uint8_t {
    auto it = fields.find(key);
    if (it == fields.end() || it->second.size() != 1) {
      throw Error("Could not read uint8 field '" + key + "'");
    }
    return it->second[0];
  }

  auto uint32_value(const std::string& key) const -> std::uint32_t {
    auto it = fields.find(key);
    if (it == fields.end() || it->second.size() != 4) {
      throw Error("Could not read uint32 field '" + key + "'");
    }
    std::uint32_t value{};
    std::memcpy(&value, it->second.data(), 4);
    return value;
  }

  auto uint64_value(const std::string& key) const -> std::uint64_t {
    auto it = fields.find(key);
    if (it == fields.end() || it->second.size() != 8) {
      throw Error("Could not read uint64 field '" + key + "'");
    }
    std::uint64_t value{};
    std::memcpy(&value, it->second.data(), 8);
    return value;
  }

  auto time_value(const std::string& key) const -> std::int64_t {
    auto it = fields.find(key);
    if (it == fields.end()) {
      throw Error("Could not read time field '" + key + "'");
    }
    return deserialize_time(it->second);
  }
};

void set_field(RecordHeader& header, std::string key, std::vector<std::uint8_t> value) {
  header.fields[std::move(key)] = std::move(value);
}

void set_string(RecordHeader& header, const std::string& key, const std::string& value) {
  set_field(header, key, {value.begin(), value.end()});
}

void set_u8(RecordHeader& header, const std::string& key, std::uint8_t value) {
  set_field(header, key, {value});
}

void set_u32(RecordHeader& header, const std::string& key, std::uint32_t value) {
  std::vector<std::uint8_t> data;
  append_le<std::uint32_t>(data, value);
  set_field(header, key, std::move(data));
}

void set_u64(RecordHeader& header, const std::string& key, std::uint64_t value) {
  std::vector<std::uint8_t> data;
  append_le<std::uint64_t>(data, value);
  set_field(header, key, std::move(data));
}

void set_time(RecordHeader& header, const std::string& key, std::int64_t value) {
  const auto packed = serialize_time(value);
  set_field(header, key, {packed.begin(), packed.end()});
}

auto parse_header_bytes(const std::vector<std::uint8_t>& raw) -> RecordHeader {
  RecordHeader header;
  std::size_t pos = 0;
  while (pos < raw.size()) {
    const auto field_size = read_le<std::uint32_t>(raw, pos);
    if (pos + field_size > raw.size()) {
      throw Error("Header field exceeds record size");
    }
    auto* begin = raw.data() + pos;
    auto* end = begin + field_size;
    auto* eq = std::find(begin, end, static_cast<std::uint8_t>('='));
    if (eq == end) {
      throw Error("Header field is missing '='");
    }
    std::string key(reinterpret_cast<const char*>(begin), eq - begin);
    header.fields[key] = std::vector<std::uint8_t>(eq + 1, end);
    pos += field_size;
  }
  return header;
}

auto read_header(std::istream& stream, std::optional<int> expected_op = {}) -> RecordHeader {
  const auto size = read_stream_le<std::uint32_t>(stream);
  std::vector<std::uint8_t> raw(size);
  if (size != 0) {
    stream.read(reinterpret_cast<char*>(raw.data()), size);
  }
  if (!stream) {
    throw Error("Could not read record header");
  }
  RecordHeader header = parse_header_bytes(raw);
  if (expected_op && header.uint8_value("op") != *expected_op) {
    throw Error("Unexpected record type");
  }
  return header;
}

auto read_header(const std::vector<std::uint8_t>& data, std::size_t& pos, std::optional<int> expected_op = {})
    -> RecordHeader {
  const auto size = read_le<std::uint32_t>(data, pos);
  if (pos + size > data.size()) {
    throw Error("Could not read record header");
  }
  std::vector<std::uint8_t> raw(data.begin() + static_cast<std::ptrdiff_t>(pos),
                                data.begin() + static_cast<std::ptrdiff_t>(pos + size));
  pos += size;
  RecordHeader header = parse_header_bytes(raw);
  if (expected_op && header.uint8_value("op") != *expected_op) {
    throw Error("Unexpected record type");
  }
  return header;
}

auto read_ros1_message_header(const std::vector<std::uint8_t>& data, std::size_t& pos)
    -> Ros1MessageHeader {
  const auto header_size = read_le<std::uint32_t>(data, pos);
  if (pos + header_size > data.size()) {
    throw Error("Could not read record header");
  }
  const auto end = pos + header_size;
  Ros1MessageHeader header;
  while (pos < end) {
    const auto field_size = read_le<std::uint32_t>(data, pos);
    if (pos + field_size > end) {
      throw Error("Header field exceeds record size");
    }
    const auto* begin = data.data() + pos;
    const auto* field_end = begin + field_size;
    const auto* eq = std::find(begin, field_end, static_cast<std::uint8_t>('='));
    if (eq == field_end) {
      throw Error("Header field is missing '='");
    }
    const auto key_size = static_cast<std::size_t>(eq - begin);
    const auto* value = eq + 1;
    const auto value_size = static_cast<std::size_t>(field_end - value);
    if (key_size == 2 && std::memcmp(begin, "op", 2) == 0 && value_size == 1) {
      header.op = *value;
    } else if (key_size == 4 && std::memcmp(begin, "conn", 4) == 0 && value_size == 4) {
      std::uint32_t cid{};
      std::memcpy(&cid, value, sizeof(cid));
      header.connection_id = static_cast<int>(cid);
    } else if (key_size == 4 && std::memcmp(begin, "time", 4) == 0 && value_size == 8) {
      std::uint32_t sec{};
      std::uint32_t nsec{};
      std::memcpy(&sec, value, sizeof(sec));
      std::memcpy(&nsec, value + sizeof(sec), sizeof(nsec));
      header.timestamp = static_cast<std::int64_t>(sec) * 1000000000LL + nsec;
    }
    pos += field_size;
  }
  return header;
}

auto header_payload(const RecordHeader& header, std::optional<int> opcode = {}) -> std::vector<std::uint8_t> {
  std::vector<std::uint8_t> data;
  if (opcode) {
    std::vector<std::uint8_t> value = {static_cast<std::uint8_t>(*opcode)};
    std::string field = "op=";
    std::vector<std::uint8_t> raw(field.begin(), field.end());
    raw.insert(raw.end(), value.begin(), value.end());
    append_le<std::uint32_t>(data, static_cast<std::uint32_t>(raw.size()));
    data.insert(data.end(), raw.begin(), raw.end());
  }
  for (const auto& item : header.fields) {
    if (item.first == "op") {
      continue;
    }
    std::string prefix = item.first + "=";
    std::vector<std::uint8_t> raw(prefix.begin(), prefix.end());
    raw.insert(raw.end(), item.second.begin(), item.second.end());
    append_le<std::uint32_t>(data, static_cast<std::uint32_t>(raw.size()));
    data.insert(data.end(), raw.begin(), raw.end());
  }
  return data;
}

auto write_header(std::ostream& stream, const RecordHeader& header, std::optional<int> opcode = {})
    -> std::size_t {
  std::vector<std::uint8_t> data = header_payload(header, opcode);
  write_le<std::uint32_t>(stream, static_cast<std::uint32_t>(data.size()));
  if (!data.empty()) {
    stream.write(reinterpret_cast<const char*>(data.data()), static_cast<std::streamsize>(data.size()));
  }
  return data.size() + 4;
}

void append_header(std::vector<std::uint8_t>& out, const RecordHeader& header, std::optional<int> opcode = {}) {
  std::vector<std::uint8_t> data = header_payload(header, opcode);
  append_le<std::uint32_t>(out, static_cast<std::uint32_t>(data.size()));
  out.insert(out.end(), data.begin(), data.end());
}

void append_sized(std::vector<std::uint8_t>& out, const std::vector<std::uint8_t>& data) {
  append_le<std::uint32_t>(out, static_cast<std::uint32_t>(data.size()));
  out.insert(out.end(), data.begin(), data.end());
}

auto field_alignment(const FieldDesc& desc, const std::unordered_map<std::string, TypeDef>& types)
    -> std::size_t {
  switch (desc.kind) {
    case NodeKind::Base:
      return std::min<std::size_t>(base_size(desc.value), 8);
    case NodeKind::Name: {
      auto it = types.find(desc.value);
      if (it == types.end() || it->second.fields.empty()) {
        return 1;
      }
      std::size_t result = 1;
      for (const auto& field : it->second.fields) {
        result = std::max(result, field_alignment(field.desc, types));
      }
      return result;
    }
    case NodeKind::Array:
      return field_alignment(*desc.sub, types);
    case NodeKind::Sequence:
      return 4;
  }
  return 1;
}

void align_vector(std::vector<std::uint8_t>& data, std::size_t alignment) {
  if (alignment <= 1) {
    return;
  }
  const auto pad = (alignment - (data.size() % alignment)) % alignment;
  data.insert(data.end(), pad, 0);
}

void align_pos(std::size_t& pos, std::size_t alignment, std::size_t limit) {
  if (alignment <= 1) {
    return;
  }
  pos = (pos + alignment - 1) & ~(alignment - 1);
  if (pos > limit) {
    throw Error("CDR alignment moved past end of data");
  }
}

auto parse_type_token(const std::string& owner, const std::string& token) -> FieldDesc {
  std::string base = token;
  std::vector<std::string> suffixes;
  while (!base.empty() && base.back() == ']') {
    const auto left = base.rfind('[');
    if (left == std::string::npos) {
      break;
    }
    suffixes.push_back(base.substr(left));
    base = base.substr(0, left);
  }

  FieldDesc desc;
  if (is_base_type(base)) {
    desc.kind = NodeKind::Base;
    desc.value = base;
  } else if (starts_with(base, "string<=")) {
    desc.kind = NodeKind::Base;
    desc.value = "string";
    desc.bound = std::stoi(base.substr(8));
  } else {
    desc.kind = NodeKind::Name;
    desc.value = normalize_fieldtype(owner, base);
  }

  for (const auto& suffix : suffixes) {
    FieldDesc parent;
    parent.sub = std::make_shared<FieldDesc>(desc);
    if (suffix == "[]") {
      parent.kind = NodeKind::Sequence;
      parent.bound = 0;
    } else if (starts_with(suffix, "[<=")) {
      parent.kind = NodeKind::Sequence;
      parent.bound = std::stoi(suffix.substr(3, suffix.size() - 4));
    } else {
      parent.kind = NodeKind::Array;
      parent.bound = std::stoi(suffix.substr(1, suffix.size() - 2));
    }
    desc = std::move(parent);
  }
  return desc;
}

void parse_msg_body(
    std::unordered_map<std::string, TypeDef>& types,
    const std::string& msgtype,
    const std::string& body) {
  TypeDef def;
  std::istringstream stream(body);
  std::string line;
  while (std::getline(stream, line)) {
    const auto comment = line.find('#');
    if (comment != std::string::npos) {
      line = line.substr(0, comment);
    }
    line = trim(line);
    if (line.empty()) {
      continue;
    }

    const auto eq = line.find('=');
    if (eq != std::string::npos) {
      const auto left = trim(line.substr(0, eq));
      const auto right = trim(line.substr(eq + 1));
      const auto words = split_words(left);
      if (words.size() >= 2) {
        def.constants.push_back({words[0], words[1], right});
        continue;
      }
    }

    const auto words = split_words(line);
    if (words.size() < 2) {
      continue;
    }
    def.fields.push_back({words[1], parse_type_token(msgtype, words[0])});
  }
  types[normalize_msgtype(msgtype)] = std::move(def);
}

void parse_msg_definition(
    std::unordered_map<std::string, TypeDef>& types,
    const std::string& root_type,
    const std::string& text) {
  const std::string sep(80, '=');
  std::size_t pos = 0;
  std::string root_body;
  std::vector<std::pair<std::string, std::string>> sections;
  const auto first_sep = text.find(sep);
  if (first_sep == std::string::npos) {
    parse_msg_body(types, root_type, text);
    return;
  }

  root_body = text.substr(0, first_sep);
  sections.emplace_back(normalize_msgtype(root_type), root_body);
  pos = first_sep;
  while (pos != std::string::npos && pos < text.size()) {
    pos += sep.size();
    if (pos < text.size() && text[pos] == '\r') {
      ++pos;
    }
    if (pos < text.size() && text[pos] == '\n') {
      ++pos;
    }
    const auto line_end = text.find('\n', pos);
    if (line_end == std::string::npos) {
      break;
    }
    std::string header = trim(text.substr(pos, line_end - pos));
    if (!starts_with(header, "MSG:")) {
      break;
    }
    const auto name = normalize_msgtype(trim(header.substr(4)));
    const auto body_start = line_end + 1;
    const auto next = text.find(sep, body_start);
    sections.emplace_back(name, text.substr(body_start, next - body_start));
    pos = next;
  }

  for (const auto& section : sections) {
    parse_msg_body(types, section.first, section.second);
  }
}

auto idl_type_to_msg(const std::string& type) -> std::string {
  std::string t = trim(type);
  if (t == "boolean") {
    return "bool";
  }
  if (t == "octet") {
    return "uint8";
  }
  if (t == "float") {
    return "float32";
  }
  if (t == "double") {
    return "float64";
  }
  if (t == "long double") {
    return "float128";
  }
  if (t == "long" || t == "int32") {
    return "int32";
  }
  if (t == "unsigned long" || t == "uint32") {
    return "uint32";
  }
  if (t == "short" || t == "int16") {
    return "int16";
  }
  if (t == "unsigned short" || t == "uint16") {
    return "uint16";
  }
  if (t == "long long" || t == "int64") {
    return "int64";
  }
  if (t == "unsigned long long" || t == "uint64") {
    return "uint64";
  }
  if (starts_with(t, "string")) {
    return "string";
  }
  return t;
}

void parse_idl_definition(std::unordered_map<std::string, TypeDef>& types, const std::string& idl_text) {
  std::string text = idl_text;
  text = std::regex_replace(text, std::regex(R"(//[^\n]*)"), "");
  std::vector<std::string> modules;
  const std::regex module_re(R"(module\s+([A-Za-z_][A-Za-z0-9_]*))");
  for (std::sregex_iterator it(text.begin(), text.end(), module_re);
       it != std::sregex_iterator();
       ++it) {
    modules.push_back((*it)[1].str());
  }
  const std::string package = modules.empty() ? "idl_msgs" : modules[0];
  const std::string ns = modules.size() >= 2 ? modules[1] : "msg";

  const std::regex struct_re(R"(struct\s+([A-Za-z_][A-Za-z0-9_]*)\s*\{([^}]*)\}\s*;)");
  for (std::sregex_iterator it(text.begin(), text.end(), struct_re); it != std::sregex_iterator(); ++it) {
    const std::string struct_name = (*it)[1].str();
    std::string body = (*it)[2].str();
    TypeDef def;
    std::istringstream stream(body);
    std::string decl;
    while (std::getline(stream, decl, ';')) {
      decl = trim(decl);
      if (decl.empty() || decl[0] == '@') {
        continue;
      }
      const auto words = split_words(decl);
      if (words.size() < 2) {
        continue;
      }
      std::string field_name = words.back();
      std::string type;
      for (std::size_t idx = 0; idx + 1 < words.size(); ++idx) {
        if (!type.empty()) {
          type += " ";
        }
        type += words[idx];
      }
      if (starts_with(type, "sequence<")) {
        auto inner = type.substr(9, type.size() - 10);
        auto comma = inner.find(',');
        if (comma != std::string::npos) {
          inner = inner.substr(0, comma);
        }
        type = idl_type_to_msg(inner) + "[]";
      } else {
        type = idl_type_to_msg(type);
      }
      def.fields.push_back({field_name, parse_type_token(package + "/" + ns + "/" + struct_name, type)});
    }
    types[package + "/" + ns + "/" + struct_name] = std::move(def);
  }
}

#include "generated_typestores.inc"

auto scalar_default(const std::string& base) -> TypedValue;
auto default_for_desc(const std::shared_ptr<detail::TypestoreState>& store, const FieldDesc& desc)
    -> TypedValue;

}  // namespace

namespace detail {

struct ConnectionState {
  int id = 0;
  std::string topic;
  std::string msgtype;
  MessageDefinitionFormat msgdef_format = MessageDefinitionFormat::Msg;
  std::string msgdef_data;
  std::string digest;
  std::string serialization_format = "cdr";
  std::string offered_qos_profiles;
  std::optional<std::string> callerid;
  std::optional<int> latching;
  std::int64_t msgcount = 0;
  BagFormat bag_format = BagFormat::Rosbag2;
};

struct TypestoreState {
  std::unordered_map<std::string, TypeDef> types;
};

struct TypedMessageState {
  std::shared_ptr<TypestoreState> typestore;
  std::string msgtype;
  std::vector<std::pair<std::string, TypedValue>> fields;
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

struct ReaderState {
  explicit ReaderState(std::vector<std::string> paths_, ReaderOptions options_)
      : paths(std::move(paths_)),
        options(options_),
        typestore(TypestorePreset::Empty),
        default_typestore_loaded(options.default_typestore == TypestorePreset::Empty) {}

  std::vector<std::string> paths;
  ReaderOptions options;
  BagFormat bag_format = BagFormat::Rosbag2;
  StoragePlugin storage = StoragePlugin::Sqlite3;
  bool is_open = false;
  std::vector<Connection> connections;
  Typestore typestore;
  bool default_typestore_loaded = false;
  std::int64_t start_time = kMaxTime;
  std::int64_t end_time = 0;
  std::int64_t message_count = 0;
  bool rosbag2_message_compression = false;
  std::vector<NativeMessage> eager_messages;
  std::map<std::uint64_t, Ros1Chunk> ros1_chunks;
  std::vector<Ros1ChunkInfo> ros1_chunk_infos;
  std::map<int, std::vector<IndexEntry>> ros1_indexes;
};

struct MessageStreamState {
  std::shared_ptr<ReaderState> reader;
  std::vector<NativeMessage> messages;
  std::vector<IndexEntry> ros1_entries;
  std::size_t index = 0;
  std::ifstream ros1_stream;
  std::uint64_t ros1_cached_chunk_pos = std::numeric_limits<std::uint64_t>::max();
  std::vector<std::uint8_t> ros1_chunk_data;
};

struct WriterState {
  WriterState(std::string path_, WriterOptions options_)
      : path(std::move(path_)), options(options_), typestore(TypestorePreset::Latest) {}

  std::string path;
  WriterOptions options;
  bool is_open = false;
  std::vector<Connection> connections;
  Typestore typestore;
  std::ofstream file;
  std::vector<std::uint8_t> chunk;
  std::int64_t chunk_start = kMaxTime;
  std::int64_t chunk_end = 0;
  std::map<int, std::vector<std::pair<std::int64_t, std::uint32_t>>> chunk_connections;
  struct WrittenChunk {
    std::uint64_t pos = 0;
    std::int64_t start = kMaxTime;
    std::int64_t end = 0;
    std::map<int, std::vector<std::pair<std::int64_t, std::uint32_t>>> connections;
  };
  std::vector<WrittenChunk> written_chunks;
  sqlite3* sqlite = nullptr;
  std::int64_t min_timestamp = kMaxTime;
  std::int64_t max_timestamp = 0;
  std::int64_t total_messages = 0;
  fs::path storage_path;
  bool mcap_header_written = false;
  std::vector<std::uint8_t> mcap_chunk;
  std::int64_t mcap_chunk_start = kMaxTime;
  std::int64_t mcap_chunk_end = 0;
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

auto require_type(const std::shared_ptr<detail::TypestoreState>& store, const std::string& msgtype)
    -> const TypeDef& {
  const auto normalized = normalize_msgtype(msgtype);
  auto it = store->types.find(normalized);
  if (it == store->types.end()) {
    throw Error("Type '" + normalized + "' is unknown");
  }
  return it->second;
}

auto mutable_field(TypedMessage& message, const std::string& name)
    -> std::pair<std::string, TypedValue>* {
  auto& state = *detail::typed_message_state(message);
  for (auto& field : state.fields) {
    if (field.first == name) {
      return &field;
    }
  }
  return nullptr;
}

auto field_value(const TypedMessage& message, const std::string& name) -> const TypedValue& {
  const auto& state = require_typed_message_state(detail::typed_message_state(message));
  for (const auto& field : state.fields) {
    if (field.first == name) {
      return field.second;
    }
  }
  throw Error("Unknown field '" + name + "' for message type '" + state.msgtype + "'");
}

auto scalar_default(const std::string& base) -> TypedValue {
  if (base == "bool") {
    return TypedValue::from_bool(false);
  }
  if (base == "string") {
    return TypedValue::from_string("");
  }
  if (base == "float32" || base == "float64" || base == "float128") {
    return TypedValue::from_double(0.0);
  }
  if (base_is_unsigned(base)) {
    return TypedValue::from_uint(0);
  }
  return TypedValue::from_int(0);
}

auto default_for_desc(const std::shared_ptr<detail::TypestoreState>& store, const FieldDesc& desc)
    -> TypedValue {
  switch (desc.kind) {
    case NodeKind::Base:
      return scalar_default(desc.value);
    case NodeKind::Name: {
      const auto& type = require_type(store, desc.value);
      auto state = std::make_shared<detail::TypedMessageState>();
      state->typestore = store;
      state->msgtype = normalize_msgtype(desc.value);
      for (const auto& field : type.fields) {
        state->fields.emplace_back(field.name, default_for_desc(store, field.desc));
      }
      return TypedValue::from_message(detail::make_typed_message(std::move(state)));
    }
    case NodeKind::Array: {
      std::vector<TypedValue> values;
      values.reserve(static_cast<std::size_t>(desc.bound));
      for (int idx = 0; idx < desc.bound; ++idx) {
        values.push_back(default_for_desc(store, *desc.sub));
      }
      return TypedValue::from_array(std::move(values));
    }
    case NodeKind::Sequence:
      return TypedValue::from_array({});
  }
  return {};
}

auto make_connection(
    int id,
    std::string topic,
    std::string msgtype,
    MessageDefinitionFormat msgdef_format,
    std::string msgdef_data,
    std::string digest,
    BagFormat bag_format) -> Connection {
  auto state = std::make_shared<detail::ConnectionState>();
  state->id = id;
  state->topic = std::move(topic);
  state->msgtype = normalize_msgtype(std::move(msgtype));
  state->msgdef_format = msgdef_format;
  state->msgdef_data = std::move(msgdef_data);
  state->digest = std::move(digest);
  state->bag_format = bag_format;
  if (bag_format == BagFormat::Rosbag2) {
    state->serialization_format = "cdr";
  }
  return detail::make_connection(std::move(state));
}

auto make_connection_from_spec(const ConnectionSpec& spec, int id, BagFormat format) -> Connection {
  auto connection = make_connection(
      id,
      spec.topic,
      spec.msgtype,
      spec.msgdef_format,
      spec.msgdef_data,
      spec.digest,
      format);
  auto& state = *detail::connection_state(connection);
  state.serialization_format = spec.serialization_format;
  state.offered_qos_profiles = spec.offered_qos_profiles;
  state.callerid = spec.callerid;
  state.latching = spec.latching;
  return connection;
}

auto cdr_alignment_for_write(const FieldDesc& desc, const std::shared_ptr<detail::TypestoreState>& store)
    -> std::size_t {
  return field_alignment(desc, store->types);
}

void write_ros1_value(
    std::vector<std::uint8_t>& out,
    const std::shared_ptr<detail::TypestoreState>& store,
    const FieldDesc& desc,
    const TypedValue& value);

auto read_ros1_value(
    const std::vector<std::uint8_t>& data,
    std::size_t& pos,
    const std::shared_ptr<detail::TypestoreState>& store,
    const FieldDesc& desc) -> TypedValue;

void write_cdr_value(
    std::vector<std::uint8_t>& out,
    const std::shared_ptr<detail::TypestoreState>& store,
    const FieldDesc& desc,
    const TypedValue& value,
    bool little_endian);

auto read_cdr_value(
    const std::vector<std::uint8_t>& data,
    std::size_t& pos,
    const std::shared_ptr<detail::TypestoreState>& store,
    const FieldDesc& desc,
    bool little_endian) -> TypedValue;

void write_base_ros1(std::vector<std::uint8_t>& out, const std::string& base, const TypedValue& value) {
  if (base == "bool") {
    append_le<std::uint8_t>(out, value.as_bool() ? 1 : 0);
  } else if (base == "string") {
    const auto text = value.as_string();
    append_le<std::uint32_t>(out, static_cast<std::uint32_t>(text.size()));
    out.insert(out.end(), text.begin(), text.end());
  } else if (base == "float32") {
    const float f = static_cast<float>(value.as_double());
    append_le<float>(out, f);
  } else if (base == "float64") {
    append_le<double>(out, value.as_double());
  } else if (base_is_unsigned(base)) {
    const auto v = value.as_uint();
    if (base_size(base) == 1) {
      append_le<std::uint8_t>(out, static_cast<std::uint8_t>(v));
    } else if (base_size(base) == 2) {
      append_le<std::uint16_t>(out, static_cast<std::uint16_t>(v));
    } else if (base_size(base) == 4) {
      append_le<std::uint32_t>(out, static_cast<std::uint32_t>(v));
    } else {
      append_le<std::uint64_t>(out, static_cast<std::uint64_t>(v));
    }
  } else {
    const auto v = value.as_int();
    if (base_size(base) == 1) {
      append_le<std::int8_t>(out, static_cast<std::int8_t>(v));
    } else if (base_size(base) == 2) {
      append_le<std::int16_t>(out, static_cast<std::int16_t>(v));
    } else if (base_size(base) == 4) {
      append_le<std::int32_t>(out, static_cast<std::int32_t>(v));
    } else {
      append_le<std::int64_t>(out, static_cast<std::int64_t>(v));
    }
  }
}

auto read_base_ros1(const std::vector<std::uint8_t>& data, std::size_t& pos, const std::string& base)
    -> TypedValue {
  if (base == "bool") {
    return TypedValue::from_bool(read_le<std::uint8_t>(data, pos) != 0);
  }
  if (base == "string") {
    const auto size = read_le<std::uint32_t>(data, pos);
    if (pos + size > data.size()) {
      throw Error("Unexpected end of ROS1 string");
    }
    std::string text(reinterpret_cast<const char*>(data.data() + pos), size);
    pos += size;
    return TypedValue::from_string(std::move(text));
  }
  if (base == "float32") {
    return TypedValue::from_double(read_le<float>(data, pos));
  }
  if (base == "float64") {
    return TypedValue::from_double(read_le<double>(data, pos));
  }
  if (base_is_unsigned(base)) {
    if (base_size(base) == 1) {
      return TypedValue::from_uint(read_le<std::uint8_t>(data, pos));
    }
    if (base_size(base) == 2) {
      return TypedValue::from_uint(read_le<std::uint16_t>(data, pos));
    }
    if (base_size(base) == 4) {
      return TypedValue::from_uint(read_le<std::uint32_t>(data, pos));
    }
    return TypedValue::from_uint(read_le<std::uint64_t>(data, pos));
  }
  if (base_size(base) == 1) {
    return TypedValue::from_int(read_le<std::int8_t>(data, pos));
  }
  if (base_size(base) == 2) {
    return TypedValue::from_int(read_le<std::int16_t>(data, pos));
  }
  if (base_size(base) == 4) {
    return TypedValue::from_int(read_le<std::int32_t>(data, pos));
  }
  return TypedValue::from_int(read_le<std::int64_t>(data, pos));
}

void write_ros1_value(
    std::vector<std::uint8_t>& out,
    const std::shared_ptr<detail::TypestoreState>& store,
    const FieldDesc& desc,
    const TypedValue& value) {
  switch (desc.kind) {
    case NodeKind::Base:
      write_base_ros1(out, desc.value, value);
      return;
    case NodeKind::Name: {
      const auto message = value.as_message();
      const auto& msg_state = require_typed_message_state(detail::typed_message_state(message));
      const auto& type = require_type(store, desc.value);
      for (const auto& field : type.fields) {
        write_ros1_value(out, store, field.desc, field_value(message, field.name));
      }
      (void)msg_state;
      return;
    }
    case NodeKind::Array: {
      const auto values = value.as_array();
      if (values.size() != static_cast<std::size_t>(desc.bound)) {
        throw Error("Unexpected array length");
      }
      for (const auto& item : values) {
        write_ros1_value(out, store, *desc.sub, item);
      }
      return;
    }
    case NodeKind::Sequence: {
      const auto values = value.as_array();
      append_le<std::uint32_t>(out, static_cast<std::uint32_t>(values.size()));
      for (const auto& item : values) {
        write_ros1_value(out, store, *desc.sub, item);
      }
      return;
    }
  }
}

auto read_ros1_value(
    const std::vector<std::uint8_t>& data,
    std::size_t& pos,
    const std::shared_ptr<detail::TypestoreState>& store,
    const FieldDesc& desc) -> TypedValue {
  switch (desc.kind) {
    case NodeKind::Base:
      return read_base_ros1(data, pos, desc.value);
    case NodeKind::Name: {
      const auto& type = require_type(store, desc.value);
      auto state = std::make_shared<detail::TypedMessageState>();
      state->typestore = store;
      state->msgtype = normalize_msgtype(desc.value);
      for (const auto& field : type.fields) {
        state->fields.emplace_back(field.name, read_ros1_value(data, pos, store, field.desc));
      }
      return TypedValue::from_message(detail::make_typed_message(std::move(state)));
    }
    case NodeKind::Array: {
      std::vector<TypedValue> values;
      values.reserve(static_cast<std::size_t>(desc.bound));
      for (int idx = 0; idx < desc.bound; ++idx) {
        values.push_back(read_ros1_value(data, pos, store, *desc.sub));
      }
      return TypedValue::from_array(std::move(values));
    }
    case NodeKind::Sequence: {
      const auto size = read_le<std::uint32_t>(data, pos);
      std::vector<TypedValue> values;
      values.reserve(size);
      for (std::uint32_t idx = 0; idx < size; ++idx) {
        values.push_back(read_ros1_value(data, pos, store, *desc.sub));
      }
      return TypedValue::from_array(std::move(values));
    }
  }
  return {};
}

void write_base_cdr(
    std::vector<std::uint8_t>& out,
    const std::string& base,
    const TypedValue& value,
    bool little_endian) {
  align_vector(out, base_size(base));
  if (base == "string") {
    throw Error("internal string cdr path error");
  }
  if (base == "bool") {
    append_endian<std::uint8_t>(out, value.as_bool() ? 1 : 0, little_endian);
  } else if (base == "float32") {
    const float f = static_cast<float>(value.as_double());
    append_endian<float>(out, f, little_endian);
  } else if (base == "float64") {
    append_endian<double>(out, value.as_double(), little_endian);
  } else if (base_is_unsigned(base)) {
    const auto v = value.as_uint();
    if (base_size(base) == 1) {
      append_endian<std::uint8_t>(out, static_cast<std::uint8_t>(v), little_endian);
    } else if (base_size(base) == 2) {
      append_endian<std::uint16_t>(out, static_cast<std::uint16_t>(v), little_endian);
    } else if (base_size(base) == 4) {
      append_endian<std::uint32_t>(out, static_cast<std::uint32_t>(v), little_endian);
    } else {
      append_endian<std::uint64_t>(out, static_cast<std::uint64_t>(v), little_endian);
    }
  } else {
    const auto v = value.as_int();
    if (base_size(base) == 1) {
      append_endian<std::int8_t>(out, static_cast<std::int8_t>(v), little_endian);
    } else if (base_size(base) == 2) {
      append_endian<std::int16_t>(out, static_cast<std::int16_t>(v), little_endian);
    } else if (base_size(base) == 4) {
      append_endian<std::int32_t>(out, static_cast<std::int32_t>(v), little_endian);
    } else {
      append_endian<std::int64_t>(out, static_cast<std::int64_t>(v), little_endian);
    }
  }
}

void write_cdr_value(
    std::vector<std::uint8_t>& out,
    const std::shared_ptr<detail::TypestoreState>& store,
    const FieldDesc& desc,
    const TypedValue& value,
    bool little_endian) {
  switch (desc.kind) {
    case NodeKind::Base:
      if (desc.value == "string") {
        align_vector(out, 4);
        const auto text = value.as_string();
        append_endian<std::uint32_t>(out, static_cast<std::uint32_t>(text.size() + 1), little_endian);
        out.insert(out.end(), text.begin(), text.end());
        out.push_back(0);
      } else {
        write_base_cdr(out, desc.value, value, little_endian);
      }
      return;
    case NodeKind::Name: {
      align_vector(out, cdr_alignment_for_write(desc, store));
      const auto message = value.as_message();
      const auto& type = require_type(store, desc.value);
      for (const auto& field : type.fields) {
        write_cdr_value(out, store, field.desc, field_value(message, field.name), little_endian);
      }
      return;
    }
    case NodeKind::Array: {
      const auto values = value.as_array();
      if (values.size() != static_cast<std::size_t>(desc.bound)) {
        throw Error("Unexpected array length");
      }
      align_vector(out, cdr_alignment_for_write(*desc.sub, store));
      for (const auto& item : values) {
        write_cdr_value(out, store, *desc.sub, item, little_endian);
      }
      return;
    }
    case NodeKind::Sequence: {
      align_vector(out, 4);
      const auto values = value.as_array();
      append_endian<std::uint32_t>(out, static_cast<std::uint32_t>(values.size()), little_endian);
      if (!values.empty()) {
        align_vector(out, cdr_alignment_for_write(*desc.sub, store));
      }
      for (const auto& item : values) {
        write_cdr_value(out, store, *desc.sub, item, little_endian);
      }
      return;
    }
  }
}

auto read_base_cdr(
    const std::vector<std::uint8_t>& data,
    std::size_t& pos,
    const std::string& base,
    bool little_endian) -> TypedValue {
  if (base == "string") {
    align_pos(pos, 4, data.size());
    const auto size = read_endian<std::uint32_t>(data, pos, little_endian);
    if (size == 0 || pos + size > data.size()) {
      throw Error("Unexpected end of CDR string");
    }
    std::string text(reinterpret_cast<const char*>(data.data() + pos), size - 1);
    pos += size;
    return TypedValue::from_string(std::move(text));
  }
  align_pos(pos, base_size(base), data.size());
  if (base == "bool") {
    return TypedValue::from_bool(read_endian<std::uint8_t>(data, pos, little_endian) != 0);
  }
  if (base == "float32") {
    return TypedValue::from_double(read_endian<float>(data, pos, little_endian));
  }
  if (base == "float64") {
    return TypedValue::from_double(read_endian<double>(data, pos, little_endian));
  }
  if (base_is_unsigned(base)) {
    if (base_size(base) == 1) {
      return TypedValue::from_uint(read_endian<std::uint8_t>(data, pos, little_endian));
    }
    if (base_size(base) == 2) {
      return TypedValue::from_uint(read_endian<std::uint16_t>(data, pos, little_endian));
    }
    if (base_size(base) == 4) {
      return TypedValue::from_uint(read_endian<std::uint32_t>(data, pos, little_endian));
    }
    return TypedValue::from_uint(read_endian<std::uint64_t>(data, pos, little_endian));
  }
  if (base_size(base) == 1) {
    return TypedValue::from_int(read_endian<std::int8_t>(data, pos, little_endian));
  }
  if (base_size(base) == 2) {
    return TypedValue::from_int(read_endian<std::int16_t>(data, pos, little_endian));
  }
  if (base_size(base) == 4) {
    return TypedValue::from_int(read_endian<std::int32_t>(data, pos, little_endian));
  }
  return TypedValue::from_int(read_endian<std::int64_t>(data, pos, little_endian));
}

auto read_cdr_value(
    const std::vector<std::uint8_t>& data,
    std::size_t& pos,
    const std::shared_ptr<detail::TypestoreState>& store,
    const FieldDesc& desc,
    bool little_endian) -> TypedValue {
  switch (desc.kind) {
    case NodeKind::Base:
      return read_base_cdr(data, pos, desc.value, little_endian);
    case NodeKind::Name: {
      align_pos(pos, cdr_alignment_for_write(desc, store), data.size());
      const auto& type = require_type(store, desc.value);
      auto state = std::make_shared<detail::TypedMessageState>();
      state->typestore = store;
      state->msgtype = normalize_msgtype(desc.value);
      for (const auto& field : type.fields) {
        state->fields.emplace_back(field.name, read_cdr_value(data, pos, store, field.desc, little_endian));
      }
      return TypedValue::from_message(detail::make_typed_message(std::move(state)));
    }
    case NodeKind::Array: {
      align_pos(pos, cdr_alignment_for_write(*desc.sub, store), data.size());
      std::vector<TypedValue> values;
      values.reserve(static_cast<std::size_t>(desc.bound));
      for (int idx = 0; idx < desc.bound; ++idx) {
        values.push_back(read_cdr_value(data, pos, store, *desc.sub, little_endian));
      }
      return TypedValue::from_array(std::move(values));
    }
    case NodeKind::Sequence: {
      align_pos(pos, 4, data.size());
      const auto size = read_endian<std::uint32_t>(data, pos, little_endian);
      if (size != 0) {
        align_pos(pos, cdr_alignment_for_write(*desc.sub, store), data.size());
      }
      std::vector<TypedValue> values;
      values.reserve(size);
      for (std::uint32_t idx = 0; idx < size; ++idx) {
        values.push_back(read_cdr_value(data, pos, store, *desc.sub, little_endian));
      }
      return TypedValue::from_array(std::move(values));
    }
  }
  return {};
}

auto type_id_for_desc(
    const std::shared_ptr<detail::TypestoreState>& store,
    const FieldDesc& desc,
    int increment,
    int& capacity,
    int& string_capacity,
    std::string& nested) -> int {
  static const std::map<std::string, int> tid = {
      {"int8", 2},      {"uint8", 3},   {"int16", 4},   {"uint16", 5},
      {"int32", 6},     {"uint32", 7},  {"int64", 8},   {"uint64", 9},
      {"float32", 10},  {"float64", 11}, {"float128", 12}, {"char", 13},
      {"bool", 15},     {"byte", 16},   {"string", 17}};
  FieldDesc current = desc;
  if (desc.kind == NodeKind::Array || desc.kind == NodeKind::Sequence) {
    capacity = desc.bound;
    current = *desc.sub;
  }
  if (current.kind == NodeKind::Name) {
    nested = current.value;
    (void)require_type(store, nested);
    return increment + 1;
  }
  if (current.kind == NodeKind::Base && current.value == "string" && current.bound != 0) {
    string_capacity = current.bound;
    return increment + 21;
  }
  auto it = tid.find(current.value);
  if (it == tid.end()) {
    throw Error("Cannot hash unsupported field type");
  }
  return increment + it->second;
}

auto json_escape(const std::string& value) -> std::string {
  std::string out;
  for (const char ch : value) {
    if (ch == '"') {
      out += "\\\"";
    } else if (ch == '\\') {
      out += "\\\\";
    } else {
      out.push_back(ch);
    }
  }
  return out;
}

auto struct_json(
    const std::shared_ptr<detail::TypestoreState>& store,
    const std::string& msgtype,
    std::map<std::string, std::string>& cache) -> std::string {
  if (cache.count(msgtype) != 0) {
    return cache[msgtype];
  }
  cache[msgtype] = "";
  const auto& type = require_type(store, msgtype);
  std::ostringstream stream;
  stream << "{\"type_name\": \"" << json_escape(msgtype) << "\", \"fields\": [";
  const auto* fields = &type.fields;
  std::vector<FieldDef> fallback;
  if (fields->empty()) {
    fallback.push_back({"structure_needs_at_least_one_member", parse_type_token(msgtype, "uint8")});
    fields = &fallback;
  }
  bool first = true;
  for (const auto& field : *fields) {
    int increment = 0;
    if (field.desc.kind == NodeKind::Array) {
      increment = 48;
    } else if (field.desc.kind == NodeKind::Sequence) {
      increment = field.desc.bound != 0 ? 96 : 144;
    }
    int capacity = 0;
    int string_capacity = 0;
    std::string nested;
    const int tid = type_id_for_desc(store, field.desc, increment, capacity, string_capacity, nested);
    if (!nested.empty()) {
      (void)struct_json(store, nested, cache);
    }
    if (!first) {
      stream << ", ";
    }
    first = false;
    stream << "{\"name\": \"" << json_escape(field.name)
           << "\", \"type\": {\"type_id\": " << tid << ", \"capacity\": " << capacity
           << ", \"string_capacity\": " << string_capacity << ", \"nested_type_name\": \""
           << json_escape(nested) << "\"}}";
  }
  stream << "]}";
  cache[msgtype] = stream.str();
  return cache[msgtype];
}

auto gendefhash(
    const std::shared_ptr<detail::TypestoreState>& store,
    const std::string& msgtype,
    std::map<std::string, std::pair<std::string, std::string>>& subdefs,
    int ros_version) -> std::pair<std::string, std::string> {
  const auto& type = require_type(store, msgtype);
  std::vector<std::string> deftext;
  std::vector<std::string> hashtext;
  for (const auto& constant : type.constants) {
    deftext.push_back(constant.type + " " + constant.name + "=" + constant.value);
    hashtext.push_back(constant.type + " " + constant.name + "=" + constant.value);
  }
  for (const auto& field : type.fields) {
    if (field.name == "structure_needs_at_least_one_member") {
      continue;
    }
    std::function<std::pair<std::string, std::string>(const FieldDesc&)> emit_desc;
    emit_desc = [&](const FieldDesc& desc) -> std::pair<std::string, std::string> {
      if (desc.kind == NodeKind::Base) {
        return {desc.value == "string" && desc.bound ? "string<=" + std::to_string(desc.bound) : desc.value,
                desc.value == "string" && desc.bound ? "string<=" + std::to_string(desc.bound) : desc.value};
      }
      if (desc.kind == NodeKind::Name) {
        if (ros_version == 1 && desc.value == "builtin_interfaces/msg/Time") {
          return {"time", "time"};
        }
        if (ros_version == 1 && desc.value == "builtin_interfaces/msg/Duration") {
          return {"duration", "duration"};
        }
        if (subdefs.count(desc.value) == 0) {
          subdefs[desc.value] = {"", ""};
          subdefs[desc.value] = gendefhash(store, desc.value, subdefs, ros_version);
        }
        return {denormalize_msgtype(desc.value), subdefs[desc.value].second};
      }
      const auto sub = emit_desc(*desc.sub);
      const std::string count = desc.bound == 0 ? "" : std::to_string(desc.bound);
      if (desc.kind == NodeKind::Array) {
        return {sub.first + "[" + count + "]", sub.second + "[" + count + "]"};
      }
      const std::string bounded = desc.bound == 0 ? "" : "<=" + std::to_string(desc.bound);
      return {sub.first + "[" + bounded + "]", sub.second + "[" + bounded + "]"};
    };
    const auto rendered = emit_desc(field.desc);
    deftext.push_back(rendered.first + " " + field.name);
    hashtext.push_back(rendered.second + " " + field.name);
  }
  std::ostringstream defstream;
  for (const auto& line : deftext) {
    defstream << line << "\n";
  }
  std::ostringstream hashstream;
  for (std::size_t idx = 0; idx < hashtext.size(); ++idx) {
    if (idx != 0) {
      hashstream << "\n";
    }
    hashstream << hashtext[idx];
  }
  return {defstream.str(), md5_hex(hashstream.str())};
}

void require_reader_open(const detail::ReaderState& state) {
  if (!state.is_open) {
    throw Error("Rosbag reader is not open");
  }
}

void ensure_reader_typestore(detail::ReaderState& state) {
  if (state.default_typestore_loaded) {
    return;
  }
  std::unordered_map<std::string, TypeDef> generated;
  register_generated_types(generated, state.options.default_typestore);
  auto& types = detail::typestore_state(state.typestore)->types;
  for (auto& item : generated) {
    types.emplace(item.first, std::move(item.second));
  }
  state.default_typestore_loaded = true;
}

void require_writer_open(const detail::WriterState& state) {
  if (!state.is_open) {
    throw Error("Rosbag writer is not open");
  }
}

void validate_connection_spec(const ConnectionSpec& spec, BagFormat format) {
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

auto spec_from_connection(const Connection& connection) -> ConnectionSpec {
  const auto& state = require_connection_state(detail::connection_state(connection));
  ConnectionSpec spec;
  spec.topic = state.topic;
  spec.msgtype = state.msgtype;
  spec.msgdef_format = state.msgdef_format;
  spec.msgdef_data = state.msgdef_data;
  spec.digest = state.digest;
  spec.serialization_format = state.serialization_format;
  spec.offered_qos_profiles = state.offered_qos_profiles;
  spec.callerid = state.callerid;
  spec.latching = state.latching;
  return spec;
}

auto selected_connection_ids(
    const std::vector<Connection>& connections,
    const std::vector<int>& ids) -> std::set<int> {
  std::set<int> result;
  if (ids.empty()) {
    for (const auto& connection : connections) {
      result.insert(connection.id());
    }
  } else {
    result.insert(ids.begin(), ids.end());
  }
  return result;
}

auto connection_by_id(const std::vector<Connection>& connections, int id) -> Connection {
  for (const auto& connection : connections) {
    if (connection.id() == id) {
      return connection;
    }
  }
  throw Error("Unknown connection id");
}

void write_ros1_connection_record(const Connection& connection, std::ostream& stream) {
  const auto& state = require_connection_state(detail::connection_state(connection));
  RecordHeader header;
  set_u32(header, "conn", static_cast<std::uint32_t>(state.id));
  set_string(header, "topic", state.topic);
  write_header(stream, header, 7);

  RecordHeader data;
  set_string(data, "topic", state.topic);
  set_string(data, "type", denormalize_msgtype(state.msgtype));
  set_string(data, "md5sum", state.digest);
  set_string(data, "message_definition", state.msgdef_data);
  if (state.callerid) {
    set_string(data, "callerid", *state.callerid);
  }
  if (state.latching) {
    set_string(data, "latching", std::to_string(*state.latching));
  }
  write_header(stream, data);
}

void append_ros1_connection_record(const Connection& connection, std::vector<std::uint8_t>& out) {
  const auto& state = require_connection_state(detail::connection_state(connection));
  RecordHeader header;
  set_u32(header, "conn", static_cast<std::uint32_t>(state.id));
  set_string(header, "topic", state.topic);
  append_header(out, header, 7);

  RecordHeader data;
  set_string(data, "topic", state.topic);
  set_string(data, "type", denormalize_msgtype(state.msgtype));
  set_string(data, "md5sum", state.digest);
  set_string(data, "message_definition", state.msgdef_data);
  if (state.callerid) {
    set_string(data, "callerid", *state.callerid);
  }
  if (state.latching) {
    set_string(data, "latching", std::to_string(*state.latching));
  }
  append_header(out, data);
}

auto read_ros1_connection(std::istream& stream) -> Connection {
  RecordHeader header = read_header(stream, 7);
  const auto id = static_cast<int>(header.uint32_value("conn"));
  const auto topic = header.string_value("topic");
  RecordHeader data = read_header(stream);
  auto connection = make_connection(
      id,
      topic,
      data.string_value("type"),
      MessageDefinitionFormat::Msg,
      data.string_value("message_definition"),
      data.string_value("md5sum"),
      BagFormat::Rosbag1);
  auto& state = *detail::connection_state(connection);
  if (data.has("callerid")) {
    state.callerid = data.string_value("callerid");
  }
  if (data.has("latching")) {
    state.latching = std::stoi(data.string_value("latching"));
  }
  return connection;
}

auto read_ros1_chunk_info(std::istream& stream) -> Ros1ChunkInfo {
  RecordHeader header = read_header(stream, 6);
  Ros1ChunkInfo info;
  if (header.uint32_value("ver") != 1) {
    throw Error("CHUNK_INFO version is not supported");
  }
  info.pos = header.uint64_value("chunk_pos");
  const auto count = header.uint32_value("count");
  info.start_time = count == 0 ? kMaxTime : header.time_value("start_time");
  info.end_time = count == 0 ? 0 : header.time_value("end_time") + 1;
  const auto data_size = read_stream_le<std::uint32_t>(stream);
  if (data_size != count * 8) {
    throw Error("Bad CHUNK_INFO data size");
  }
  for (std::uint32_t idx = 0; idx < count; ++idx) {
    const int cid = static_cast<int>(read_stream_le<std::uint32_t>(stream));
    const int msgcount = static_cast<int>(read_stream_le<std::uint32_t>(stream));
    info.counts[cid] = msgcount;
  }
  return info;
}

auto read_ros1_chunk(std::istream& stream) -> Ros1Chunk {
  RecordHeader header = read_header(stream, 5);
  Ros1Chunk chunk;
  chunk.compression = header.string_value("compression");
  chunk.uncompressed_size = header.uint32_value("size");
  chunk.data_size = read_stream_le<std::uint32_t>(stream);
  chunk.data_pos = static_cast<std::uint64_t>(stream.tellg());
  stream.seekg(chunk.data_size, std::ios::cur);
  return chunk;
}

void read_ros1_index_data(
    std::istream& stream,
    std::uint64_t chunk_pos,
    std::map<int, std::vector<IndexEntry>>& indexes) {
  RecordHeader header = read_header(stream, 4);
  if (header.uint32_value("ver") != 1) {
    throw Error("IDXDATA version is not supported");
  }
  const int cid = static_cast<int>(header.uint32_value("conn"));
  const auto count = header.uint32_value("count");
  const auto data_size = read_stream_le<std::uint32_t>(stream);
  if (data_size != count * 12) {
    throw Error("Bad IDXDATA data size");
  }
  auto& index = indexes[cid];
  for (std::uint32_t idx = 0; idx < count; ++idx) {
    const auto sec = read_stream_le<std::uint32_t>(stream);
    const auto nsec = read_stream_le<std::uint32_t>(stream);
    const auto offset = read_stream_le<std::uint32_t>(stream);
    index.push_back({static_cast<std::int64_t>(sec) * 1000000000LL + nsec, chunk_pos, offset});
  }
}

void open_rosbag1(detail::ReaderState& state) {
  std::ifstream stream(state.paths.front(), std::ios::binary);
  if (!stream) {
    throw Error("Could not open file '" + state.paths.front() + "'");
  }
  std::string magic(13, '\0');
  stream.read(&magic[0], 13);
  if (magic != "#ROSBAG V2.0\n") {
    throw Error("File magic is invalid");
  }
  RecordHeader header = read_header(stream, 3);
  const auto index_pos = header.uint64_value("index_pos");
  const auto conn_count = header.uint32_value("conn_count");
  const auto chunk_count = header.uint32_value("chunk_count");
  if (header.has("encryptor") && !header.string_value("encryptor").empty()) {
    throw Error("Bag encryption is not supported");
  }
  if (index_pos == 0 && chunk_count != 0) {
    throw Error("Bag is not indexed");
  }
  state.bag_format = BagFormat::Rosbag1;
  state.storage = StoragePlugin::Sqlite3;
  if (chunk_count == 0) {
    state.start_time = kMaxTime;
    state.end_time = 0;
    state.message_count = 0;
    return;
  }

  stream.seekg(static_cast<std::streamoff>(index_pos));
  for (std::uint32_t idx = 0; idx < conn_count; ++idx) {
    state.connections.push_back(read_ros1_connection(stream));
  }
  for (std::uint32_t idx = 0; idx < chunk_count; ++idx) {
    state.ros1_chunk_infos.push_back(read_ros1_chunk_info(stream));
  }

  for (const auto& info : state.ros1_chunk_infos) {
    stream.seekg(static_cast<std::streamoff>(info.pos));
    state.ros1_chunks[info.pos] = read_ros1_chunk(stream);
    for (std::size_t idx = 0; idx < info.counts.size(); ++idx) {
      read_ros1_index_data(stream, info.pos, state.ros1_indexes);
    }
  }

  state.start_time = kMaxTime;
  state.end_time = 0;
  state.message_count = 0;
  for (const auto& info : state.ros1_chunk_infos) {
    state.start_time = std::min(state.start_time, info.start_time);
    state.end_time = std::max(state.end_time, info.end_time);
    for (const auto& item : info.counts) {
      state.message_count += item.second;
    }
  }
  for (auto& connection : state.connections) {
    auto& conn_state = *detail::connection_state(connection);
    conn_state.msgcount = static_cast<std::int64_t>(state.ros1_indexes[conn_state.id].size());
    if (!conn_state.msgdef_data.empty()) {
      state.typestore.register_msg(conn_state.msgtype, conn_state.msgdef_data);
    }
  }
}

auto rosbag1_sorted_entries(detail::ReaderState& state, const ReaderMessageOptions& options)
    -> std::vector<IndexEntry> {
  const auto wanted = selected_connection_ids(state.connections, options.connection_ids);
  std::vector<IndexEntry> entries;
  for (const auto& cid : wanted) {
    auto it = state.ros1_indexes.find(cid);
    if (it == state.ros1_indexes.end()) {
      continue;
    }
    entries.insert(entries.end(), it->second.begin(), it->second.end());
  }
  std::sort(entries.begin(), entries.end(), [](const auto& lhs, const auto& rhs) {
    return lhs.timestamp < rhs.timestamp;
  });

  std::vector<IndexEntry> filtered;
  filtered.reserve(entries.size());
  for (const auto& entry : entries) {
    if (options.start_time && entry.timestamp < *options.start_time) {
      continue;
    }
    if (options.stop_time && entry.timestamp >= *options.stop_time) {
      break;
    }
    filtered.push_back(entry);
  }
  return filtered;
}

void read_rosbag1_message_at(
    detail::ReaderState& state,
    std::ifstream& stream,
    std::uint64_t& cached_chunk_pos,
    std::vector<std::uint8_t>& chunk_data,
    const IndexEntry& entry,
    Message& message) {
  if (cached_chunk_pos != entry.chunk_pos) {
    const auto& chunk = state.ros1_chunks.at(entry.chunk_pos);
    stream.seekg(static_cast<std::streamoff>(chunk.data_pos));
    if (chunk.compression.empty() || chunk.compression == "none") {
      chunk_data.resize(chunk.data_size);
      stream.read(reinterpret_cast<char*>(chunk_data.data()), chunk.data_size);
    } else {
      std::vector<std::uint8_t> compressed(chunk.data_size);
      stream.read(reinterpret_cast<char*>(compressed.data()), chunk.data_size);
      chunk_data = decompress_named(chunk.compression, compressed, chunk.uncompressed_size);
    }
    cached_chunk_pos = entry.chunk_pos;
  }

  std::size_t pos = entry.offset;
  auto header = read_ros1_message_header(chunk_data, pos);
  while (header.op == 7) {
    const auto size = read_le<std::uint32_t>(chunk_data, pos);
    pos += size;
    header = read_ros1_message_header(chunk_data, pos);
  }
  if (header.op != 2) {
    throw Error("Expected to find message data");
  }
  const auto size = read_le<std::uint32_t>(chunk_data, pos);
  if (pos + size > chunk_data.size()) {
    throw Error("Message data exceeds chunk");
  }
  message.connection = connection_by_id(state.connections, header.connection_id);
  message.timestamp = header.timestamp;
  message.data.assign(chunk_data.begin() + static_cast<std::ptrdiff_t>(pos),
                      chunk_data.begin() + static_cast<std::ptrdiff_t>(pos + size));
}

auto read_rosbag1_message_at(
    detail::ReaderState& state,
    std::ifstream& stream,
    std::uint64_t& cached_chunk_pos,
    std::vector<std::uint8_t>& chunk_data,
    const IndexEntry& entry) -> NativeMessage {
  Message message;
  read_rosbag1_message_at(state, stream, cached_chunk_pos, chunk_data, entry, message);
  return {std::move(message.connection), message.timestamp, std::move(message.data)};
}

auto collect_rosbag1_messages(detail::ReaderState& state, const ReaderMessageOptions& options)
    -> std::vector<NativeMessage> {
  const auto entries = rosbag1_sorted_entries(state, options);
  std::ifstream stream(state.paths.front(), std::ios::binary);
  if (!stream) {
    throw Error("Could not open rosbag1 file");
  }
  std::uint64_t cached_chunk_pos = std::numeric_limits<std::uint64_t>::max();
  std::vector<std::uint8_t> chunk_data;
  std::vector<NativeMessage> result;
  result.reserve(entries.size());
  for (const auto& entry : entries) {
    result.push_back(read_rosbag1_message_at(state, stream, cached_chunk_pos, chunk_data, entry));
  }
  return result;
}

auto sqlite_exec(sqlite3* db, const std::string& sql) -> void {
  char* errmsg = nullptr;
  if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errmsg) != SQLITE_OK) {
    std::string message = errmsg ? errmsg : "sqlite error";
    sqlite3_free(errmsg);
    throw Error(message);
  }
}

auto sqlite_text(sqlite3_stmt* stmt, int col) -> std::string {
  const auto* text = sqlite3_column_text(stmt, col);
  return text ? reinterpret_cast<const char*>(text) : "";
}

void open_sqlite_storage(detail::ReaderState& state, const fs::path& database) {
  sqlite3* db = nullptr;
  if (sqlite3_open_v2(database.string().c_str(), &db, SQLITE_OPEN_READONLY, nullptr) != SQLITE_OK) {
    throw Error("Could not open sqlite3 database '" + database.string() + "'");
  }
  auto close_db = [&]() {
    if (db) {
      sqlite3_close(db);
      db = nullptr;
    }
  };

  sqlite3_stmt* stmt = nullptr;
  const char* sql =
      "SELECT topics.id, name, type, COUNT(messages.id), serialization_format, "
      "offered_qos_profiles, type_description_hash "
      "FROM topics LEFT JOIN messages ON topics.id = messages.topic_id "
      "GROUP BY topics.id ORDER BY topics.id";
  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
    close_db();
    throw Error("Could not query sqlite3 topics");
  }
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    auto conn = make_connection(
        sqlite3_column_int(stmt, 0),
        sqlite_text(stmt, 1),
        sqlite_text(stmt, 2),
        MessageDefinitionFormat::None,
        "",
        sqlite_text(stmt, 6),
        BagFormat::Rosbag2);
    auto& cstate = *detail::connection_state(conn);
    cstate.msgcount = sqlite3_column_int64(stmt, 3);
    cstate.serialization_format = sqlite_text(stmt, 4);
    cstate.offered_qos_profiles = sqlite_text(stmt, 5);
    state.connections.push_back(conn);
  }
  sqlite3_finalize(stmt);

  sql =
      "SELECT topic_type, encoding, encoded_message_definition, type_description_hash "
      "FROM message_definitions ORDER BY id";
  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
    while (sqlite3_step(stmt) == SQLITE_ROW) {
      const auto msgtype = sqlite_text(stmt, 0);
      const auto encoding = sqlite_text(stmt, 1);
      const auto msgdef = sqlite_text(stmt, 2);
      for (auto& conn : state.connections) {
        auto& cstate = *detail::connection_state(conn);
        if (cstate.msgtype == msgtype) {
          cstate.msgdef_format = encoding == "ros2idl" ? MessageDefinitionFormat::Idl
                                                       : MessageDefinitionFormat::Msg;
          cstate.msgdef_data = msgdef;
          if (cstate.msgdef_format == MessageDefinitionFormat::Idl) {
            state.typestore.register_idl(msgdef);
          } else {
            state.typestore.register_msg(msgtype, msgdef);
          }
        }
      }
    }
    sqlite3_finalize(stmt);
  }

  sql = "SELECT MIN(timestamp), MAX(timestamp) + 1, COUNT(*) FROM messages";
  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
    close_db();
    throw Error("Could not query sqlite3 metadata");
  }
  if (sqlite3_step(stmt) == SQLITE_ROW) {
    if (sqlite3_column_type(stmt, 0) == SQLITE_NULL) {
      state.start_time = kMaxTime;
      state.end_time = 0;
      state.message_count = 0;
    } else {
      state.start_time = sqlite3_column_int64(stmt, 0);
      state.end_time = sqlite3_column_int64(stmt, 1);
      state.message_count = sqlite3_column_int64(stmt, 2);
    }
  }
  sqlite3_finalize(stmt);
  close_db();
}

auto collect_sqlite_messages(
    detail::ReaderState& state,
    const fs::path& database,
    const ReaderMessageOptions& options) -> std::vector<NativeMessage> {
  sqlite3* db = nullptr;
  if (sqlite3_open_v2(database.string().c_str(), &db, SQLITE_OPEN_READONLY, nullptr) != SQLITE_OK) {
    throw Error("Could not open sqlite3 database");
  }
  std::ostringstream sql;
  sql << "SELECT topic_id, timestamp, data FROM messages";
  std::vector<int> ids;
  const auto wanted = selected_connection_ids(state.connections, options.connection_ids);
  std::vector<std::string> clauses;
  if (!wanted.empty()) {
    std::ostringstream clause;
    clause << "topic_id IN (";
    bool first = true;
    for (const auto id : wanted) {
      if (!first) {
        clause << ",";
      }
      first = false;
      clause << id;
    }
    clause << ")";
    clauses.push_back(clause.str());
  }
  if (options.start_time) {
    clauses.push_back("timestamp >= " + std::to_string(*options.start_time));
  }
  if (options.stop_time) {
    clauses.push_back("timestamp < " + std::to_string(*options.stop_time));
  }
  if (!clauses.empty()) {
    sql << " WHERE ";
    for (std::size_t idx = 0; idx < clauses.size(); ++idx) {
      if (idx != 0) {
        sql << " AND ";
      }
      sql << clauses[idx];
    }
  }
  sql << " ORDER BY timestamp";

  sqlite3_stmt* stmt = nullptr;
  if (sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    sqlite3_close(db);
    throw Error("Could not query sqlite3 messages");
  }
  std::vector<NativeMessage> result;
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    NativeMessage msg;
    msg.connection = connection_by_id(state.connections, sqlite3_column_int(stmt, 0));
    msg.timestamp = sqlite3_column_int64(stmt, 1);
    const auto* blob = static_cast<const std::uint8_t*>(sqlite3_column_blob(stmt, 2));
    const auto size = sqlite3_column_bytes(stmt, 2);
    msg.data.assign(blob, blob + size);
    if (state.rosbag2_message_compression) {
      msg.data = zstd_decompress(msg.data);
    }
    result.push_back(std::move(msg));
  }
  sqlite3_finalize(stmt);
  sqlite3_close(db);
  return result;
}

void mcap_write_u16(std::vector<std::uint8_t>& out, std::uint16_t value) { append_le(out, value); }
void mcap_write_u32(std::vector<std::uint8_t>& out, std::uint32_t value) { append_le(out, value); }
void mcap_write_u64(std::vector<std::uint8_t>& out, std::uint64_t value) { append_le(out, value); }
void mcap_write_string(std::vector<std::uint8_t>& out, const std::string& value) {
  append_string_raw(out, value);
}
void mcap_write_record(std::ostream& stream, std::uint8_t opcode, const std::vector<std::uint8_t>& record) {
  stream.put(static_cast<char>(opcode));
  write_le<std::uint64_t>(stream, static_cast<std::uint64_t>(record.size()));
  if (!record.empty()) {
    stream.write(reinterpret_cast<const char*>(record.data()), static_cast<std::streamsize>(record.size()));
  }
}

void mcap_append_record(std::vector<std::uint8_t>& out, std::uint8_t opcode, const std::vector<std::uint8_t>& record) {
  out.push_back(opcode);
  append_le<std::uint64_t>(out, static_cast<std::uint64_t>(record.size()));
  out.insert(out.end(), record.begin(), record.end());
}

auto mcap_read_sized(const std::vector<std::uint8_t>& data, std::size_t& pos) -> std::vector<std::uint8_t> {
  const auto size = read_le<std::uint64_t>(data, pos);
  if (pos + size > data.size()) {
    throw Error("MCAP record exceeds file");
  }
  std::vector<std::uint8_t> result(data.begin() + static_cast<std::ptrdiff_t>(pos),
                                  data.begin() + static_cast<std::ptrdiff_t>(pos + size));
  pos += static_cast<std::size_t>(size);
  return result;
}

void open_mcap_storage(detail::ReaderState& state, const fs::path& path) {
  auto data = read_file(path);
  if (data.size() < 16 || std::string(reinterpret_cast<char*>(data.data()), 8) != "\x89MCAP0\r\n") {
    throw Error("MCAP file magic is invalid");
  }
  std::map<int, std::string> schema_names;
  std::map<int, std::string> schema_defs;
  struct ChannelInfo {
    int id = 0;
    int schema_id = 0;
    std::string topic;
    std::string encoding;
    std::string qos;
  };
  struct PendingMcapMessage {
    int channel_id = 0;
    std::int64_t timestamp = 0;
    std::vector<std::uint8_t> data;
  };
  std::map<int, ChannelInfo> channels;
  std::map<int, std::int64_t> counts;
  std::vector<PendingMcapMessage> pending_messages;
  std::int64_t start = kMaxTime;
  std::int64_t end = 0;

  auto read_metadata_qos = [](const std::vector<std::uint8_t>& rec, std::size_t& rpos) {
    const auto size = read_le<std::uint32_t>(rec, rpos);
    if (rpos + size > rec.size()) {
      throw Error("MCAP metadata map exceeds record");
    }
    const auto endpos = rpos + size;
    std::string qos;
    while (rpos < endpos) {
      const auto key = read_string_raw(rec, rpos);
      const auto value = read_string_raw(rec, rpos);
      if (key == "offered_qos_profiles") {
        qos = value;
      }
    }
    return qos;
  };

  std::function<void(const std::vector<std::uint8_t>&, std::size_t, std::size_t)> scan_records;
  scan_records = [&](const std::vector<std::uint8_t>& records, std::size_t pos, std::size_t endpos) {
    while (pos < endpos) {
      if (pos + 1 > records.size()) {
        throw Error("MCAP record opcode exceeds file");
      }
      const auto opcode = records[pos++];
      auto rec = mcap_read_sized(records, pos);
      std::size_t rpos = 0;
      if (opcode == 0x02) {
        break;
      }
      if (opcode == 0x03) {
        const int sid = read_le<std::uint16_t>(rec, rpos);
        schema_names[sid] = read_string_raw(rec, rpos);
        (void)read_string_raw(rec, rpos);
        schema_defs[sid] = read_string_raw(rec, rpos);
      } else if (opcode == 0x04) {
        ChannelInfo ch;
        ch.id = read_le<std::uint16_t>(rec, rpos);
        ch.schema_id = read_le<std::uint16_t>(rec, rpos);
        ch.topic = read_string_raw(rec, rpos);
        ch.encoding = read_string_raw(rec, rpos);
        ch.qos = read_metadata_qos(rec, rpos);
        channels[ch.id] = ch;
      } else if (opcode == 0x05) {
        const int cid = read_le<std::uint16_t>(rec, rpos);
        rpos += 4;
        const auto timestamp = static_cast<std::int64_t>(read_le<std::uint64_t>(rec, rpos));
        rpos += 8;
        counts[cid] += 1;
        start = std::min(start, timestamp);
        end = std::max(end, timestamp);
        PendingMcapMessage message;
        message.channel_id = cid;
        message.timestamp = timestamp;
        message.data.assign(rec.begin() + static_cast<std::ptrdiff_t>(rpos), rec.end());
        pending_messages.push_back(std::move(message));
      } else if (opcode == 0x06) {
        (void)read_le<std::uint64_t>(rec, rpos);
        (void)read_le<std::uint64_t>(rec, rpos);
        const auto uncompressed_size = read_le<std::uint64_t>(rec, rpos);
        rpos += 4;
        const auto compression = read_string_raw(rec, rpos);
        const auto compressed_size = read_le<std::uint64_t>(rec, rpos);
        if (rpos + compressed_size > rec.size()) {
          throw Error("MCAP chunk compressed data exceeds record");
        }
        std::vector<std::uint8_t> compressed(
            rec.begin() + static_cast<std::ptrdiff_t>(rpos),
            rec.begin() + static_cast<std::ptrdiff_t>(rpos + compressed_size));
        auto chunk_records = decompress_named(compression, compressed, static_cast<std::size_t>(uncompressed_size));
        scan_records(chunk_records, 0, chunk_records.size());
      }
      if (pos + 8 <= records.size() &&
          std::string(reinterpret_cast<const char*>(records.data() + pos), 8) == "\x89MCAP0\r\n") {
        break;
      }
    }
  };

  scan_records(data, 8, data.size());

  state.connections.clear();
  for (const auto& [cid, ch] : channels) {
    auto conn = make_connection(
        cid,
        ch.topic,
        schema_names[ch.schema_id],
        schema_defs[ch.schema_id].empty() ? MessageDefinitionFormat::None : MessageDefinitionFormat::Msg,
        schema_defs[ch.schema_id],
        "",
        BagFormat::Rosbag2);
    auto& cstate = *detail::connection_state(conn);
    cstate.serialization_format = ch.encoding;
    cstate.offered_qos_profiles = ch.qos;
    cstate.msgcount = counts[cid];
    state.connections.push_back(conn);
    if (!cstate.msgdef_data.empty()) {
      state.typestore.register_msg(cstate.msgtype, cstate.msgdef_data);
    }
  }
  state.eager_messages.clear();
  state.eager_messages.reserve(pending_messages.size());
  for (auto& msg : pending_messages) {
    NativeMessage native;
    native.connection = connection_by_id(state.connections, msg.channel_id);
    native.timestamp = msg.timestamp;
    native.data = std::move(msg.data);
    state.eager_messages.push_back(std::move(native));
  }
  std::sort(state.eager_messages.begin(), state.eager_messages.end(), [](const auto& lhs, const auto& rhs) {
    return lhs.timestamp < rhs.timestamp;
  });
  state.storage = StoragePlugin::Mcap;
  state.bag_format = BagFormat::Rosbag2;
  state.start_time = start;
  state.end_time = end == 0 ? 0 : end + 1;
  state.message_count = std::accumulate(counts.begin(), counts.end(), std::int64_t{0}, [](auto acc, const auto& item) {
    return acc + item.second;
  });
}

auto copy_or_decompress_file(const fs::path& path, bool compressed) -> fs::path {
  if (!compressed) {
    return path;
  }
  auto data = zstd_decompress(read_file(path));
  fs::path tmp = fs::temp_directory_path() / ("rosbags_cpp_" + path.stem().string());
  write_file(tmp, data);
  return tmp;
}

void open_rosbag2_dir(detail::ReaderState& state, const fs::path& path) {
  const auto metadata_path = path / "metadata.yaml";
  YAML::Node root = YAML::LoadFile(metadata_path.string());
  YAML::Node info = root["rosbag2_bagfile_information"];
  if (!info) {
    throw Error("metadata.yaml is missing rosbag2_bagfile_information");
  }
  const auto storage = info["storage_identifier"].as<std::string>();
  const auto compression_mode =
      info["compression_mode"] ? info["compression_mode"].as<std::string>() : std::string();
  const auto compression_format =
      info["compression_format"] ? info["compression_format"].as<std::string>() : std::string();
  state.rosbag2_message_compression = compression_mode == "message" || compression_mode == "MESSAGE";
  const bool file_compressed = compression_mode == "file" || compression_mode == "FILE";
  fs::path storage_path = path / info["relative_file_paths"][0].as<std::string>();
  if (file_compressed && compression_format != "zstd") {
    throw Error("Only zstd rosbag2 file compression is supported");
  }
  storage_path = copy_or_decompress_file(storage_path, file_compressed);
  if (storage == "sqlite3") {
    state.storage = StoragePlugin::Sqlite3;
    open_sqlite_storage(state, storage_path);
    state.paths = {storage_path.string()};
  } else if (storage == "mcap") {
    open_mcap_storage(state, storage_path);
  } else {
    throw Error("Unsupported rosbag2 storage plugin '" + storage + "'");
  }
  state.bag_format = BagFormat::Rosbag2;
}

void write_rosbag1_chunk(detail::WriterState& state) {
  if (state.chunk.empty()) {
    return;
  }
  detail::WriterState::WrittenChunk written;
  written.pos = static_cast<std::uint64_t>(state.file.tellp());
  written.start = state.chunk_start;
  written.end = state.chunk_end;
  written.connections = state.chunk_connections;

  RecordHeader header;
  const auto compression = compression_name(state.options.compression_format, BagFormat::Rosbag1);
  set_string(header, "compression", compression);
  set_u32(header, "size", static_cast<std::uint32_t>(state.chunk.size()));
  write_header(state.file, header, 5);
  const auto compressed = compress_named(compression, state.chunk);
  write_le<std::uint32_t>(state.file, static_cast<std::uint32_t>(compressed.size()));
  if (!compressed.empty()) {
    state.file.write(reinterpret_cast<const char*>(compressed.data()), compressed.size());
  }

  for (const auto& [cid, items] : state.chunk_connections) {
    RecordHeader idx;
    set_u32(idx, "ver", 1);
    set_u32(idx, "conn", static_cast<std::uint32_t>(cid));
    set_u32(idx, "count", static_cast<std::uint32_t>(items.size()));
    write_header(state.file, idx, 4);
    write_le<std::uint32_t>(state.file, static_cast<std::uint32_t>(items.size() * 12));
    for (const auto& item : items) {
      const auto packed = serialize_time(item.first);
      state.file.write(reinterpret_cast<const char*>(packed.data()), packed.size());
      write_le<std::uint32_t>(state.file, item.second);
    }
  }

  state.written_chunks.push_back(std::move(written));
  state.chunk.clear();
  state.chunk_start = kMaxTime;
  state.chunk_end = 0;
  state.chunk_connections.clear();
}

auto make_metadata_yaml(const detail::WriterState& state, const fs::path& relative_file) -> std::string {
  std::ostringstream yaml;
  const auto duration = state.total_messages ? state.max_timestamp - state.min_timestamp : 0;
  const auto start = state.total_messages ? state.min_timestamp : 0;
  const std::string mode = state.options.compression_mode == CompressionMode::File
                               ? "file"
                               : state.options.compression_mode == CompressionMode::Message ? "message" : "";
  const auto format = mode.empty() ? "" : compression_name(state.options.compression_format, BagFormat::Rosbag2);
  yaml << "rosbag2_bagfile_information:\n";
  yaml << "  version: " << state.options.rosbag2_version << "\n";
  yaml << "  storage_identifier: " << (state.options.storage == StoragePlugin::Mcap ? "mcap" : "sqlite3") << "\n";
  yaml << "  relative_file_paths:\n";
  yaml << "    - " << relative_file.filename().string() << "\n";
  yaml << "  duration:\n";
  yaml << "    nanoseconds: " << duration << "\n";
  yaml << "  starting_time:\n";
  yaml << "    nanoseconds_since_epoch: " << start << "\n";
  yaml << "  message_count: " << state.total_messages << "\n";
  yaml << "  topics_with_message_count:\n";
  for (const auto& connection : state.connections) {
    const auto& conn = require_connection_state(detail::connection_state(connection));
    yaml << "    - topic_metadata:\n";
    yaml << "        name: " << conn.topic << "\n";
    yaml << "        type: " << conn.msgtype << "\n";
    yaml << "        serialization_format: " << conn.serialization_format << "\n";
    yaml << "        offered_qos_profiles: \"\"\n";
    yaml << "        type_description_hash: " << conn.digest << "\n";
    yaml << "      message_count: " << conn.msgcount << "\n";
  }
  yaml << "  compression_format: " << (format.empty() ? "\"\"" : format) << "\n";
  yaml << "  compression_mode: " << (mode.empty() ? "\"\"" : mode) << "\n";
  yaml << "  files:\n";
  yaml << "    - path: " << relative_file.filename().string() << "\n";
  yaml << "      starting_time:\n";
  yaml << "        nanoseconds_since_epoch: " << start << "\n";
  yaml << "      duration:\n";
  yaml << "        nanoseconds: " << duration << "\n";
  yaml << "      message_count: " << state.total_messages << "\n";
  yaml << "  custom_data: {}\n";
  yaml << "  ros_distro: rosbags\n";
  return yaml.str();
}

void sqlite_prepare_schema(sqlite3* db) {
  sqlite_exec(
      db,
      "CREATE TABLE schema(schema_version INTEGER PRIMARY KEY, ros_distro TEXT NOT NULL);"
      "CREATE TABLE metadata(id INTEGER PRIMARY KEY, metadata_version INTEGER NOT NULL, metadata TEXT NOT NULL);"
      "CREATE TABLE topics(id INTEGER PRIMARY KEY, name TEXT NOT NULL, type TEXT NOT NULL, "
      "serialization_format TEXT NOT NULL, offered_qos_profiles TEXT NOT NULL, type_description_hash TEXT NOT NULL);"
      "CREATE TABLE message_definitions(id INTEGER PRIMARY KEY, topic_type TEXT NOT NULL, encoding TEXT NOT NULL, "
      "encoded_message_definition TEXT NOT NULL, type_description_hash TEXT NOT NULL);"
      "CREATE TABLE messages(id INTEGER PRIMARY KEY, topic_id INTEGER NOT NULL, timestamp INTEGER NOT NULL, data BLOB NOT NULL);"
      "CREATE INDEX timestamp_idx ON messages (timestamp ASC);"
      "INSERT INTO schema(schema_version, ros_distro) VALUES (4, 'rosbags');");
}

void sqlite_bind_text(sqlite3_stmt* stmt, int index, const std::string& value) {
  sqlite3_bind_text(stmt, index, value.c_str(), static_cast<int>(value.size()), SQLITE_TRANSIENT);
}

void write_mcap_schema_channel(std::ostream& stream, const Connection& connection) {
  const auto& conn = require_connection_state(detail::connection_state(connection));
  std::vector<std::uint8_t> rec;
  mcap_write_u16(rec, static_cast<std::uint16_t>(conn.id));
  mcap_write_string(rec, conn.msgtype);
  mcap_write_string(rec, conn.msgdef_format == MessageDefinitionFormat::Idl ? "ros2idl" : "ros2msg");
  mcap_write_string(rec, conn.msgdef_data);
  mcap_write_record(stream, 0x03, rec);

  rec.clear();
  mcap_write_u16(rec, static_cast<std::uint16_t>(conn.id));
  mcap_write_u16(rec, static_cast<std::uint16_t>(conn.id));
  mcap_write_string(rec, conn.topic);
  mcap_write_string(rec, conn.serialization_format);
  std::vector<std::uint8_t> metadata;
  mcap_write_string(metadata, "offered_qos_profiles");
  mcap_write_string(metadata, conn.offered_qos_profiles);
  mcap_write_u32(rec, static_cast<std::uint32_t>(metadata.size()));
  rec.insert(rec.end(), metadata.begin(), metadata.end());
  mcap_write_record(stream, 0x04, rec);
}

void write_mcap_chunk(detail::WriterState& state) {
  if (state.mcap_chunk.empty()) {
    return;
  }

  const auto compression =
      state.options.compression_mode == CompressionMode::Storage
          ? compression_name(state.options.compression_format, BagFormat::Rosbag2)
          : std::string();
  const auto compressed = compress_named(compression, state.mcap_chunk);

  std::vector<std::uint8_t> rec;
  mcap_write_u64(rec, static_cast<std::uint64_t>(state.mcap_chunk_start == kMaxTime ? 0 : state.mcap_chunk_start));
  mcap_write_u64(rec, static_cast<std::uint64_t>(state.mcap_chunk_end));
  mcap_write_u64(rec, static_cast<std::uint64_t>(state.mcap_chunk.size()));
  mcap_write_u32(rec, 0);
  mcap_write_string(rec, compression);
  mcap_write_u64(rec, static_cast<std::uint64_t>(compressed.size()));
  rec.insert(rec.end(), compressed.begin(), compressed.end());
  mcap_write_record(state.file, 0x06, rec);

  state.mcap_chunk.clear();
  state.mcap_chunk_start = kMaxTime;
  state.mcap_chunk_end = 0;
}

void close_mcap(detail::WriterState& state) {
  write_mcap_chunk(state);
  std::vector<std::uint8_t> footer;
  mcap_write_u64(footer, 0);
  mcap_write_u64(footer, 0);
  mcap_write_u32(footer, 0);
  mcap_write_record(state.file, 0x02, footer);
  state.file.write("\x89MCAP0\r\n", 8);
  state.file.close();
}

}  // namespace

Error::Error(const std::string& message) : std::runtime_error(message) {}
Error::Error(const char* message) : std::runtime_error(message) {}

Connection::Connection(std::shared_ptr<detail::ConnectionState> state) : state_(std::move(state)) {}

auto Connection::valid() const noexcept -> bool {
  return static_cast<bool>(state_);
}
auto Connection::id() const -> int { return require_connection_state(state_).id; }
auto Connection::topic() const -> const std::string& { return require_connection_state(state_).topic; }
auto Connection::msgtype() const -> const std::string& { return require_connection_state(state_).msgtype; }
auto Connection::msgdef_format() const -> MessageDefinitionFormat { return require_connection_state(state_).msgdef_format; }
auto Connection::msgdef_data() const -> const std::string& { return require_connection_state(state_).msgdef_data; }
auto Connection::digest() const -> const std::string& { return require_connection_state(state_).digest; }
auto Connection::serialization_format() const -> const std::string& { return require_connection_state(state_).serialization_format; }
auto Connection::offered_qos_profiles() const -> const std::string& { return require_connection_state(state_).offered_qos_profiles; }
auto Connection::callerid() const -> const std::optional<std::string>& { return require_connection_state(state_).callerid; }
auto Connection::latching() const -> const std::optional<int>& { return require_connection_state(state_).latching; }
auto Connection::msgcount() const -> std::int64_t { return require_connection_state(state_).msgcount; }
auto Connection::bag_format() const -> BagFormat { return require_connection_state(state_).bag_format; }

TypedValue::TypedValue() = default;
TypedValue::~TypedValue() = default;
TypedValue::TypedValue(const TypedValue&) = default;
auto TypedValue::operator=(const TypedValue&) -> TypedValue& = default;
TypedValue::TypedValue(TypedValue&&) noexcept = default;
auto TypedValue::operator=(TypedValue&&) noexcept -> TypedValue& = default;
TypedValue::TypedValue(std::shared_ptr<detail::TypedValueState> state) : state_(std::move(state)) {}

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
void expect_kind(const TypedValue& value, TypedValueKind kind, const std::string& context) {
  if (value.kind() != kind) {
    throw Error("Unexpected typed value kind for " + context);
  }
}
auto TypedValue::as_bool() const -> bool { expect_kind(*this, TypedValueKind::Bool, "bool"); return state_->bool_value; }
auto TypedValue::as_int() const -> std::int64_t { expect_kind(*this, TypedValueKind::Int, "int"); return state_->int_value; }
auto TypedValue::as_uint() const -> std::uint64_t { expect_kind(*this, TypedValueKind::UInt, "uint"); return state_->uint_value; }
auto TypedValue::as_double() const -> double { expect_kind(*this, TypedValueKind::Float, "float"); return state_->double_value; }
auto TypedValue::as_string() const -> std::string { expect_kind(*this, TypedValueKind::String, "string"); return state_->string_value; }
auto TypedValue::as_message() const -> TypedMessage { expect_kind(*this, TypedValueKind::Message, "message"); return state_->message_value; }
auto TypedValue::as_array() const -> std::vector<TypedValue> { expect_kind(*this, TypedValueKind::Array, "array"); return state_->array_value; }

TypedMessage::TypedMessage() = default;
TypedMessage::~TypedMessage() = default;
TypedMessage::TypedMessage(const TypedMessage&) = default;
auto TypedMessage::operator=(const TypedMessage&) -> TypedMessage& = default;
TypedMessage::TypedMessage(TypedMessage&&) noexcept = default;
auto TypedMessage::operator=(TypedMessage&&) noexcept -> TypedMessage& = default;
TypedMessage::TypedMessage(std::shared_ptr<detail::TypedMessageState> state) : state_(std::move(state)) {}
auto TypedMessage::valid() const noexcept -> bool { return static_cast<bool>(state_); }
auto TypedMessage::msgtype() const -> const std::string& { return require_typed_message_state(state_).msgtype; }
auto TypedMessage::field_names() const -> std::vector<std::string> {
  const auto& state = require_typed_message_state(state_);
  std::vector<std::string> result;
  result.reserve(state.fields.size());
  for (const auto& field : state.fields) {
    result.push_back(field.first);
  }
  return result;
}
auto TypedMessage::fields() const -> std::vector<std::pair<std::string, TypedValue>> {
  return require_typed_message_state(state_).fields;
}
auto TypedMessage::get(const std::string& field_name) const -> TypedValue {
  return field_value(*this, field_name);
}
void TypedMessage::set(const std::string& field_name, const TypedValue& value) {
  auto* field = mutable_field(*this, field_name);
  if (!field) {
    throw Error("Unknown field '" + field_name + "' for message type '" + msgtype() + "'");
  }
  field->second = value;
}

Typestore::Typestore(TypestorePreset preset) : state_(std::make_shared<detail::TypestoreState>()) {
  register_generated_types(state_->types, preset);
}
Typestore::Typestore(std::shared_ptr<detail::TypestoreState> state) : state_(std::move(state)) {}
Typestore::~Typestore() = default;
Typestore::Typestore(const Typestore&) = default;
auto Typestore::operator=(const Typestore&) -> Typestore& = default;
Typestore::Typestore(Typestore&&) noexcept = default;
auto Typestore::operator=(Typestore&&) noexcept -> Typestore& = default;

void Typestore::register_msg(const std::string& msgtype, const std::string& msgdef) {
  if (!state_) {
    throw Error("Invalid rosbags typestore");
  }
  parse_msg_definition(state_->types, normalize_msgtype(msgtype), msgdef);
}

void Typestore::register_idl(const std::string& idl_text) {
  if (!state_) {
    throw Error("Invalid rosbags typestore");
  }
  parse_idl_definition(state_->types, idl_text);
}

auto Typestore::create(
    const std::string& msgtype,
    std::vector<std::pair<std::string, TypedValue>> fields) const -> TypedMessage {
  const auto& state = require_typestore_state(state_);
  const auto normalized = normalize_msgtype(msgtype);
  const auto& type = require_type(state_, normalized);
  for (const auto& field : fields) {
    const auto found = std::find_if(type.fields.begin(), type.fields.end(), [&](const FieldDef& item) {
      return item.name == field.first;
    });
    if (found == type.fields.end()) {
      throw Error("Unknown field '" + field.first + "' for message type '" + normalized + "'");
    }
  }
  auto message_state = std::make_shared<detail::TypedMessageState>();
  message_state->typestore = state_;
  message_state->msgtype = normalized;
  for (const auto& field : type.fields) {
    auto found = std::find_if(fields.begin(), fields.end(), [&](const auto& item) {
      return item.first == field.name;
    });
    message_state->fields.emplace_back(
        field.name, found == fields.end() ? default_for_desc(state_, field.desc) : found->second);
  }
  return detail::make_typed_message(std::move(message_state));
}

auto Typestore::deserialize_ros1(
    const std::vector<std::uint8_t>& data,
    const std::string& msgtype) const -> TypedMessage {
  const auto normalized = normalize_msgtype(msgtype);
  const auto& type = require_type(state_, normalized);
  std::size_t pos = 0;
  auto message_state = std::make_shared<detail::TypedMessageState>();
  message_state->typestore = state_;
  message_state->msgtype = normalized;
  for (const auto& field : type.fields) {
    message_state->fields.emplace_back(field.name, read_ros1_value(data, pos, state_, field.desc));
  }
  if (pos != data.size()) {
    throw Error("ROS1 deserializer did not consume all bytes");
  }
  return detail::make_typed_message(std::move(message_state));
}

auto Typestore::serialize_ros1(const TypedMessage& message) const -> std::vector<std::uint8_t> {
  const auto& msg_state = require_typed_message_state(detail::typed_message_state(message));
  const auto& type = require_type(state_, msg_state.msgtype);
  std::vector<std::uint8_t> out;
  for (const auto& field : type.fields) {
    write_ros1_value(out, state_, field.desc, field_value(message, field.name));
  }
  return out;
}

auto Typestore::deserialize_cdr(
    const std::vector<std::uint8_t>& data,
    const std::string& msgtype) const -> TypedMessage {
  if (data.size() < 4) {
    throw Error("CDR data is too short");
  }
  const bool little_endian = data[1] != 0;
  const auto normalized = normalize_msgtype(msgtype);
  const auto& type = require_type(state_, normalized);
  std::vector<std::uint8_t> body(data.begin() + 4, data.end());
  std::size_t pos = 0;
  auto message_state = std::make_shared<detail::TypedMessageState>();
  message_state->typestore = state_;
  message_state->msgtype = normalized;
  for (const auto& field : type.fields) {
    message_state->fields.emplace_back(field.name, read_cdr_value(body, pos, state_, field.desc, little_endian));
  }
  return detail::make_typed_message(std::move(message_state));
}

auto Typestore::serialize_cdr(const TypedMessage& message, bool little_endian) const
    -> std::vector<std::uint8_t> {
  const auto& msg_state = require_typed_message_state(detail::typed_message_state(message));
  const auto& type = require_type(state_, msg_state.msgtype);
  std::vector<std::uint8_t> body;
  for (const auto& field : type.fields) {
    write_cdr_value(body, state_, field.desc, field_value(message, field.name), little_endian);
  }
  std::vector<std::uint8_t> out = {0, static_cast<std::uint8_t>(little_endian ? 1 : 0), 0, 0};
  out.insert(out.end(), body.begin(), body.end());
  return out;
}

auto Typestore::deserialize_raw(
    const std::vector<std::uint8_t>& data,
    const std::string& msgtype,
    BagFormat format) const -> TypedMessage {
  return format == BagFormat::Rosbag1 ? deserialize_ros1(data, msgtype) : deserialize_cdr(data, msgtype);
}

auto Typestore::serialize_raw(const TypedMessage& message, BagFormat format) const
    -> std::vector<std::uint8_t> {
  return format == BagFormat::Rosbag1 ? serialize_ros1(message) : serialize_cdr(message);
}

auto Typestore::ros1_to_cdr(
    const std::vector<std::uint8_t>& data,
    const std::string& msgtype) const -> std::vector<std::uint8_t> {
  return serialize_cdr(deserialize_ros1(data, msgtype));
}

auto Typestore::cdr_to_ros1(
    const std::vector<std::uint8_t>& data,
    const std::string& msgtype) const -> std::vector<std::uint8_t> {
  return serialize_ros1(deserialize_cdr(data, msgtype));
}

auto Typestore::connection_spec(
    std::string topic,
    std::string msgtype,
    BagFormat format,
    std::string serialization_format) const -> ConnectionSpec {
  const auto normalized = normalize_msgtype(msgtype);
  std::map<std::string, std::pair<std::string, std::string>> subdefs;
  auto generated = gendefhash(state_, normalized, subdefs, format == BagFormat::Rosbag1 ? 1 : 2);
  for (const auto& item : subdefs) {
    generated.first += std::string(80, '=') + "\nMSG: " + denormalize_msgtype(item.first) + "\n" + item.second.first;
  }
  ConnectionSpec spec;
  spec.topic = std::move(topic);
  spec.msgtype = normalized;
  spec.msgdef_format = MessageDefinitionFormat::Msg;
  spec.msgdef_data = generated.first;
  spec.digest = format == BagFormat::Rosbag1 ? generated.second : [&]() {
    std::map<std::string, std::string> cache;
    const auto root = struct_json(state_, normalized, cache);
    std::ostringstream json;
    json << "{\"type_description\": " << root << ", \"referenced_type_descriptions\": [";
    bool first = true;
    for (const auto& item : cache) {
      if (item.first == normalized) {
        continue;
      }
      if (!first) {
        json << ", ";
      }
      first = false;
      json << item.second;
    }
    json << "]}";
    return "RIHS01_" + sha256_hex(json.str());
  }();
  spec.serialization_format = std::move(serialization_format);
  return spec;
}

MessageStream::MessageStream() = default;
MessageStream::~MessageStream() = default;
MessageStream::MessageStream(std::shared_ptr<detail::MessageStreamState> state) : state_(std::move(state)) {}
MessageStream::MessageStream(MessageStream&&) noexcept = default;
auto MessageStream::operator=(MessageStream&&) noexcept -> MessageStream& = default;
auto MessageStream::next(Message& message) -> bool {
  if (!state_) {
    return false;
  }
  if (state_->reader && state_->reader->bag_format == BagFormat::Rosbag1) {
    if (state_->index >= state_->ros1_entries.size()) {
      return false;
    }
    read_rosbag1_message_at(
        *state_->reader,
        state_->ros1_stream,
        state_->ros1_cached_chunk_pos,
        state_->ros1_chunk_data,
        state_->ros1_entries[state_->index++],
        message);
    return true;
  }
  if (state_->index >= state_->messages.size()) {
    return false;
  }
  const auto& src = state_->messages[state_->index++];
  message.connection = src.connection;
  message.timestamp = src.timestamp;
  message.data = src.data;
  return true;
}

Reader::Reader(std::vector<std::string> paths, ReaderOptions options)
    : state_(std::make_shared<detail::ReaderState>(std::move(paths), options)) {
  if (state_->paths.empty()) {
    throw Error("Reader requires at least one path");
  }
}
Reader::Reader(std::initializer_list<std::string> paths, ReaderOptions options)
    : Reader(std::vector<std::string>(paths), options) {}
Reader::Reader(std::string path, ReaderOptions options) : Reader(std::vector<std::string>{std::move(path)}, options) {}
Reader::~Reader() = default;
Reader::Reader(Reader&&) noexcept = default;
auto Reader::operator=(Reader&&) noexcept -> Reader& = default;

void Reader::open() {
  fs::path path(state_->paths.front());
  if (!fs::exists(path)) {
    throw Error("Path does not exist");
  }
  if (fs::is_regular_file(path) && path.extension() == ".bag") {
    open_rosbag1(*state_);
  } else if (fs::is_directory(path)) {
    open_rosbag2_dir(*state_, path);
  } else if (path.extension() == ".db3") {
    state_->bag_format = BagFormat::Rosbag2;
    state_->storage = StoragePlugin::Sqlite3;
    open_sqlite_storage(*state_, path);
  } else if (path.extension() == ".mcap") {
    open_mcap_storage(*state_, path);
  } else {
    throw Error("Unsupported bag path '" + path.string() + "'");
  }
  state_->is_open = true;
}

void Reader::close() {
  if (!state_) {
    return;
  }
  state_->is_open = false;
}
auto Reader::is_open() const noexcept -> bool { return state_ && state_->is_open; }
auto Reader::bag_format() const -> BagFormat { return state_->bag_format; }
auto Reader::connections() const -> std::vector<Connection> { require_reader_open(*state_); return state_->connections; }
auto Reader::messages(ReaderMessageOptions options) -> MessageStream {
  require_reader_open(*state_);
  if (state_->bag_format == BagFormat::Rosbag1) {
    auto stream_state = std::make_shared<detail::MessageStreamState>();
    stream_state->reader = state_;
    stream_state->ros1_entries = rosbag1_sorted_entries(*state_, options);
    stream_state->ros1_stream.open(state_->paths.front(), std::ios::binary);
    if (!stream_state->ros1_stream) {
      throw Error("Could not open rosbag1 file");
    }
    return MessageStream(std::move(stream_state));
  }
  std::vector<NativeMessage> messages;
  if (state_->storage == StoragePlugin::Sqlite3 && !state_->paths.empty() && fs::path(state_->paths.front()).extension() == ".db3") {
    messages = collect_sqlite_messages(*state_, state_->paths.front(), options);
  } else {
    const auto wanted = selected_connection_ids(state_->connections, options.connection_ids);
    for (const auto& msg : state_->eager_messages) {
      if (wanted.count(msg.connection.id()) == 0) {
        continue;
      }
      if (options.start_time && msg.timestamp < *options.start_time) {
        continue;
      }
      if (options.stop_time && msg.timestamp >= *options.stop_time) {
        continue;
      }
      auto copy = msg;
      if (state_->rosbag2_message_compression) {
        copy.data = zstd_decompress(copy.data);
      }
      messages.push_back(std::move(copy));
    }
  }
  auto stream_state = std::make_shared<detail::MessageStreamState>();
  stream_state->messages = std::move(messages);
  return MessageStream(std::move(stream_state));
}
auto Reader::typestore() const -> Typestore {
  require_reader_open(*state_);
  ensure_reader_typestore(*state_);
  return state_->typestore;
}
auto Reader::deserialize(const Message& message) const -> TypedMessage {
  require_reader_open(*state_);
  ensure_reader_typestore(*state_);
  return state_->typestore.deserialize_raw(message.data, message.connection.msgtype(), state_->bag_format);
}
auto Reader::duration() const -> std::int64_t {
  require_reader_open(*state_);
  return std::max<std::int64_t>(0, state_->end_time - state_->start_time);
}
auto Reader::start_time() const -> std::int64_t { require_reader_open(*state_); return state_->start_time; }
auto Reader::end_time() const -> std::int64_t { require_reader_open(*state_); return state_->end_time; }
auto Reader::message_count() const -> std::int64_t { require_reader_open(*state_); return state_->message_count; }

Writer::Writer(std::string path, WriterOptions options)
    : state_(std::make_shared<detail::WriterState>(std::move(path), std::move(options))) {}
Writer::~Writer() = default;
Writer::Writer(Writer&&) noexcept = default;
auto Writer::operator=(Writer&&) noexcept -> Writer& = default;

void Writer::open() {
  if (state_->options.format == BagFormat::Rosbag1) {
    state_->file.open(state_->path, std::ios::binary | std::ios::out | std::ios::trunc);
    if (!state_->file) {
      throw Error("Could not open rosbag1 writer");
    }
    state_->file.write("#ROSBAG V2.0\n", 13);
    RecordHeader header;
    set_u64(header, "index_pos", 0);
    set_u32(header, "conn_count", 0);
    set_u32(header, "chunk_count", 0);
    const auto size = write_header(state_->file, header, 3);
    const auto padsize = 4096 - 4 - size;
    write_le<std::uint32_t>(state_->file, static_cast<std::uint32_t>(padsize));
    std::string padding(padsize, ' ');
    state_->file.write(padding.data(), static_cast<std::streamsize>(padding.size()));
  } else {
    fs::create_directories(state_->path);
    const fs::path dir(state_->path);
    if (state_->options.storage == StoragePlugin::Sqlite3) {
      state_->storage_path = dir / (dir.filename().string() + ".db3");
      if (sqlite3_open(state_->storage_path.string().c_str(), &state_->sqlite) != SQLITE_OK) {
        throw Error("Could not open sqlite3 writer");
      }
      sqlite_prepare_schema(state_->sqlite);
    } else {
      state_->storage_path = dir / (dir.filename().string() + ".mcap");
      state_->file.open(state_->storage_path, std::ios::binary | std::ios::out | std::ios::trunc);
      state_->file.write("\x89MCAP0\r\n", 8);
      std::vector<std::uint8_t> rec;
      mcap_write_string(rec, "ros2");
      mcap_write_string(rec, "rosbags-cpp-native");
      mcap_write_record(state_->file, 0x01, rec);
    }
  }
  state_->is_open = true;
}

void Writer::close() {
  if (!state_ || !state_->is_open) {
    return;
  }
  if (state_->options.format == BagFormat::Rosbag1) {
    write_rosbag1_chunk(*state_);
    const auto index_pos = static_cast<std::uint64_t>(state_->file.tellp());
    for (const auto& connection : state_->connections) {
      write_ros1_connection_record(connection, state_->file);
    }
    for (const auto& chunk : state_->written_chunks) {
      RecordHeader header;
      set_u32(header, "ver", 1);
      set_u64(header, "chunk_pos", chunk.pos);
      set_time(header, "start_time", chunk.start == kMaxTime ? 0 : chunk.start);
      set_time(header, "end_time", chunk.end);
      set_u32(header, "count", static_cast<std::uint32_t>(chunk.connections.size()));
      write_header(state_->file, header, 6);
      write_le<std::uint32_t>(state_->file, static_cast<std::uint32_t>(chunk.connections.size() * 8));
      for (const auto& [cid, items] : chunk.connections) {
        write_le<std::uint32_t>(state_->file, static_cast<std::uint32_t>(cid));
        write_le<std::uint32_t>(state_->file, static_cast<std::uint32_t>(items.size()));
      }
    }
    state_->file.seekp(13);
    RecordHeader header;
    set_u64(header, "index_pos", index_pos);
    set_u32(header, "conn_count", static_cast<std::uint32_t>(state_->connections.size()));
    set_u32(header, "chunk_count", static_cast<std::uint32_t>(state_->written_chunks.size()));
    const auto size = write_header(state_->file, header, 3);
    const auto padsize = 4096 - 4 - size;
    write_le<std::uint32_t>(state_->file, static_cast<std::uint32_t>(padsize));
    std::string padding(padsize, ' ');
    state_->file.write(padding.data(), static_cast<std::streamsize>(padding.size()));
    state_->file.close();
  } else if (state_->options.storage == StoragePlugin::Sqlite3) {
    const auto metadata = make_metadata_yaml(*state_, state_->storage_path);
    sqlite3_stmt* stmt = nullptr;
    sqlite3_prepare_v2(state_->sqlite, "INSERT INTO metadata(metadata_version, metadata) VALUES(?, ?)", -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, state_->options.rosbag2_version);
    sqlite_bind_text(stmt, 2, metadata);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (!state_->connections.empty()) {
      sqlite_exec(state_->sqlite, "COMMIT;");
    }
    sqlite_exec(state_->sqlite, "PRAGMA optimize;");
    sqlite3_close(state_->sqlite);
    state_->sqlite = nullptr;
    fs::path final_storage = state_->storage_path;
    if (state_->options.compression_mode == CompressionMode::File) {
      auto compressed = zstd_compress(read_file(state_->storage_path));
      final_storage = state_->storage_path;
      final_storage += ".zstd";
      write_file(final_storage, compressed);
      fs::remove(state_->storage_path);
    }
    std::ofstream meta(fs::path(state_->path) / "metadata.yaml");
    meta << make_metadata_yaml(*state_, final_storage);
  } else {
    close_mcap(*state_);
    fs::path final_storage = state_->storage_path;
    if (state_->options.compression_mode == CompressionMode::File) {
      auto compressed = zstd_compress(read_file(state_->storage_path));
      final_storage = state_->storage_path;
      final_storage += ".zstd";
      write_file(final_storage, compressed);
      fs::remove(state_->storage_path);
    }
    std::ofstream meta(fs::path(state_->path) / "metadata.yaml");
    meta << make_metadata_yaml(*state_, final_storage);
  }
  state_->is_open = false;
}

auto Writer::is_open() const noexcept -> bool { return state_ && state_->is_open; }

auto Writer::add_connection(const Connection& connection) -> Connection {
  require_writer_open(*state_);
  const auto& source = require_connection_state(detail::connection_state(connection));
  if (source.bag_format != state_->options.format) {
    throw Error("Cannot add raw connection from different bag format");
  }
  return add_connection(spec_from_connection(connection));
}

auto Writer::add_connection(const ConnectionSpec& input_spec) -> Connection {
  require_writer_open(*state_);
  ConnectionSpec spec = input_spec;
  validate_connection_spec(spec, state_->options.format);
  const int id = state_->options.format == BagFormat::Rosbag1
                     ? static_cast<int>(state_->connections.size())
                     : static_cast<int>(state_->connections.size() + 1);
  auto connection = make_connection_from_spec(spec, id, state_->options.format);
  state_->connections.push_back(connection);
  if (state_->options.format == BagFormat::Rosbag1) {
    append_ros1_connection_record(connection, state_->chunk);
  } else if (state_->options.storage == StoragePlugin::Sqlite3) {
    sqlite3_stmt* stmt = nullptr;
    sqlite3_prepare_v2(state_->sqlite, "INSERT INTO message_definitions (topic_type, encoding, encoded_message_definition, type_description_hash) VALUES(?, ?, ?, ?)", -1, &stmt, nullptr);
    sqlite_bind_text(stmt, 1, spec.msgtype);
    sqlite_bind_text(stmt, 2, spec.msgdef_format == MessageDefinitionFormat::Idl ? "ros2idl" : "ros2msg");
    sqlite_bind_text(stmt, 3, spec.msgdef_data);
    sqlite_bind_text(stmt, 4, spec.digest);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    sqlite3_prepare_v2(state_->sqlite, "INSERT INTO topics VALUES(?, ?, ?, ?, ?, ?)", -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, id);
    sqlite_bind_text(stmt, 2, spec.topic);
    sqlite_bind_text(stmt, 3, spec.msgtype);
    sqlite_bind_text(stmt, 4, spec.serialization_format);
    sqlite_bind_text(stmt, 5, spec.offered_qos_profiles);
    sqlite_bind_text(stmt, 6, spec.digest);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (state_->connections.size() == 1) {
      sqlite_exec(state_->sqlite, "BEGIN TRANSACTION;");
    }
  } else {
    write_mcap_schema_channel(state_->file, connection);
  }
  return connection;
}

auto Writer::add_connection(
    std::string topic,
    std::string msgtype,
    const Typestore& typestore,
    std::string serialization_format) -> Connection {
  return add_connection(typestore.connection_spec(std::move(topic), std::move(msgtype), state_->options.format, std::move(serialization_format)));
}

void Writer::write(
    const Connection& connection,
    std::int64_t timestamp,
    const std::vector<std::uint8_t>& data) {
  require_writer_open(*state_);
  const auto& conn = require_connection_state(detail::connection_state(connection));
  auto found = std::find_if(state_->connections.begin(), state_->connections.end(), [&](const Connection& item) {
    return item.id() == conn.id;
  });
  if (found == state_->connections.end()) {
    throw Error("There is no connection registered with this writer");
  }
  auto& stored_conn = *detail::connection_state(*found);
  stored_conn.msgcount += 1;
  state_->min_timestamp = std::min(state_->min_timestamp, timestamp);
  state_->max_timestamp = std::max(state_->max_timestamp, timestamp);
  state_->total_messages += 1;
  if (state_->options.format == BagFormat::Rosbag1) {
    const auto offset = static_cast<std::uint32_t>(state_->chunk.size());
    state_->chunk_connections[conn.id].push_back({timestamp, offset});
    state_->chunk_start = std::min(state_->chunk_start, timestamp);
    state_->chunk_end = std::max(state_->chunk_end, timestamp);
    RecordHeader header;
    set_u32(header, "conn", static_cast<std::uint32_t>(conn.id));
    set_time(header, "time", timestamp);
    append_header(state_->chunk, header, 2);
    append_sized(state_->chunk, data);
    if (state_->chunk.size() > state_->options.chunk_threshold) {
      write_rosbag1_chunk(*state_);
    }
  } else if (state_->options.storage == StoragePlugin::Sqlite3) {
    auto payload = data;
    if (state_->options.compression_mode == CompressionMode::Message) {
      payload = zstd_compress(payload);
    }
    sqlite3_stmt* stmt = nullptr;
    sqlite3_prepare_v2(state_->sqlite, "INSERT INTO messages (topic_id, timestamp, data) VALUES(?, ?, ?)", -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, conn.id);
    sqlite3_bind_int64(stmt, 2, timestamp);
    sqlite3_bind_blob(stmt, 3, payload.data(), static_cast<int>(payload.size()), SQLITE_TRANSIENT);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
  } else {
    auto payload = data;
    if (state_->options.compression_mode == CompressionMode::Message) {
      payload = zstd_compress(payload);
    }
    std::vector<std::uint8_t> rec;
    mcap_write_u16(rec, static_cast<std::uint16_t>(conn.id));
    mcap_write_u32(rec, 0);
    mcap_write_u64(rec, static_cast<std::uint64_t>(timestamp));
    mcap_write_u64(rec, static_cast<std::uint64_t>(timestamp));
    rec.insert(rec.end(), payload.begin(), payload.end());
    if (state_->options.compression_mode == CompressionMode::Storage) {
      state_->mcap_chunk_start = std::min(state_->mcap_chunk_start, timestamp);
      state_->mcap_chunk_end = std::max(state_->mcap_chunk_end, timestamp);
      mcap_append_record(state_->mcap_chunk, 0x05, rec);
      if (state_->mcap_chunk.size() > state_->options.chunk_threshold) {
        write_mcap_chunk(*state_);
      }
    } else {
      mcap_write_record(state_->file, 0x05, rec);
    }
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
