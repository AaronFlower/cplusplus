#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define n 256

volatile int a = 1, b = 2, c = 3, d= 4;

int add_parallel()
{
  int s1 = 0, s2 = 0;
  for (int i = 0; i < n * n * n; ++i) {
    s1 += a;
    s2 += b;
    s1 += c;
    s2 += d;
  }
  return s1 + s2;
}

int add()
{
  int s = 0;
  for (int i = 0; i < n * n * n; ++i) {
    s += a;
    s += b;
    s += c;
    s += d;
  }
  return s;
}

int main() {
    clock_t start = clock();
    int s = add();
    float seconds = (float) (clock() - start) / CLOCKS_PER_SEC * 1000;
    printf("         sum = %d, %.4fms\n", s, seconds);

    start = clock();
    s = add_parallel();
    seconds = (float) (clock() - start) / CLOCKS_PER_SEC * 1000;
    printf("parallel_sum = %d, %.4fms\n", s, seconds);

    return 0;
}
