#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#if defined(__clang__)
#define __UNROLL_4 _Pragma("clang loop unroll_count(4)")
#define __UNROLL_0 _Pragma("clang loop unroll(disable)")
#elif defined(__GNUC__) || defined(__GNUG__)
#define __UNROLL_4 _Pragma("GCC unroll 4")
#define __UNROLL_0
#else
#define __UNROLL_4
#define __UNROLL_0
#endif

#define n 512

volatile int a = 2, b = 2;

int add_unrolling()
{
  int s = 0;

  __UNROLL_4
  for (int i = 0; i < n * n * n; ++i) {
    s += a * i;
  }
  return s;
}

int add_loop()
{
  int s = 0;
  __UNROLL_0
  for (int i = 0; i < n * n * n; ++i) {
    s += b * i;
  }
  return s;
}

int main() {
    clock_t start = clock();
    int s = add_loop();
    float seconds = (float) (clock() - start) / CLOCKS_PER_SEC * 1000;
    printf("     add_loop = %d, %.4fms\n", s, seconds);

    start = clock();
    s = add_unrolling();
    seconds = (float) (clock() - start) / CLOCKS_PER_SEC * 1000;
    printf("add_unrolling = %d, %.4fms\n", s, seconds);

    return 0;
}
