#include <iostream>
#include <ctime>
#include <cstdlib>

const int n = 1e5;
int a[n], s = 0;

int main() {
  for (int i = 0; i < n; i++)
    a[i] = rand();

  clock_t start = clock();
  for (int t = 0; t < 100000; t++)
    for (int i = 0; i < n; i++)
        s += a[i];

  std::cout << " time: " << (double(clock() - start)) / CLOCKS_PER_SEC << " sum = " << s << std::endl;

  return 0;
}
