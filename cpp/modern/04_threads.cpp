#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using std::cout;

void foo() {
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  cout << "foo done" << std::endl;
}

void basic_threads() {
  cout << "spawning first thread...\n";
  std::thread t1(foo);

  cout << "spawning second thread...\n";
  std::thread t2([]() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    cout << "bar done" << std::endl;
  });

  cout << "waiting for threads to finish.." << std::endl;
  t1.join();
  t2.join();

  cout << "done!\n";
}

int count = 0;
std::mutex mtx;

void increment_manually(int n) {
  for (int i = 0; i < n; i++) {
    mtx.lock();
    count++;
    mtx.unlock();
  }
}

// automatic locking/unlocking
void increment_raii(int n) {
  for (int i = 0; i < n; i++) {
    std::lock_guard<std::mutex> lock(mtx);
    count++;
  }
}

int main() {
  std::vector<std::thread> threads;
  int n = 100;

  for (int i = 0; i < 4; i++) {
    // pass function and argument separately
    threads.emplace_back(std::thread(increment_manually, n));
  }

  for (int i = 0; i < 3; i++) {
    // pass function and argument separately
    threads.emplace_back(std::thread(increment_raii, n));
  }

  // or use lambda (closure)
  threads.emplace_back(std::thread([n]() {
    for (int i = 0; i < n; i++) {
      mtx.lock();
      count++;
      mtx.unlock();
    }
  }));

  for (auto& thread : threads) thread.join();
  assert(count == 8 * 100);
  cout << "done! count=" << count << std::endl;
}
