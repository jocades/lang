#include <assert.h>

#include <atomic>
#include <cerrno>
#include <deque>
#include <iostream>
#include <memory>
#include <system_error>
#include <thread>

using namespace std;

template <typename T>
class Shared {
 public:
  mutex mtx;
  atomic<size_t> senders;
  deque<T> queue;
  condition_variable avail;

  void debug() const {
    cout << "Shared(senders=" << senders << ", queue=" << queue.size() << ")\n";
  }
};

template <typename T>
class Sender {
 private:
  shared_ptr<Shared<T>> shared;

 public:
  Sender(shared_ptr<Shared<T>> shared) : shared(shared) {
    cout << "Sender Constructor\n";
  };

  Sender(const Sender& other) : shared(other.shared) {
    shared->senders++;  // fetch_add(1, memory_order_acq_rel)
  }

  void send(const T&& data) {
    shared->mtx.lock();
    shared->queue.emplace_back(data);
    shared->mtx.unlock();
    shared->avail.notify_one();
  }

  void debug() const {
    cout << "Sender() |- ";
    shared->debug();
  }

  // Sender(Sender& other) {
  //   cout << "Sender Copy\n";
  //   shared->mtx.lock();
  //   shared->senders++;
  //   shared->mtx.unlock();
  // }

  // Sender clone() {}

  ~Sender() {
    cout << "Drop Sender\n";
    shared->senders--;
    bool last = shared->senders == 0;
    // Make sure to wake up the receiver since it may be waiting but there are
    // no active senders left.
    if (last) shared->avail.notify_one();
  }
};

template <typename T>
class Receiver {
 private:
  shared_ptr<Shared<T>> shared;
  deque<T> buffer;

 public:
  Receiver(shared_ptr<Shared<T>> shared) : shared(shared) {
    cout << "Receiver Constructor\n";
  }

  optional<T> recv() {
    if (!buffer.empty()) {
      T data = std::move(buffer.front());
      buffer.pop_front();
      return data;
    }

    unique_lock<mutex> guard(shared->mtx);
    while (true) {
      if (!shared->queue.empty()) {
        if (shared->senders == 0) return nullopt;
        T data = std::move(shared->queue.front());
        shared->queue.pop_front();
        std::swap(buffer, shared->queue);
        return data;
      }
      shared->avail.wait(guard);
      cout << "waiting for avail" << endl;
    }
  }

  void debug() const {
    cout << "Receiver(buffer=" << buffer.size() << " |- ";
    shared->debug();
  }

  ~Receiver() {
    cout << "Drop Receiver\n";
  }
};

template <typename T>
pair<Sender<T>, Receiver<T>> channel() {
  shared_ptr<Shared<T>> shared = make_shared<Shared<T>>();
  return make_pair(Sender<T>(shared), Receiver<T>(shared));
}

class W {
 public:
  int v;

  W() {
    cout << "W Constructor\n";
  }

  W(int v) : v(v) {
    cout << "W Constructor with v\n";
  }

  W(const W& other) {
    v = other.v;
    cout << "W Copy Constructor\n";
  };

  W(W&& other) noexcept {
    v = other.v;
    other.v = -1;
    cout << "W Move Constructor\n";
  }
};

void test() {
  auto [tx, rx] = channel<W>();

  cout << "----------\n";

  thread([&rx]() mutable {
    cout << "Actor waiting for msg...\n";
    auto msg = rx.recv();
    if (msg) {
      cout << "Actor received " << msg->v << endl;
    } else {
      cout << "No senders! Shutting down..." << endl;
    }
  }).detach();

  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  tx.send(W(1));

  std::this_thread::sleep_for(std::chrono::seconds(2));

  // for (int i = 0; i < 5; i++) {
  //   tx.send(W(i));
  // }

  // actor.join();

  /* array<thread, 9> tasks;
  for (int i = 0; i < tasks.size(); i++) {
    tasks[i] = thread([]() {});
  } */
}

int main() {
  test();
}

/* struct User {
  string name;
  size_t age;

  User(string name, size_t age) : name(name), age(age) {}
  //
  // User(User& other) = delete;

  void display() const {
    cout << "User(name=" << name << ", age=" << age << ")\n";
  }
}; */

class User {
 public:
  string name;
  size_t age;

  User(const string& name, int age) : name(name), age(age) {
    cout << "Constructor\n";
  }

  User(User& other) : name(other.name), age(other.age) {
    cout << "Copy Constructor\n";
  }

  void display() const {
    cout << "User(name=" << name << ", age=" << age << ")\n";
  }
};

class X {
 public:
  W _w;

  X(W& w) : _w(std::move(w)) {
    cout << "X Constructor\n";
  }

  X(W&& w) : _w(std::move(w)) {
    cout << "X Move Constructor\n";
  }
};

W create() {
  W w;
  w.v = 10;
  return w;  // return value optimization (allocated where this function is called)
}

void recv() {
  deque<W> q;
  auto w = W(1);
  q.push_back(std::move(w));
  cout << w.v << '\n';

  cout << "size=" << q.size() << '\n';

  auto first = std::move(q.front());
  q.pop_front();
  cout << first.v << '\n';

  cout << "size=" << q.size() << '\n';

  if (!q.empty()) {
    auto& foo = q.front();
    cout << foo.v << '\n';
  }
}
