#include <iostream>
#include "binary_search_tree.h"
#include <vector>

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

int main () {
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

    return 0;
}
