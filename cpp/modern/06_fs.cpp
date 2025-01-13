#include <cstdint>
#include <fstream>
#include <iostream>
#include <stdexcept>

int main() {
  std::ifstream file("input.txt");
  if (!file) throw std::runtime_error("failed to open file");

  file.seekg(0, std::ios::end);
  std::streamsize size = file.tellg();
  file.seekg(0, std::ios::beg);

  std::vector<uint8_t> buf(size);
  if (file.read(reinterpret_cast<char*>(buf.data()), size)) {
    std::cout << "file read with " << size << " bytes\n";
  }

  for (size_t i = 0; i < buf.size(); i++) {
    std::cout << "0x" << std::hex << static_cast<int>(buf[i]) << " ";
  }
  std::cout << std::dec << '\n';

  std::string content(buf.begin(), buf.end());
  std::cout << "content: " << content << '\n';
}
