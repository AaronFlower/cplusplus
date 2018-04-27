#include <iostream>
#include <vector>

#include "binary_tree.h"

using std::cout;
using std::endl;
using std::vector;

int main () {
    cout << "Hello Binary Tree" << endl;
    vector<double> values;

    BTree tree;
    tree.insert(10);
    tree.insert(6);
    tree.insert(11);
    tree.insert(14);
    tree.preorder(values);
    
    for(auto begin = values.cbegin(); begin < values.cend(); ++begin) {
        cout << *begin << "\t";
    }
    cout << endl;
    return 0;
}
