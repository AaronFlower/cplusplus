#include <atomic>
#include <iostream>
#include <pthread.h>

struct Node {
  Node *next;
};

static std::atomic<Node *> g_head(nullptr);

static void *thread_func(void *) {
  for (int i = 0; i < 200000; ++i) {
    Node *insert = new Node;
    insert->next = g_head.load(std::memory_order_relaxed);
    while (!g_head.compare_exchange_weak(insert->next, insert,
                                         std::memory_order_release,
                                         std::memory_order_acquire))
      ;
  }
  return nullptr;
}

int main(int argc, char **argv) {
  int n_thread = 4;
  if (argc == 2)
                n_thread = atoi(argv[1]);

  pthread_t tids[n_thread];
  for (int i = 0; i < n_thread; ++i) {
                pthread_create(&tids[i], nullptr, thread_func, nullptr);
  }
  for (int i = 0; i < n_thread; ++i) {
                pthread_join(tids[i], nullptr);
  }

  int count = 0;
  while (g_head) {
                Node *t = g_head.load(std::memory_order_relaxed);
                g_head.store(t->next, std::memory_order_relaxed);
                delete t;
                ++count;
  }

  std::cout << " n_threads = " << n_thread << " total: " << count << std::endl;

  return 0;
}
