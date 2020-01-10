#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "solution.h"

#include <iostream>
#include <algorithm>

using namespace std;

TEST(test, CppSort) {
    std::cout << "Hello kth-number" << std::endl;

    vector<int> nums{1, 2, 7, 9, -10, 3, 9};
    sort(nums.begin(), nums.end(), [](const int a, const int b) {
                return a > b;
            });
    for (auto e : nums) { cout << e << "\t"; } cout << endl;
    sort(nums.begin(), nums.end(), std::greater<int>());
    for (auto e : nums) { cout << e << "\t"; } cout << endl;
    sort(nums.begin(), nums.end(), std::less<int>());
    /* qsort(nums.begin(), nums.size()); */
    for (auto e : nums) { cout << e << "\t"; } cout << endl;
}

TEST(test, CppQuiksort) {
    // cstdlib, qsort 是 c 语言中的函数, qsort 真是难用.
    int nums[] = {1, 2, 7, 9, -10, 3, 9};
    constexpr int size = sizeof nums / sizeof *nums;

    /* qsort(nums, size, sizeof *nums, [](const int *a, const int *b) { */
            /* return 0; */
            /* }); */
    for (auto e : nums) {
        cout << e << "\t";
    }
    cout << endl;
}

TEST(test, MyQuickSort) {
    Solution s;
    vector<int> nums = {5, 6, 1, 2, 7, 9, -10, 3, 9};
    s.quicksort(nums);
    for (auto e : nums) { cout << e << "\t"; } cout << endl;
}
