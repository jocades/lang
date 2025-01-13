#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstdint>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <thread>

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

  int read(void* buf, size_t size) {
    return ::read(_sock, buf, size);
  }

  int write(const void* buf, size_t size) {
    return ::write(_sock, buf, size);
  }

  int write_all(const void* buf) {
    return 1;
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

void process(TcpStream stream) {
  u8 buf[1024];
  while (true) {
    int n = stream.read(buf, sizeof(buf));
    if (n == 0) break;
    if (n < 0) {
      cerr << "failed to read from socket\n";
      break;
    }

    string str(buf, buf + n);
    cout << "received " << n << " bytes -> ";

    string s = "hello\n";
    ::write(stream.sock(), s.data(), s.size());

    const char* cs = "hello\n";
    size_t len = sizeof(s);
    size_t sent = 0;

    while (sent < len) {
      const char* p = cs + sent;
      sent += stream.write(p, len);
    }

    memset(buf, 0, n);
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
      // process(std::move(stream));

      thread(process, std::move(stream)).detach();

      /* std::thread([&stream]() {
        const char* buf = "hello";
        write(stream.sock(), buf, strlen(buf));
        std::this_thread::sleep_for(std::chrono::seconds(5));
      }).detach(); */

    } catch (const std::exception& e) {
      cout << "Error: " << e.what() << '\n';
    }
  }
}
}  // namespace server

int wwrite(const void* buf) {
  return 2;
}

int main() {
  server::run();

  char s[] = "hello\n";
  size_t len = strlen(s);
  cout << "len=" << len << " size=" << sizeof(s) << '\n';

  cout << *(s + 4) << '=' << (int)*(s + 4) << '\n';

  string x(s + 2, len);
  cout << x;

  int n = 0;
  while (n < len) {
    cout << n << '\n';
    n += wwrite(s + n);
  }

  for (int i = 0; i < n; i++) {
    cout << (int)s[i] << ' ';
  }
  cout << '\n';
}
