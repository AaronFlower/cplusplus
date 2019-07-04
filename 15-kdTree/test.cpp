#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "solution.h"
#include "point.h"
#include "boundedPQueue.h"
#include "kdTree.h"

#include <iostream>
#include <vector>
#include <string>
#include <utility>

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

    // Test initializer list constructor.
    const Point<2> p3{2, 4};
    double a, b;
    a = p3[0];
    b = p3[1];
    EXPECT_EQ(p3.size(), 2);
    EXPECT_EQ(a, 2);
    EXPECT_EQ(b, 4);

    const Point<2> p4 = {1, 2};
    EXPECT_EQ(p4.size(), 2);
    EXPECT_EQ(p4[0], 1);
    EXPECT_EQ(p4[1], 2);
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

TEST(test, KDTreeInit) {
    KDTree<2, int> tree;
    EXPECT_EQ(tree.size(), 0);
    /* vector<pair<Point<2>, int>> points { */
    vector<KDTree<2, int>::sample> points{
        {{7, 2}, 0},
        {{5, 4}, 1},
        {{9, 6}, 0},
        {{4, 7}, 1},
        {{8, 1}, 0},
        {{2, 3}, 0},
    };

    KDTree<2, int> tree2(points);

    EXPECT_EQ(tree2.size(), 6);

    auto res = tree2.bfs();
    for (auto level: res) {
        for (auto e : level) {
            cout << "({" << e.first[0] << ", " << e.first[1] <<  "}, ";
            cout << e.second << ")  ";
        }
        cout << std::endl;
    }

}
