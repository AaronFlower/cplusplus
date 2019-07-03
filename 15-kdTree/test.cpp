#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "solution.h"
#include "point.h"
#include "boundedPQueue.h"

#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::vector;
using std::string;

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

TEST(test, BoundedPQueue) {
    BoundedPQueue<string> bpq(4);

    EXPECT_EQ(bpq.empty(), true);
    EXPECT_EQ(bpq.size(), 0);
    EXPECT_EQ(bpq.maxSize(), 4);

    EXPECT_THROW(bpq.best(), std::out_of_range);
    EXPECT_THROW(bpq.worst(), std::out_of_range);

    bpq.enqueue("hello", 2.0);
    EXPECT_EQ(bpq.best(), 2.0);
    EXPECT_EQ(bpq.worst(), 2.0);

    bpq.enqueue("Kid", 2.718);
    bpq.enqueue("Foo", 3.14);
    EXPECT_EQ(bpq.best(), 2.0);
    EXPECT_EQ(bpq.worst(), 3.14);
    EXPECT_EQ(bpq.size(), 3);

    bpq.enqueue("Bar", 0.618);
    EXPECT_EQ(bpq.best(), 0.618);
    EXPECT_EQ(bpq.worst(), 3.14);
    EXPECT_EQ(bpq.size(), 4);

    bpq.enqueue("Max", 10.0);
    EXPECT_EQ(bpq.best(), 0.618);
    EXPECT_EQ(bpq.worst(), 3.14);
    EXPECT_EQ(bpq.size(), 4);

    bpq.enqueue("Min", 0.10);
    EXPECT_EQ(bpq.best(), 0.1);
    EXPECT_EQ(bpq.worst(), 2.718);
    EXPECT_EQ(bpq.size(), 4);
}
