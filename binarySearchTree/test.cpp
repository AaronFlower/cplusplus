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

int main () {
    BinarySearchTree tree;
    tree.insertNode(5);
    tree.insertNode(3);
    tree.insertNode(6);
    vector<int> v;
    tree.inorderTreeWalk(v);
    printVector(v);


    vector<int> init_data = {12, 5, 8, 2, 9, 15, 19, 13, 17};
    BinarySearchTree tree2(init_data);
    v.clear(); 
    tree2.inorderTreeWalk(v);
    printVector(v);

    return 0;
}
