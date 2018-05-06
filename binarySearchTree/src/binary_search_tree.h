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
        BinarySearchTree(){root = nullptr;}
        BinarySearchTree(const vector<int> &data);
        ~BinarySearchTree();

        void insertNode(int x);
        void inorderTreeWalk(vector<int> &v);
        void inorderTreeWalkStack(vector<int> &v);
    
    private:
       void inorderTreeWalk(BNode * tree, vector<int> &v);
       void destroyTree(BNode * tree);
       BNode * createBNode(int x);
       BNode * root;
};

#endif

