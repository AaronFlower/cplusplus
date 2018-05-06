#include "binary_search_tree.h"
#include <vector>

using std::vector;

BinarySearchTree::BinarySearchTree(const vector<int> &v) :BinarySearchTree() {
    for (auto x:v) {
        insertNode(x);    
    }
}

void BinarySearchTree::insertNode(int x) {
    BNode * node = createBNode(x); 
    if (root == nullptr) {
        root = node;
    } else {
        BNode * cur, * p;
        cur = root;
        do {
            p = cur;
            if (cur->key > x) {
                cur = cur->left;
            } else {
                cur = cur->right;
            }
        } while(cur != nullptr);

        if (p->key > x) {
            p->left = node;
            node->parent = p;
        } else {
            p->right = node;
            node->parent = p;
        }
    }
}


BinarySearchTree::~BinarySearchTree(){
    destroyTree(root);
}

void BinarySearchTree::destroyTree(BNode *tree) {
    if (tree) {
        destroyTree(tree->left);
        destroyTree(tree->right);
        delete tree;
    }
}

void BinarySearchTree::inorderTreeWalk(vector<int> &v) {
    if (root == nullptr)
        return;
    inorderTreeWalk(root, v);
}


void BinarySearchTree::inorderTreeWalk(BNode * tree, vector<int> &v) {
    if (tree) {
        inorderTreeWalk(tree->left, v);
        v.push_back(tree->key);
        inorderTreeWalk(tree->right, v);
    }
}

BNode * BinarySearchTree::createBNode(int x) {
    BNode * node = new BNode;
    node->key = x;
    node->parent = nullptr;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}
