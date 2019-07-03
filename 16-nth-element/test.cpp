#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "solution.h"

#include <iostream>
#include <vector>

using std::vector;

TEST(test, partition) {
    vector<int> data{8, 9, 2, 1, 5, 3, 7};
    Solution<int> s;

    s.partition(data.begin(), data.end());
    EXPECT_THAT(data, testing::ElementsAre(2, 1, 5, 3, 7, 9, 8));

    data = {1, 2, 3, 4};
    s.partition(data.begin(), data.end());
    EXPECT_THAT(data, testing::ElementsAre(1, 2, 3, 4));

    data = {4, 3, 2, 1};
    s.partition(data.begin(), data.end());
    EXPECT_THAT(data, testing::ElementsAre(1, 3, 2, 4));

    data = {1};
    s.partition(data.begin(), data.end());
    EXPECT_THAT(data, testing::ElementsAre(1));
}

TEST(test, INIT) {
    vector<int> data{8, 9, 2, 1, 5, 3, 7};
    auto mid = data.begin() + data.size() / 2;

    Solution<int> s;
    s.nth_element(data.begin(), mid, data.end());
    EXPECT_EQ(*mid, 5);

    mid = data.begin();
    s.nth_element(data.begin(), mid, data.end());
    EXPECT_EQ(*mid, 1);

    mid = data.begin() + 1;
    s.nth_element(data.begin(), mid, data.end());
    EXPECT_EQ(*mid, 2);

    mid = data.begin() + 2;
    s.nth_element(data.begin(), mid, data.end());
    EXPECT_EQ(*mid, 3);

    mid =  data.begin() + data.size() - 1;
    s.nth_element(data.begin(), mid, data.end());
    EXPECT_EQ(*mid, 9);
}

TEST(test, DOUBLE) {
    vector<double> data{0.618, 1.1414, 2.18, 1.618, 5.0,  3.14};
    auto mid = data.begin() + data.size() / 2;

    Solution<double> s;
    s.nth_element(data.begin(), mid, data.end());
    EXPECT_EQ(*mid, 2.18);

    mid = data.begin();
    s.nth_element(data.begin(), mid, data.end());
    EXPECT_EQ(*mid, 0.618);

    mid = data.begin() + 1;
    s.nth_element(data.begin(), mid, data.end());
    EXPECT_EQ(*mid, 1.1414);

    mid = data.begin() + 2;
    s.nth_element(data.begin(), mid, data.end());
    EXPECT_EQ(*mid, 1.618);

    mid =  data.begin() + data.size() - 1;
    s.nth_element(data.begin(), mid, data.end());
    EXPECT_EQ(*mid, 5.0);
}

// @Todo support customized compare function.
