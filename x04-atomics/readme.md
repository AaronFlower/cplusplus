## Atomics

### LinkedList

```bash
g++ -O2 -std=c++11 -Wall -fsanitize=thread linked_list.cpp
```

### SpinLock Bench

```bash
❯ g++ -O2 -std=c++11 spinlock_bench.cpp && ./a.out

>  g++ -O2 -std=c++11 -Wall spinlock_bench.cpp -I../../cassini/third/include -lpthread -L ../../cassini/third/lib -lbrpc -lgflags -lssl -lcrypto -lprotobuf -ldl

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

### Another compare with butex

It is interesting that butex is the best, but its cache misses is higher that ttas. It has lower bus-cycles.

For now, I cannot understand why.


```
$ perf stat -e cache-misses,bus-cycles,L1-dcache-loads,L1-dcache-load-misses  ./spin_bench 16 3
MUTEX count = 1600000 cost_ns 245207736 per 153

 Performance counter stats for './spin_bench 16 3':

            31,365      cache-misses
        86,605,144      bus-cycles
       455,338,318      L1-dcache-loads
        21,810,251      L1-dcache-load-misses     #    4.79% of all L1-dcache accesses

       0.247153809 seconds time elapsed

       0.322901000 seconds user
       3.340786000 seconds sys


$ perf stat -e cache-misses,bus-cycles,L1-dcache-loads,L1-dcache-load-misses  ./spin_bench 16 2
BUTEX count = 1600000 cost_ns 232402823 per 145

 Performance counter stats for './spin_bench 16 2':

            39,165      cache-misses
        82,834,178      bus-cycles
       418,782,259      L1-dcache-loads
        19,691,375      L1-dcache-load-misses     #    4.70% of all L1-dcache accesses

       0.234351434 seconds time elapsed

       0.338363000 seconds user
       3.143107000 seconds sys


$ perf stat -e cache-misses,bus-cycles,L1-dcache-loads,L1-dcache-load-misses  ./spin_bench 16 1
TTAS count = 1600000 cost_ns 679572646 per 424

 Performance counter stats for './spin_bench 16 1':

           801,035      cache-misses
       251,459,375      bus-cycles
     3,192,064,191      L1-dcache-loads
        20,905,465      L1-dcache-load-misses     #    0.65% of all L1-dcache accesses

       0.681621664 seconds time elapsed

      10.060809000 seconds user
       0.000000000 seconds sys


$ perf stat -e cache-misses,bus-cycles,L1-dcache-loads,L1-dcache-load-misses  ./spin_bench 16 0
TAS count = 1600000 cost_ns 1287438729 per 804

 Performance counter stats for './spin_bench 16 0':

         5,734,139      cache-misses
       444,153,978      bus-cycles
       546,862,020      L1-dcache-loads
        23,110,010      L1-dcache-load-misses     #    4.23% of all L1-dcache accesses

       1.289415830 seconds time elapsed

      17.768328000 seconds user
       0.000000000 seconds sys

```
