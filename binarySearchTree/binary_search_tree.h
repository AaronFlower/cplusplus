#ifndef BINARY_SEARCH_TREE_H__
#define BINARY_SEARCH_TREE_H__

#include <vector>
using std::vector;

struct BNode {
    BNode * left;
    BNode * right;
    BNode * parent;
    int key;
};

class BinarySearchTree {
    public:
        BinarySearchTree(){}
        BinarySearchTree(const vector<int> &data);
        ~BinarySearchTree();

        void insertNode(int x);
        void inorderTreeWalk(vector<int> &v);
    
    private:
       void inorderTreeWalk(BNode * tree, vector<int> &v);
       BNode * createBNode(int x);
       BNode * root;
};

#endif

