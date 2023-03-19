#include <stdio.h>

int foo(int *a, int *b)
{
  *a = 5;
  *b = 6;
  return *a + *b;
}

int rfoo(int *restrict a, int *restrict b)
{
  *a = 5;
  *b = 6;
  return *a + *b;
}

int main(void)
{
  int a, b;
  printf(" foo = %d\n", foo(&a, &b));
  printf("rfoo = %d\n", rfoo(&a, &b));

  printf(" foo = %d\n", foo(&a, &a));
  printf("rfoo = %d\n", rfoo(&b, &b));
  return 0;
}
