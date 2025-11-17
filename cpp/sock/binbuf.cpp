#include <cassert>
#include <cstdint>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

using std::cout;

class BinBuffer {
 private:
  std::vector<char> buf;
  size_t offset = 0;

  void compact() {
    if (offset == 0) return;
    buf.erase(buf.begin(), buf.begin() + offset);
    offset = 0;
  }

 public:
  void put_u8(uint8_t n) {
    buf.push_back(n);
  }

  void put_u32(uint32_t n) {
    buf.push_back((uint8_t)(n >> 24) & 0xff);
    buf.push_back((uint8_t)(n >> 16) & 0xff);
    buf.push_back((uint8_t)(n >> 8) & 0xff);
    buf.push_back((uint8_t)(n & 0xff));
  }

  void put_str(const std::string& s) {
    put_u32(s.size());
    buf.insert(buf.end(), s.begin(), s.end());
  }

  std::optional<uint8_t> get_u8() {
    if (offset + 1 > buf.size()) return std::nullopt;
    uint8_t value = buf[offset];
    offset += 1;
    return value;
  }

  std::optional<uint32_t> get_u32() {
    if (offset + 4 > buf.size()) return std::nullopt;
    uint32_t value = ((uint8_t)buf[offset] << 24) | ((uint8_t)buf[offset + 1] << 16) |
                     ((uint8_t)buf[offset + 2] << 8) | ((uint8_t)buf[offset + 3]);
    offset += 4;
    return value;
  }

  std::optional<std::string> get_str(uint32_t len) {
    if (offset + len > buf.size()) return std::nullopt;
    std::string value(buf.begin() + offset, buf.begin() + offset + len);
    offset += len;
    return value;
  }

  std::optional<std::string> read_frame() {
    size_t prev_offset = offset;

    auto lenopt = get_u32();
    if (!lenopt) {
      offset = prev_offset;
      return std::nullopt;
    }

    uint32_t len = lenopt.value();
    auto stropt = get_str(len);
    if (!stropt) {
      offset = prev_offset;
      return std::nullopt;
    }

    compact();
    return stropt;
  }
};

void test_frame() {
  BinBuffer buf;

  buf.put_str("hello");
  buf.put_str("world");

  auto m1 = buf.read_frame();
  assert(m1.has_value());

  cout << "Frame 1: " << *m1 << '\n';

  auto m2 = buf.read_frame();
  assert(m2.has_value());

  cout << "Frame 2: " << *m2 << '\n';
}

void test_partial() {
  BinBuffer buf;

  // Part 1 arrives
  buf.put_u32(5);
  buf.put_u8('h');
  buf.put_u8('e');

  // Try to read (should fail)
  auto partial = buf.read_frame();
  assert(!partial.has_value());

  // Part 2 arrives
  buf.put_u8('l');
  buf.put_u8('l');
  buf.put_u8('o');

  // We now have a full frame
  auto full = buf.read_frame();
  assert(full.has_value());

  cout << *full << '\n';
}

int main() {
  test_frame();
  test_partial();
}
