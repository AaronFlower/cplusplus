#ifndef MY_SOLUTION__
#define MY_SOLUTION__



class Solution {
public:
    long fib(unsigned n) {
        if (n <= 2) return 1;
        return fib(n - 1) + fib(n - 2);
    }
};

#endif /* ifndef MY_SOLUTION__ */
