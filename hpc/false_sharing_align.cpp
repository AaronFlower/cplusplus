#include <ctime>
#include <thread>
#include <atomic>
#include <iostream>
#include <string>
#include <mutex>

struct TrueFoo {
  std::atomic<int> a alignas(64);
  std::atomic<int> b alignas(64);
  TrueFoo():a(0), b(0) {}
};

struct FalseFoo {
  std::atomic<int> a alignas(64);
  std::atomic<int> b;
  FalseFoo():a(0), b(0) {}
};

struct WorkerInfo {
  std::string desc;
  std::atomic<int> *val;
};

std::mutex io_lock;

void worker(WorkerInfo* info)
{
  clock_t start = clock();
  for (size_t r = 100 * 100 * 100 * 100; --r;) {
    *(info->val) += 1;
  }

  io_lock.lock();
  std::cout << info->desc
    << " addr = " << info->val
    << " value =" << *(info->val)
    << " cost = "  << (double(clock() - start)) / CLOCKS_PER_SEC
    << std::endl;
  io_lock.unlock();
}

void true_sharing () {
  TrueFoo foo;
  WorkerInfo a{"True a", &foo.a};
  WorkerInfo b{"True b", &foo.b};
  std::thread t1(worker, &a);
  std::thread t2(worker, &b);
  t1.join();
  t2.join();
}

void false_sharing () {
  FalseFoo foo;
  WorkerInfo a{"False a", &foo.a};
  WorkerInfo b{"False b", &foo.b};
  std::thread t1(worker, &a);
  std::thread t2(worker, &b);
  t1.join();
  t2.join();
}

int main(void)
{
  true_sharing();
  false_sharing();
  return 0;
}
