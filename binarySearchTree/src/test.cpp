#include <iostream>
#include <vector>
#include <gtest/gtest.h>

#include "binary_search_tree.h"

using std::cout;
using std::endl;
using std::vector;

void printVector (const vector<int> &v) {
    for (auto ele:v) {
        cout << ele << "\t";
    }
    cout << endl;
}

void testDestroy () {
    vector<int> v;
    vector<int> init_data = {12, 5, 18, 2, 9, 15, 19, 13, 17};
    BinarySearchTree tree(init_data);
    tree.inorderTreeWalkStack(v);
    printVector(v);
}

void testSearch () {
    vector<int> v;
    vector<int> init_data = {12, 5, 18, 2, 9, 15, 19, 13, 17};
    BinarySearchTree tree(init_data);
    tree.inorderTreeWalkStack(v);
    printVector(v);

    auto node = tree.search(18);
    if (node && node->key == 18) {
        cout << "Hit 18" << endl;
    }
    node = tree.search(3);
    if (!node) {
        cout << "Not hit 3" << endl;
    }
}

TEST(BinarySearchTree, MAXIMUM) {
//    BinarySearchTree tree;
 //   EXPECT_EQ(nullptr, tree.maximum());

    vector<int> init_data = {12, 5, 8, 2, 9, 15, 19, 13, 17};
    BinarySearchTree tree2(init_data);
    EXPECT_EQ(19, tree2.maximum()->key);
}

TEST(BinarySearchTree, LevelOrderWalk) {
    vector<int> init_data = {12, 5, 8, 2, 9, 15, 19, 13, 17};
    BinarySearchTree tree(init_data);
    EXPECT_EQ(19, tree.maximum()->key);
    vector<int> v;
    tree.levelOrderWalk(v);
    printVector(v);
}

void testMinMax(const BinarySearchTree &tree) {
    auto maxNode = tree.maximum();
    auto minNode = tree.minimum();
    cout << "Tree Max : " << maxNode->key << endl;
    cout << "Tree Min : " << minNode->key << endl;
}

int main (int argc, char **argv) {
    BinarySearchTree tree;
    tree.insertNode(5);
    tree.insertNode(3);
    tree.insertNode(6);
    vector<int> v;
    tree.inorderTreeWalkStack(v);
    printVector(v);


    vector<int> init_data = {12, 5, 8, 2, 9, 15, 19, 13, 17};
    BinarySearchTree tree2(init_data);
    v.clear(); 
    tree2.inorderTreeWalk(v);
    printVector(v);


    testDestroy();
    testSearch();
    testMinMax(tree);
    testMinMax(tree2);


    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

