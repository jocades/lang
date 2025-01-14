#include <fcntl.h>

#include <cerrno>
#include <iostream>
#include <system_error>

using namespace std;

int main() {
  int fd = open("abcd", O_RDONLY);

  if (fd == -1) {
    cerr << "Error opening file: " << strerror(errno) << '\n';
    // throw std::system_error(errno, std::system_category(), "failed to open file");
  }

  if (errno == ENOENT) {
    std::cerr << "File not found\n";
  }
}
