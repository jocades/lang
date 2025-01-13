#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstdint>
#include <iostream>
#include <memory>
#include <stdexcept>

using namespace std;  // remove in prod, only include what's needed, just testing here

class TcpStream {
 private:
  int _sock;

 public:
  explicit TcpStream(int fd) : _sock(fd) {}

  // Disable copy and assignment
  TcpStream(const TcpStream&) = delete;
  TcpStream operator=(const TcpStream&) = delete;

  // Enable move semantics
  TcpStream(TcpStream&& other) noexcept : _sock(other._sock) {
    other._sock = -1;
  }

  TcpStream& operator=(TcpStream&& other) {
    if (this != &other) {
      if (_sock != -1) close(_sock);
      _sock = other._sock;
      other._sock = -1;
    }
    return *this;
  }

  int read(uint8_t* buf, size_t size) {
    int n = ::read(_sock, buf, size);
    return n;
  }

  static size_t put(uint8_t* buf, size_t size) {
    if (!buf) return 0;
    size_t n = 0;
    for (; n < size; n++) {
      buf[n] = 'a' + n;
    }
    return n;
  }

  inline int sock() {
    return _sock;
  }

  ~TcpStream() {
    if (_sock != -1) close(_sock);
  }
};

class TcpListener {
 private:
  int _sock;
  explicit TcpListener(int fd) : _sock(fd) {}

 public:
  static TcpListener bind(uint16_t port) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) throw std::runtime_error("failed to create socket");

    int opt = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) != 0) {
      throw std::runtime_error("failed to set socket options");
    }

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_addr = {.s_addr = INADDR_ANY},
        .sin_port = htons(port),
    };

    if (::bind(fd, (sockaddr*)&addr, sizeof(addr)) < 0) {
      throw std::runtime_error("failed to bind socket");
    }

    if (listen(fd, 5) < 0) throw std::runtime_error("failed to listen on socket");

    return TcpListener(fd);
  }

  TcpStream accept() {
    int fd = ::accept(_sock, nullptr, nullptr);
    if (fd < 0) throw std::runtime_error("failed to accept connection");
    return TcpStream(fd);
  }

  inline int sock() {
    return _sock;
  }
};

typedef uint8_t u8;

int read(vector<u8>& buf) {
  // std::string x = "abcd";
  const char* x = "abcd";
  int n = 0;
  for (int i = 0; i < strlen(x); i++) {
    buf.push_back(*(x + i));
    n++;
  }
  return n;
}

void process(TcpStream stream) {
  u8 buf[1024];
  while (true) {
    int n = read(stream.sock(), buf, sizeof(buf));
    cout << "received " << n << " bytes\n";
    if (n == 0) break;
    if (n < 0) {
      std::cerr << "failed to read from socket\n";
      break;
    }
    write(stream.sock(), buf, n);
    memset(buf, 0, n);
    throw std::runtime_error("Oops!");
  }

  cout << "client disconnected\n'";
}

constexpr uint16_t PORT = 8000;

namespace server {
void run() {
  auto listener = TcpListener::bind(PORT);
  cout << "Listening on port " << PORT << "...\n";

  while (true) {
    try {
      auto stream = listener.accept();
      cout << "client connected\n";
      process(std::move(stream));

    } catch (const std::exception& e) {
      cout << "Error: " << e.what() << '\n';
    }
  }
}
}  // namespace server

int main() {
  server::run();
}
