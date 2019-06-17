#ifndef MY_SOLUTION__
#define MY_SOLUTION__

#include <cstdlib>
#include <iostream>
#include <vector>

using std::vector;

/**
 * Implement a minimal C++11 allocator with debug output.
 */
template <class T>
struct MyAlloc {
    typedef T value_type;

    MyAlloc() = default;

    template <class U> MyAlloc(const MyAlloc<U> &) {}

    T* allocate(std::size_t n) {
        n = n * sizeof(T);
        std::cout << "[+] Allocating " << n << "bytes \n";
        /* return static_cast<T *>(::operator new(n)); */
        return static_cast<T *>(::operator new(n));
        /* return (T *)(::operator new(n)); */
    }

    void deallocate(T *p, std::size_t n) {
        std::cout << "[-] Deallocating " << n * sizeof(*p) << "bytes \n";
        /* ::operator delete(p); */
        delete(p);
    }
};

template <class T, class U>
bool operator==(const MyAlloc<T> &, const MyAlloc<U> &) {return true; }

template <class T, class U>
bool operator!=(const MyAlloc<T> &, const MyAlloc<U> &) {return false; }

class Solution {
public:
    void usingReserve(int sz) {
        vector<int, MyAlloc<int>> v;
        v.reserve(sz);

        for (int i = 0; i < sz; ++i) {
            v.emplace_back(i);
        }
    }

    void notUsingReserve(int sz) {
        vector<int, MyAlloc<int>> v;

        for (int i = 0; i < sz; ++i) {
            v.emplace_back(i);
        }
    }
};

#endif /* ifndef MY_SOLUTION__ */
