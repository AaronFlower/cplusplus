#include "binary_tree.h"


BTree::BTree() {
    root = nullptr;
}

BTree::~BTree() {
    
}

void BTree::insert(double val) {
   if (root == nullptr) {
     root = new BNode;
     root->left = nullptr;
     root->right = nullptr;
     root->value = val;
   } else {
       insert(root, val);
   }
}

void BTree::insert(BNode * node, double val) {
    if (val > node->value) {
        if (node->right) {
            insert(node->right, val);
        } else {
            node->right = new BNode;
            node->right->value = val;
            node->right->left = nullptr;
            node->right->right = nullptr;
        }
    } else {
        if (node->left) {
            insert(node->left, val);
        } else {
            node->left = new BNode;
            node->left->value = val;
            node->left->left = nullptr;
            node->left->right = nullptr;
        }
    }
}


void BTree::preorder(vector<double> &v) {
    if (root == nullptr) {
        return;
    } else {
        preorder(root, v);     
    }
}

void BTree::preorder(BNode * node, vector<double> &v) {
    if (node == nullptr) {
        return;
    } else {
        preorder(node->left, v);
        v.push_back(node->value);
        preorder(node->right, v);
    }
}



