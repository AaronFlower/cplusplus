#include <iostream>
#include <vector>
#include <string>

#include "binary_tree.h"

using std::cout;
using std::endl;
using std::vector;
using std::string;


void printOrder(const string & order, const vector<double> & v) {
    cout << order << endl;
    for (auto ele : v) {
        cout << ele << "\t" ;
    }
    cout << endl;
}

int main () {
    cout << "Hello Binary Tree" << endl;
    vector<double> data = {10, 6, 14, 5, 8, 11, 18};
    vector<double> inV, postV, preV;

    BTree tree;
    for (auto d: data) {
        tree.insert(d);
    }
    tree.inorder(inV);
    tree.postorder(postV);
    tree.preorder(preV);

    printOrder("Inorder", inV);
    printOrder("Preorder", preV);
    printOrder("Postorder", postV);
    
    return 0;
}
