#include "math.h"

bool isPrime(int n) {
    if (n <= 1) return false;

    if (n % 2 == 0) return n == 2;

    for (int i = 3;; i += 2) {
        if (i > n / i) break;
        if (n % i == 0) return false;
    }

    return true;
}
