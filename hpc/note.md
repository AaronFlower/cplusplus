## HPC

### Reciprocal of Throughput

- Optimization for latency
- Optimization for throughput

### Compilation

-  -E
-  -S
-  -c
-  -o

### Linking

- LTO
- The main advantage of using static libraries is that you can perform various interprocedural optimizations that require more context than just the signatures of library functions, such as **function inlining** or **dead code elimination**.
- LTO is a relatively recent feature (it appeared in GCC only around 2014), and it is still far from perfect. In C and C++, the way to make sure no performance is lost is to create a header-only library. As the name suggests, they are just header files that contain full definitions of all functions, and so by simply including them, the compiler gets access to all optimizations possible. Although you do have to recompile them from scratch each time, this approach retains full control and makes sure that no performance is lost.

### Optimization Levels

There are 4 and a half main levels of optimization for speed in GCC:

-O0 is the default one that does no optimizations (although, in a sense, it does optimize: for compilation time).
-O1 (also aliased as -O) does a few “low-hanging fruit” optimizations, almost not affecting the compilation time.
-O2 enables all optimizations that are known to have little to no negative side effects and take reasonable time to complete (this is what most projects use for production builds).
-O3 does very aggressive optimization, enabling almost all correct optimizations implemented in GCC.
-Ofast does everything in -O3, plus a few more optimizations flags that may break strict standard compliance, but not in a way that would be critical for most applications (e.g., floating-point operations may be rearranged so that the result is off by a few bits in the mantissa).

### Specifying Targets

```c++
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
```
