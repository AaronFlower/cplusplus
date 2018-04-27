#ifndef BINARY_TREE_H__ 
#define BINARY_TREE_H__ 

#include <vector>

using std::vector;

struct BNode {
    double value;
    BNode * left;
    BNode * right;
};


class BTree {
    public:
        BTree();
        ~BTree();
        void insert(double);
        BNode * search(double);
        void preorder(vector<double> &v);

    private:
        void insert(BNode * node, double val);
        void destroy();
        void preorder(BNode * node, vector<double> &v);

        BNode * root;
};



#endif
