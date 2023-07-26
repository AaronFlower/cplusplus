#include <atomic>
#include <chrono>
#include <iostream>
#include <pthread.h>
#include <thread>
#include <vector>

// SPSC_Queue
// Single Producer, Single Consumer. RingBuffer
// It's wati-free(hence also lock-free)

struct RingBuffer {
  RingBuffer(int N) : r_index_{0}, w_index_{0}, data_(N, 0) { assert(N > 2); }

  bool push(int n) {
    int w = w_index_.load(std::memory_order_relaxed);
    int next = w + 1;
    next = (next != data_.size()) * next;
    if (next == r_index_.load(std::memory_order_acquire)) {
      return false;
    }
    data_[w] = n;
    w_index_.store(next, std::memory_order_release);
    return true;
  }

  bool pop(int &n) {
    int r = r_index_.load(std::memory_order_relaxed);
    if (r == w_index_.load(std::memory_order_acquire)) {
      return false;
    }
    n = data_[r];
    int next = r + 1;
    next = (next != data_.size()) * next;
    r_index_.store(next, std::memory_order_release);
    return true;
  }

  alignas(64) std::atomic<int> r_index_;
  alignas(64) std::atomic<int> w_index_;
  std::vector<int> data_;
};

struct RingBuffer2 {
  RingBuffer2(size_t cap) : data_(cap, 0) {}

  bool push(int n) {
    int w_index = w_index_.load(std::memory_order_relaxed);
    int next = w_index + 1;
    next = (next != data_.size()) * next;
    if (next == r_index_cache_) {
      r_index_cache_ = r_index_.load(std::memory_order_acquire);
      if (next == r_index_cache_) {
        return false;
      }
    }

    data_[w_index] = n;
    w_index_.store(next, std::memory_order_release);
    return true;
  }

  bool pop(int &n) {
    int r_index = r_index_.load(std::memory_order_relaxed);
    if (r_index == w_index_cache_) {
      w_index_cache_ = w_index_.load(std::memory_order_acquire);

      if (r_index == w_index_cache_) {
        return false;
      }
    }

    int next = r_index + 1;
    next = (next != data_.size()) * next;
    n = data_[r_index];
    r_index_.store(next, std::memory_order_release);
    return true;
  }

  alignas(64) std::atomic<int> w_index_{0};
  size_t w_index_cache_{0};
  alignas(64) std::atomic<int> r_index_{0};
  size_t r_index_cache_{0};
  std::vector<int> data_;
};

template <typename T> void simple_test() {
  T rb(4);
  assert(rb.push(0));
  assert(rb.push(1));
  assert(rb.push(2));
  assert(!rb.push(3));
  int n;

  assert(rb.pop(n));
  assert(n == 0);

  assert(rb.pop(n));
  assert(n == 1);

  assert(rb.pop(n));
  assert(n == 2);

  assert(!rb.pop(n));

  assert(rb.push(3));
  assert(rb.pop(n));
  assert(n == 3);
}

void pin_thead(int cpu) {
#ifdef __linux__
  if (cpu < 0)
    return;

  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  CPU_SET(cpu, &cpuset);
  if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t),
                             &cpuset == -1)) {
    perror("pthread_setaffinity_no");
    exit(1);
  }
#elif __APPLE__
    // macOS/iOS-specific code
#elif _WIN32
    // Windows-specific code
#else
    // Code for other platforms
#endif
}

template <typename T> void bench(int cpu1, int cpu2) {
  const size_t q_size = 10000;
  const int64_t iters = 100000000;
  T q(q_size);

  auto t = std::thread([&] {
    // pin_thread(cpu1);
    for (int i = 0; i < iters; ++i) {
      int val;
      while (!q.pop(val))
        ;
      if (val != i) {
        throw std::runtime_error("");
      }
    }
  });

  // pin_thread(cpu2);
  auto start = std::chrono::steady_clock::now();
  for (int i = 0; i < iters; ++i) {
    while (!q.push(i))
      ;
  }

  while (q.r_index_.load(std::memory_order_relaxed) !=
         q.w_index_.load(std::memory_order_relaxed))
    ;
  auto stop = std::chrono::steady_clock::now();
  t.join();
  auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start)
                  .count();
  std::cout << iters * 1000000000 / diff << " ops/s" << std::endl;
}

int main(int argc, char *argv[]) {
  int cpu1 = -1;
  int cpu2 = -1;

  simple_test<RingBuffer>();

  bench<RingBuffer>(cpu1, cpu2);

  simple_test<RingBuffer2>();
  bench<RingBuffer2>(cpu1, cpu2);
  return 0;
}
