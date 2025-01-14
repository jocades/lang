#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cerrno>
#include <cstdint>
#include <iostream>
#include <memory>
#include <span>
#include <stdexcept>
#include <thread>

using namespace std;

void syserr(const char* ctx) {
  throw std::system_error(errno, std::system_category(), ctx);
}

class TcpStream {
 private:
  int _sock;

 public:
  explicit TcpStream(int fd) : _sock(fd) {}

  TcpStream(const TcpStream&) = delete;
  TcpStream operator=(const TcpStream&) = delete;

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

  ssize_t read(span<char> buf) {
    return ::read(_sock, buf.data(), buf.size());
  }

  ssize_t write(span<const char> bytes) {
    return ::write(_sock, bytes.data(), bytes.size());
  }

  ssize_t write_all(span<const char> bytes) {
    size_t size = bytes.size();
    size_t n = 0;

    while (n < size) {
      ssize_t w = ::write(_sock, bytes.data() + n, size - n);
      if (w < 0) {
        syserr("failed to write to socket");
        return n;
      }
      n += w;
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
    if (fd < 0) syserr("failed to create socket");

    int opt = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) != 0) {
      syserr("failed to set socket options");
    }

    sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr = {.s_addr = INADDR_ANY},
    };

    if (::bind(fd, (sockaddr*)&addr, sizeof(addr)) < 0) {
      syserr("failed to bind socket");
    }

    if (listen(fd, 5) < 0) syserr("failed to listen on socket");

    return TcpListener(fd);
  }

  TcpStream accept() {
    int fd = ::accept(_sock, nullptr, nullptr);
    if (fd < 0) syserr("failed to accept connection");
    return TcpStream(fd);
  }

  inline int sock() {
    return _sock;
  }
};

constexpr uint16_t PORT = 8000;

namespace server {
void run() {
  auto listener = TcpListener::bind(PORT);
  cout << "Listening on port " << PORT << "...\n";

  while (true) {
    try {
      auto stream = listener.accept();
      cout << "client connected\n";

      std::thread([stream = std::move(stream)]() mutable {
        array<char, 1024> buf;

        while (true) {
          int n = stream.read(buf);
          if (n == 0) break;
          cout << "READ " << n << '\n';

          string response = "echo -> " + string(buf.data(), n);
          int o = stream.write(response);
          cout << "WRITE " << o << '\n';
        }

        cout << "client disconneted\n";
      }).detach();

    } catch (const std::system_error& e) {
      cerr << "System Error: " << e.what() << '\n';
    } catch (const std::exception& e) {
      cerr << "Error: " << e.what() << '\n';
    }
  }
}
}  // namespace server

int main() {
  server::run();
}
