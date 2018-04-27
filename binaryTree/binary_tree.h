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
        void inorder(vector<double> &v);
        void preorder(vector<double> &v);
        void postorder(vector<double> &v);

    private:
        void insert(BNode * node, double val);
        void destroy();
        void inorder(BNode * node, vector<double> &v);
        void preorder(BNode * node, vector<double> &v);
        void postorder(BNode * node, vector<double> &v);

        BNode * root;
};



#endif
