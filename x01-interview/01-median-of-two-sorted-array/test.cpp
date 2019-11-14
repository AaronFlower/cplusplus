#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "solution.h"

#include <iostream>

TEST(test, INIT) {
    Solution s;
    vector<int> nums = {1, 2, 3, 0, 8, 5, 3};
    int median = s.findKth(nums, 0, nums.size(), nums.size() / 2);
    std::cout << median << std::endl;

    nums = {1, 2, 3};
    median = s.findKth(nums, 0, nums.size(), nums.size() / 2);
    std::cout << median << std::endl;

    nums = {1, 2, 3, 4};
    median = s.findKth(nums, 0, nums.size(), nums.size() / 2);
    std::cout << median << std::endl;
}
