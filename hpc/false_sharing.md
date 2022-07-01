###

Test

```
# ./a_true.out
True a addr = 0x7ffc4b13b880 value =99999999 cost = 1.31957
True b addr = 0x7ffc4b13b8c0 value =99999999 cost = 1.32058

# ./a_false.out
False a addr = 0x7ffde561b000 value =99999999 cost = 4.60434
False b addr = 0x7ffde561b004 value =99999999 cost = 5.05932
```

Using `perf` to analyze.

```
$ perf stat -B -e L1-dcache-load-misses,L1-dcache-loads,L1-dcache-stores,L1-icache-load-misses,LLC-load-misses,LLC-loads,LLC-store-misses,LLC-stores,branch-load-misses,branch-loads,dTLB-load-misses,dTLB-loads,dTLB-store-misses,dTLB-stores,iTLB-load-misses,iTLB-loads,node-load-misses,node-loads,node-store-misses,node-store ./a_true.out
True a addr = 0x7fffb9e68180 value =99999999 cost = 1.3197
True b addr = 0x7fffb9e681c0 value =99999999 cost = 1.31496

 Performance counter stats for './a_true.out':

           374,978      L1-dcache-load-misses     #    0.10% of all L1-dcache hits    (15.48%)
       392,829,286      L1-dcache-loads                                               (16.01%)
       195,978,053      L1-dcache-stores                                              (15.22%)
            56,390      L1-icache-load-misses                                         (10.60%)
             2,284      LLC-load-misses           #   37.71% of all LL-cache hits     (10.42%)
             6,056      LLC-loads                                                     (16.38%)
             1,539      LLC-store-misses                                              (10.85%)
             2,652      LLC-stores                                                    (10.78%)
             9,165      branch-load-misses                                            (16.07%)
       192,445,300      branch-loads                                                  (21.30%)
               935      dTLB-load-misses          #    0.00% of all dTLB cache hits   (20.97%)
       388,064,495      dTLB-loads                                                    (18.11%)
               191      dTLB-store-misses                                             (9.93%)
       185,695,612      dTLB-stores                                                   (10.41%)
                58      iTLB-load-misses          #    0.92% of all iTLB cache hits   (10.35%)
             6,333      iTLB-loads                                                    (10.28%)
             1,880      node-load-misses                                              (15.32%)
                25      node-loads                                                    (20.30%)
             1,606      node-store-misses                                             (10.08%)
               369      node-store                                                    (10.02%)

       0.680747655 seconds time elapsed

$ perf stat -B -e L1-dcache-load-misses,L1-dcache-loads,L1-dcache-stores,L1-icache-load-misses,LLC-load-misses,LLC-loads,LLC-store-misses,LLC-stores,branch-load-misses,branch-loads,dTLB-load-misses,dTLB-loads,dTLB-store-misses,dTLB-stores,iTLB-load-misses,iTLB-loads,node-load-misses,node-loads,node-store-misses,node-store ./a_false.out
False b addr = 0x7ffeefd758c4 value =99999999 cost = 11.0824
False a addr = 0x7ffeefd758c0 value =99999999 cost = 11.5339

 Performance counter stats for './a_false.out':

        72,024,888      L1-dcache-load-misses     #   18.21% of all L1-dcache hits    (14.98%)
       395,623,950      L1-dcache-loads                                               (15.03%)
       194,590,961      L1-dcache-stores                                              (15.04%)
           199,374      L1-icache-load-misses                                         (10.11%)
        11,086,994      LLC-load-misses           #   44.03% of all LL-cache hits     (10.11%)
        25,182,216      LLC-loads                                                     (15.15%)
        27,466,286      LLC-store-misses                                              (10.06%)
        34,704,857      LLC-stores                                                    (10.03%)
            82,292      branch-load-misses                                            (15.12%)
       202,301,301      branch-loads                                                  (20.15%)
             3,169      dTLB-load-misses          #    0.00% of all dTLB cache hits   (20.13%)
       410,299,902      dTLB-loads                                                    (19.91%)
               574      dTLB-store-misses                                             (14.80%)
       204,788,564      dTLB-stores                                                   (10.04%)
               100      iTLB-load-misses          #    0.14% of all iTLB cache hits   (10.04%)
            72,554      iTLB-loads                                                    (10.03%)
        10,048,746      node-load-misses                                              (15.03%)
           943,595      node-loads                                                    (20.03%)
        22,569,837      node-store-misses                                             (9.99%)
         5,134,366      node-store                                                    (9.95%)

       5.993642911 seconds time elapsed
```

Explain

```
The LLC (last-level cache) is the last, and longest-latency, level in the memory hierarchy before main memory (DRAM). Any memory requests missing here must be serviced by local or remote DRAM, with significant latency. The LLC Miss metric shows a ratio of cycles with outstanding LLC misses to all cycles.
```

### References
1. [Using JMH to Benchmark Multi-Threaded Code](http://psy-lob-saw.blogspot.com/2013/05/using-jmh-to-benchmark-multi-threaded.html)
2. [Dive Deeper into Cache Coherency](http://psy-lob-saw.blogspot.com/2013/09/diving-deeper-into-cache-coherency.html) 
3. [Notes on False Sharing](http://psy-lob-saw.blogspot.com/2014/06/notes-on-false-sharing.html)
4. [Avoid False Sharing](http://www.nic.uoregon.edu/~khuck/ts/acumem-report/manual_html/ch06s07.html)
