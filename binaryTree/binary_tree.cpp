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


void BTree::inorder(vector<double> &v) {
    if (root == nullptr) {
        return;
    } else {
        inorder(root, v);     
    }
}

void BTree::inorder(BNode * node, vector<double> &v) {
    if (node == nullptr) {
        return;
    } else {
        inorder(node->left, v);
        v.push_back(node->value);
        inorder(node->right, v);
    }
}

void BTree::postorder(vector<double> &v) {
    postorder(root, v);
}

void BTree::postorder(BNode* node, vector<double> &v) {
    if (node == nullptr) return;
    postorder(node->left, v);
    postorder(node->right, v);
    v.push_back(node->value);
}

void BTree::preorder(vector<double> &v) {
    preorder(root, v);
}

void BTree::preorder(BNode* node, vector<double> &v) {
    if (node == nullptr) return;
    v.push_back(node->value);
    preorder(node->left, v);
    preorder(node->right, v);
}


















