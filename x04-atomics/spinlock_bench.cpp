#include "semaphore.h"
#include <atomic>
#include <chrono>
#include <iostream>
#include <mutex>

struct alignas(64) tas_spinlock {
  std::atomic<bool> lock_{false};

  void lock() {
    while (lock_.exchange(true, std::memory_order_acquire))
      ;
  }

  void unlock() { lock_.store(false, std::memory_order_release); }
};

struct alignas(64) ttas_spinlock {
  std::atomic<bool> lock_{false};

  void lock() {
    for (;;) {
      if (!lock_.exchange(true, std::memory_order_acquire)) {
        break;
      }
      while (lock_.load(std::memory_order_relaxed))
	__builtin_ia32_pause();
    }
  }

  void unlock() { lock_.store(false, std::memory_order_release); }
};

tas_spinlock tas_clk;
ttas_spinlock ttas_clk;
std::mutex m_clk;
LightweightMutex lw_clk;

int count = 0;

#define N 100000

template <typename Lock> void *run_task(void *arg) {
  Lock *clk = static_cast<Lock *>(arg);
  for (int i = 0; i < N; ++i) {
    std::lock_guard<Lock> guard(*clk);
    ++count;
  }
  return nullptr;
}

template <typename Lock> int test_lock(int n_worker, Lock *clk, const char* name) {
  auto begin = std::chrono::steady_clock::now();
  pthread_t tids[n_worker];

  for (int i = 0; i < n_worker; ++i) {
    pthread_create(&tids[i], nullptr, run_task<Lock>, (void *)clk);
  }

  for (int i = 0; i < n_worker; ++i) {
    pthread_join(tids[i], nullptr);
  }
  auto end = std::chrono::steady_clock::now();

  auto cost = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

  std::cout << name << " count = " << count << " cost_ns " << cost.count() << " per "
            << cost.count() / (n_worker * N) << std::endl;
  return 0;
}

int main(int argc, char **argv) {
  int n_worker = 4, option = 2;

  if (argc > 1) {
    n_worker = atoi(argv[1]);
  }
  if (argc > 2) {
    option = atoi(argv[2]);
  }

  switch (option) {
  case 0:
    test_lock<tas_spinlock>(n_worker, &tas_clk, "TAS");
    break;
  case 1:
    test_lock<ttas_spinlock>(n_worker, &ttas_clk, "TTAS");
    break;
  case 2:
    test_lock<tas_spinlock>(n_worker, &tas_clk, "TAS");
    test_lock<ttas_spinlock>(n_worker, &ttas_clk, "TTAS");
    test_lock<std::mutex>(n_worker, &m_clk, "MUTEX");
    test_lock<LightweightMutex>(n_worker, &lw_clk, "LIGHT");
    break;
  default:
    std::cout << "Please use option 0, 1, 2" << std::endl;
  }

  return 0;
}
