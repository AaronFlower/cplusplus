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
        void inorderTreeWalk(vector<int> &v) const;
        void inorderTreeWalkStack(vector<int> &v) const;
        void levelOrderWalk(vector<int> &v) const;
        BNode * search(int x) const;
        BNode * minimum() const;
        BNode * maximum() const;

        BNode * successor(int x) const;
        BNode * predecessor(int x) const;

    private:
       void inorderTreeWalk(BNode * tree, vector<int> &v) const;
       void destroyTree(BNode * tree);
       BNode * createBNode(int x);
       BNode * root;
};

#endif

