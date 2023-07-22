## Atomics

### LinkedList

```bash
g++ -O2 -std=c++11 -Wall -fsanitize=thread linked_list.cpp
```

### SpinLock Bench

```bash
❯ g++ -O2 -std=c++11 spinlock_bench.cpp && ./a.out
count = 40000 cost_ns 4221990 per 105
count = 80000 cost_ns 2575314 per 64

❯ ./a.out 8 2
count = 80000 cost_ns 12487183 per 156
count = 160000 cost_ns 6224561 per 77

❯ ./a.out 8 0
count = 80000 cost_ns 12613636 per 157

❯ ./a.out 8 1
count = 80000 cost_ns 7398635 per 92
``
