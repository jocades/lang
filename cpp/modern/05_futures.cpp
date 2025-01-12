#include <future>
#include <iostream>
#include <thread>
#include <vector>

int compute(int x) {
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  return x * x;
}

void manually() {
  std::vector<std::future<int>> futures;

  // Spawn 8 threads and collect futures
  for (int i = 0; i < 8; i++) {
    // Creatge a promise and future pair
    std::promise<int> prom;
    futures.push_back(prom.get_future());

    std::thread([i, prom = std::move(prom)]() mutable {
      int result = compute(i);
      prom.set_value(result);
    }).detach();
  }

  // Collect results from each future
  for (auto& fut : futures) {
    std::cout << "computed result: " << fut.get() << '\n';
  }

  std::cout << "done!" << std::endl;
}

void with_async() {
  std::vector<std::future<int>> futures;

  for (int i = 0; i < 8; i++) {
    futures.push_back(std::async(std::launch::async, compute, i));
  }

  for (auto& fut : futures) {
    std::cout << "computed result: " << fut.get() << '\n';
  }

  std::cout << "done!" << std::endl;
}

template <typename T>
class Mutex {
 private:
  T inner;
  std::mutex mtx;

 public:
  Mutex(T v) : inner(std::move(v)) {}

  T& lock() {
    std::lock_guard<std::mutex> guard(mtx);
    return inner;
  }
};

void increment(Mutex<int>& counter) {
  auto& n = counter.lock();
  n += 1;
}

int main() {
  Mutex<int> counter(0);
  increment(std::ref(counter));

  auto& n = counter.lock();
  std::cout << n << std::endl;
}
