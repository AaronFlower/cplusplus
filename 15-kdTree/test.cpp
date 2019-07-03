#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "solution.h"
#include "point.h"

#include <iostream>
#include <vector>

using std::cout;
using std::vector;

TEST(test, Point) {
    vector<double> nums1{1, 2, 3, 4};
    vector<double> nums2{3, 4, 5, 6};
    Point<4> p1, p2;
    copy(nums1.begin(), nums1.end(), p1.begin());
    copy(nums2.begin(), nums2.end(), p2.begin());

    EXPECT_EQ(p1.size(), 4);
    EXPECT_EQ(p2.size(), 4);
    EXPECT_EQ(EuclideanDistance(p1, p2), 16);
}
