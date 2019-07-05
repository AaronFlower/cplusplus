#include <time.h>

double My_pi = 3.14;

int fact(int n) {
    if (n <= 1)  return 1;
    return n * fact(n - 1);
}

int my_mod(int x, int y) {
    return (x % y);
}

char *get_time() {
    time_t ltime;
    time(&ltime);
    return ctime(&ltime);
}
