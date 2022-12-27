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

### Contract Programming

> A general and language-agnostic advice is to always **inspect the assembly** that the compiler produced, and if it is not what you were hoping for, try to think about corner cases that may be limiting the compiler from optimizing it.

### bfloat

Lower-precision types need less memory bandwidth to move them around and usually take fewer cycles to operate on (e.g., the division instruction may take xx, yy, or zz cycles depending on the type), which is why they are preferred when error tolerance allows it.

Deep learning, emerging as a very popular and computationally-intensive field, created a huge demand for low-precision matrix multiplication, which led to manufacturers developing separate hardware or at least adding specialized instructions that support these types of computations — most notably, Google developing a custom chip called TPU (tensor processing unit) that specializes on multiplying 128-by-128 bfloat matrices, and NVIDIA adding “tensor cores,” capable of performing 4-by-4 matrix multiplication in one go, to all their newer GPUs.

Apart from their sizes, most of the behavior is the same between all floating-point types, which we will now clarify.


### BigInt

For all purposes other than multiplication, 128-bit integers are just bundled as two registers. This makes it too weird to have a full-fledged 128-bit type, so the support for it is limited, other than for basic arithmetic operations. For example:

```c++
__int128_t add(__int128_t a, __int128_t b) {
    return a + b;
}
```

is compiled to 

```c++
add:
    mov rax, rdi
    add rax, rdx    ; this sets the carry flag in case of an overflow
    adc rsi, rcx    ; +1 if the carry flag is set
    mov rdx, rsi
    ret
```

Using this method, we can make our Int bigger to Infinity.






