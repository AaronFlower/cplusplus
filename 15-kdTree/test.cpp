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
using std::endl;

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

bool isEqualSample(KDTree<2, int>::sample& lhs, KDTree<2, int>::sample rhs) {
    return lhs.first[0] == rhs.first[0] &&
        lhs.first[1] == rhs.first[1] &&
        lhs.second == rhs.second;
}

TEST(test, KDTreeInit) {
    KDTree<2, int> tree1;
    EXPECT_EQ(tree1.size(), 0);

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
    EXPECT_EQ(isEqualSample(res[0][0], {{7, 2}, 0}), true);
    EXPECT_EQ(isEqualSample(res[1][0], {{5, 4}, 1}), true);
    EXPECT_EQ(isEqualSample(res[1][1], {{9, 6}, 0}), true);
    EXPECT_EQ(isEqualSample(res[2][0], {{2, 3}, 0}), true);
    EXPECT_EQ(isEqualSample(res[2][1], {{4, 7}, 1}), true);
    EXPECT_EQ(isEqualSample(res[2][2], {{8, 1}, 0}), true);

    tree1 = tree2;

    EXPECT_EQ(tree1.size(), 6);
    res = tree1.bfs();
    EXPECT_EQ(isEqualSample(res[0][0], {{7, 2}, 0}), true);
    EXPECT_EQ(isEqualSample(res[1][0], {{5, 4}, 1}), true);
    EXPECT_EQ(isEqualSample(res[1][1], {{9, 6}, 0}), true);
    EXPECT_EQ(isEqualSample(res[2][0], {{2, 3}, 0}), true);
    EXPECT_EQ(isEqualSample(res[2][1], {{4, 7}, 1}), true);
    EXPECT_EQ(isEqualSample(res[2][2], {{8, 1}, 0}), true);

    KDTree<2, int> tree3(tree1);

    EXPECT_EQ(tree3.size(), 6);
    res = tree3.bfs();
    EXPECT_EQ(isEqualSample(res[0][0], {{7, 2}, 0}), true);
    EXPECT_EQ(isEqualSample(res[1][0], {{5, 4}, 1}), true);
    EXPECT_EQ(isEqualSample(res[1][1], {{9, 6}, 0}), true);
    EXPECT_EQ(isEqualSample(res[2][0], {{2, 3}, 0}), true);
    EXPECT_EQ(isEqualSample(res[2][1], {{4, 7}, 1}), true);
    EXPECT_EQ(isEqualSample(res[2][2], {{8, 1}, 0}), true);
}

TEST(test, findNode) {
    vector<KDTree<2, int>::sample> points{
        {{7, 2}, 0},
        {{5, 4}, 1},
        {{9, 6}, 0},
        {{4, 7}, 1},
        {{8, 1}, 0},
        {{2, 3}, 0},
    };

    KDTree<2, int> tree2(points);

    auto res = tree2.testFind({7, 2});
    EXPECT_EQ(isEqualSample(res, {{7, 2}, 0}), true);

    res = tree2.testFind({8, 1});
    EXPECT_EQ(isEqualSample(res, {{8, 1}, 0}), true);

    res = tree2.testFind({7, 1});
    EXPECT_EQ(isEqualSample(res, {{8, 1}, 0}), true);

    res = tree2.testFind({8, 7});
    EXPECT_EQ(isEqualSample(res, {{9, 6}, 0}), true);
}

TEST(test, InsertCreate) {
    vector<KDTree<2, int>::sample> points{
        {{5, 4}, 1},
        {{9, 6}, 0},
        {{4, 7}, 1},
        {{8, 1}, 0},
        {{2, 3}, 0},
    };

    KDTree<2, int> tree;

    EXPECT_EQ(tree.size(), 0);

    tree.insert({7, 2}, 0);
    EXPECT_EQ(tree.size(), 1);

    // Already exists and change the label.
    tree.insert({7, 2}, 1);
    EXPECT_EQ(tree.size(), 1);

    for (auto s : points) {
        tree.insert(s.first, s.second);
    }
    EXPECT_EQ(tree.size(), 6);

    // Already exists and change the label.
    tree.insert({2, 3}, 1);
    EXPECT_EQ(tree.size(), 6);

    auto res = tree.bfs();
    EXPECT_EQ(isEqualSample(res[0][0], {{7, 2}, 1}), true);
    EXPECT_EQ(isEqualSample(res[1][0], {{5, 4}, 1}), true);
    EXPECT_EQ(isEqualSample(res[1][1], {{9, 6}, 0}), true);
    EXPECT_EQ(isEqualSample(res[2][0], {{2, 3}, 1}), true);
    EXPECT_EQ(isEqualSample(res[2][1], {{4, 7}, 1}), true);
    EXPECT_EQ(isEqualSample(res[2][2], {{8, 1}, 0}), true);

    // Insert a new node. Always the axis.
    tree.insert({2, 4}, 1);
    EXPECT_EQ(tree.size(), 7);

    res = tree.bfs();
    EXPECT_EQ(isEqualSample(res[0][0], {{7, 2}, 1}), true);
    EXPECT_EQ(isEqualSample(res[1][0], {{5, 4}, 1}), true);
    EXPECT_EQ(isEqualSample(res[1][1], {{9, 6}, 0}), true);
    EXPECT_EQ(isEqualSample(res[2][0], {{2, 3}, 1}), true);
    EXPECT_EQ(isEqualSample(res[2][1], {{4, 7}, 1}), true);
    EXPECT_EQ(isEqualSample(res[2][2], {{8, 1}, 0}), true);
    EXPECT_EQ(isEqualSample(res[3][0], {{2, 4}, 1}), true);

    EXPECT_EQ(tree.contains({2, 4}), true);
    EXPECT_EQ(tree.contains({3, 4}), false);

    Point<2> pt{2, 4};
    tree[pt] = 0;
    auto sample = tree.testFind(pt);
    EXPECT_EQ(isEqualSample(sample, {{2, 4}, 0}), true);

    pt = {3, 4};
    tree[pt] = 1;
    sample = tree.testFind(pt);
    EXPECT_EQ(isEqualSample(sample, {{3, 4}, 1}), true);
}

TEST(test, kNN) {
     vector<KDTree<2, int>::sample> points{
        {{7, 2}, 0},
        {{5, 4}, 0},
        {{9, 6}, 0},
        {{4, 7}, 0},
        {{8, 1}, 1},
        {{2, 3}, 0},
    };

    // The generated KDTree please references
    // https://en.wikipedia.org/wiki/K-d_tree

    KDTree<2, int> tree(points);

    auto label = tree.kNNValue({6, 1}, 1);
    EXPECT_EQ(label, 0);

    label = tree.kNNValue({9, 1}, 1);
    EXPECT_EQ(label, 1);

    label = tree.kNNValue({6, 1}, 2);
    EXPECT_EQ(label, 1);

    label = tree.kNNValue({6, 1}, 3, true);
    EXPECT_EQ(label, 0);

    label = tree.kNNValue({6, 1}, 4, true);
    EXPECT_EQ(label, 0);
}
