#ifndef MY_SOLUTION__
#define MY_SOLUTION__

#include <vector>

using std::vector;
using std::size_t;

template <typename T>
class Solution {
public:
     typedef typename vector<T>::iterator iterator;

     void nth_element(iterator begin, iterator nth, iterator end) {
        if (begin >= end) {
            throw std::out_of_range("out of range");
        }

        nth_helper(begin, nth, end);
     }

     void nth_helper(iterator begin, iterator nth, iterator end) {
        if (begin < end) {
            auto ith = partition(begin, end);
            if ((ith - begin) == (nth - begin)) {
                nth = ith;
                return;
            } else if ((ith - begin) > (nth - begin)) {
                nth_helper(begin, nth, ith);
            } else {
                nth_helper(ith + 1, nth + (nth - ith - 1), end);
            }
        }
     }

    iterator partition(iterator begin, iterator end) {
        auto pivot = *(end - 1);
        auto len = end - begin;
        auto ith = begin - 1;

        for (int j = 0; j < len; ++j) {
            if (*(begin + j) < pivot) {
                ++ith;
                std::swap(*ith, *(begin + j));
            }
        }
        ++ith;
        std::swap(*ith, *(end - 1));
        return ith;
    }
};

#endif /* ifndef MY_SOLUTION__ */
