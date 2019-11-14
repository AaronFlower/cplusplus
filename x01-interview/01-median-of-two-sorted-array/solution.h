#ifndef MY_SOLUTION__
#define MY_SOLUTION__

#include <vector>

//评测题目1: 两个有序数组，求两者所有元素的中位数
//评测题目2: 一个无序数组，求其中位数

using std::vector;

class Solution {
public:

    float findMedian(vector<int>& nums1, vector<int>& nums2) {
        
    }

    int findKth(vector<int> &nums, int start, int end, int k) {
      if (start < end) {
        int i = partition(nums, start, end);
        if ((i - start) == k) return nums[i];
        if (i < k) {
            return findKth(nums, i + 1, end, k - i);
        } else {
            return findKth(nums, start, i, i - k);
        }
      }
    }


    int partition(vector<int> &nums, int start, int end) {
        int i = start - 1;
        int pivot = nums[end -1];
        for (int j = start; j < end; ++j) {
            if (nums[j] < pivot) {
              ++i;
              std::swap(nums[i], nums[j]);
            }
        }
        ++i;
        std::swap(nums[i], nums[end - 1]);
        return i;
    }
};

#endif /* ifndef MY_SOLUTION__ */
