#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class TcpListener {
 public:
  static TcpListener bind(uint16_t port) {};
};

void handle_connection(TcpStream stream) {
  vector<char> buf;
  while (true) {
    int n = stream.read_until(buf, '\n');
    if (n == 0) break;
    cout << "Received " << buf << '\n';
  }
  cout << "Peer disconnected\n";
}

int main() {
  TcpListener listener = TcpListener::bind(8000);

  while (true) {
    auto stream = listener.accept();
    cout << "Peer connected " << stream.peer_addr() << '\n';
    handle_connection(stream);
  }
}
