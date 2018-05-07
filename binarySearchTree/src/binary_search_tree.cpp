#include "binary_search_tree.h"
#include <vector>
#include <stack>
#include <queue>

using std::vector;
using std::stack;
using std::queue;

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

void BinarySearchTree::inorderTreeWalk(vector<int> &v) const {
    if (root == nullptr)
        return;
    inorderTreeWalk(root, v);
}


void BinarySearchTree::inorderTreeWalk(BNode * tree, vector<int> &v) const {
    if (tree) {
        inorderTreeWalk(tree->left, v);
        v.push_back(tree->key);
        inorderTreeWalk(tree->right, v);
    }
}

void BinarySearchTree::inorderTreeWalkStack(vector<int> &v) const {
    stack<BNode *> stack;
    if (root) {
        BNode * cur = root;
        stack.push(cur);
        while (!stack.empty()) {
            if (cur) {
                while (cur->left) {
                    stack.push(cur->left);
                    cur = cur->left;
                }
            }
            cur = stack.top();
            stack.pop();
            v.push_back(cur->key);
            if (cur->right) {
                stack.push(cur->right);
                cur = cur->right;
            }
        }
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


BNode * BinarySearchTree::search(int x) const {
    BNode *result = nullptr;
    BNode *cur = root;
    while (cur != nullptr) {
        if (cur->key < x) {
            cur = cur->right;
        } else if (cur->key > x) {
            cur = cur->left;
        } else {
            result = cur;
            break;
        }
    } 
    return result;
}

BNode * BinarySearchTree::maximum() const {
    BNode * cur, * pre;
    pre = cur = root;
    while (cur) {
        pre = cur;
        cur = cur->right;
    }
    return pre;
}

BNode * BinarySearchTree::minimum() const {
    BNode * cur, * pre;
    pre = cur = root;
    while (cur) {
        pre = cur;
        cur = cur->left;
    }
    return pre;
}


void BinarySearchTree::levelOrderWalk(vector<int> &v) const {
    if (root) {
        queue<BNode *> q;
        q.push(root);
        while (!q.empty()) {
            BNode * cur = q.front();
            q.pop();
            v.push_back(cur->key);
            if (cur->left) {
                q.push(cur->left);
            }
            if (cur->right) {
                q.push(cur->right);
            }
        }
    }
}
