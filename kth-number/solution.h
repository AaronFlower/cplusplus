#ifndef MY_SOLUTION__
#define MY_SOLUTION__

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    void quicksort(vector<int>& nums) {
        quickHelper(nums, 0, nums.size());
    }

    void quickHelper(vector<int>& nums, int begin, int end) {
        if (begin + 1 < end) {
            int i = partition(nums, begin, end);
            quickHelper(nums, begin, i);
            quickHelper(nums, i + 1, end);
        }
    }

    int partition(vector<int>& nums, int begin, int end) {
        int i = begin;
        int j = begin - 1;
        int pivot = nums[end - 1];
        for (i = begin; i < end; ++i) {
            if (nums[i] < pivot) {
                ++j;
                swap(nums[i], nums[j]);
            }
        }
        ++j;
        swap(nums[i - 1], nums[j]);
        return j;
    }
};

#endif /* ifndef MY_SOLUTION__ */
