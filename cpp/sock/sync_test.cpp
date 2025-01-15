#include <atomic>
#include <cassert>
#include <deque>
#include <iostream>
#include <queue>
#include <thread>

using namespace std;

class W {
 private:
  int _data;

 public:
  explicit W(int data) : _data(data) {
    cout << "Construct\n";
  };

  W(const W& other) : _data(other._data) {
    cout << "Copy\n";
  }

  W(W&& other) : _data(other._data) {
    cout << "Move\n";
  }

  int data() const {
    return _data;
  }
};

ostream& operator<<(ostream& stream, const W& w) {
  stream << "W(" << w.data() << ')';
  return stream;
}

void dbg(const queue<W>& q) {
  cout << "size=" << q.size() << '\n';
}

size_t counter = 0;

constexpr size_t NUM_THREADS = 8;
constexpr size_t INC = 10000000000;

void inc() {
  for (size_t i = 0; i < INC; i++) {
    counter++;
  }
}

void test() {
  vector<thread> tasks;
  tasks.reserve(NUM_THREADS);

  for (size_t i = 0; i < NUM_THREADS; i++) tasks.emplace_back(inc);
  for (auto& task : tasks) task.join();

  cout << counter << '\n';
  assert(counter == NUM_THREADS * INC);
}

int main() {
  queue<W> q;

  W w1(1);
  q.emplace(std::move(w1));

  q.emplace(2);

  dbg(q);

  auto& first = q.front();
  q.pop();

  cout << first << '\n';
  test();

  /* deque<W> dq;
  dq.push_back(1);

  for () */
}
