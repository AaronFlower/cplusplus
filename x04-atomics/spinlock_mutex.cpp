#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

class spinlock_mutex {
public:
  spinlock_mutex() : flag{ATOMIC_FLAG_INIT} {}

  void lock() {
    while (flag.test_and_set(std::memory_order_acquire))
      ;
  }

  void unlock() { flag.clear(std::memory_order_release); }

private:
  std::atomic_flag flag;
};

spinlock_mutex lock;

void worker(int n) {
  for (int i = 0; i < 10; ++i) {
    std::lock_guard<spinlock_mutex> guard(lock);
    std::this_thread::sleep_for(10ms);
    std::cout << n << i << "\n";
  }
  std::cout << std::endl;
}

struct A {
  int a[100];
};

struct B {
  int a;
  int b;
};

struct C {
  int a;
  int b;
  double c;
  char d;
};

int main(void) {
  std::vector<std::thread> tasks;
  for (int i = 0; i < 4; ++i) {
    tasks.emplace_back(worker, i);
  }

  for (int i = 0; i < 4; ++i) {
    tasks[i].join();
  }

  std::atomic<int> ai;

  std::cout << " check atomic_int " << ai.is_lock_free() << std::endl;
  std::cout << " check atomic_A   " << std::atomic<A>{}.is_lock_free()
            << std::endl;
  std::cout << " check atomic_A*  " << std::atomic<A *>{}.is_lock_free()
            << std::endl;
  std::cout << " check atomic_B   " << std::atomic<B>{}.is_lock_free()
            << std::endl;
  std::cout << " check atomic_B*  " << std::atomic<B *>{}.is_lock_free()
            << std::endl;
  std::cout << " check atomic_C   " << std::atomic<C>{}.is_lock_free()
            << std::endl;
  std::cout << " check atomic_C*  " << std::atomic<C *>{}.is_lock_free()
            << std::endl;

  return 0;
}
