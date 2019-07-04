/**
 * code Reference
 * https://github.com/junjiedong/KDTree/blob/master/src/KDTree.h
 *
 * An interface representing a kd-tree in some number of dimensions.
 * The tree can be constructed from a set of data and then queried
 * for membership and k-Neart Neighbors.
 */

#ifndef KD_TREE_H__
#define KD_TREE_H__

#include "point.h"
#include "boundedPQueue.h"

#include <vector>
#include <algorithm>
#include <queue>

using std::size_t;
using std::pair;
using std::vector;
using std::queue;


template <size_t N, typename Y>
class KDTree {
public:
    typedef Point<N> X;
    typedef pair<X, Y> sample;
    // Don't missing `typename`
    typedef typename vector<sample>::iterator iterator;

    KDTree();

    // Build a balanced KD-tree from a large set of Data
    KDTree(vector<sample>& trainData);

    // Frees up all dynamically allocated resources
    ~KDTree();

    // Deep-copies the contents of another KDTree into this one.
    KDTree(const KDTree& rhs);
    KDTree& operator=(const KDTree& rhs);

    // Return the dimensions of the points stored in this KDTree.
    size_t dimension() const;

    // Returns the number of elements in the kd-tree;
    size_t size() const;

    bool empty() const;

    // Returns whether the specified point is contained in the KDTree.
    bool contains(const X& pt) const;

    // Inserts the point `pt` into the KDTree, associating it with the
    // specified value. If the element already existed in the tree, the
    // new value will override the existing one.
    void insert(const X& pt, const Y& value=Y());

    // Returns a reference to the value associated with point pt in the KDTree.
    // If the point does not exist, the it is added to the KDTree using the
    // default value of Y as its key.
    Y& operator[](const X& pt);

    // Returns a reference to the key associated with point pt. If the point
    // is not in the tree, this function throws an out_of_range execution.
    Y& at(const X&pt);
    const Y& at(const X& pt) const;

    // Given a point v and an integer k, finds the k points in the KDTree
    // nearest to v and returns the common value associated with those points.
    // In the event of a tie, one of the most frequent value will be choosen.
    Y& kNNValue(const X& key, size_t k) const;

    vector<vector<sample>> bfs() {
        vector<vector<sample>> res;
        if (!root) return res;

        queue<Node *> q;
        q.push(root);
        while (!q.empty()) {
            size_t len = q.size();
            vector<sample> level;
            for (size_t i = 0; i < len; ++i) {
                auto top = q.front();
                q.pop();
                level.push_back({top->point, top->value});
                if (top->left) q.push(top->left);
                if (top->right) q.push(top->right);
            }
            res.push_back(level);
        }
        return res;
    }

private:

    struct Node {
        X point;
        Node *left;
        Node *right;

        size_t level; // level of the node in the tree, starts at 0 for the root.
        Y value;
        Node(const X& pt, int l, const Y& v = Y()):
            point(pt), left(nullptr), right(nullptr), level(l), value(v) {}
    };

    Node *root;
    size_t _size;

    // Recursively build a subtree that satisfied the KD-Tree invariant using
    // points in [start, end). At each level, we split point into two halves
    // using the median of the points as pivot. The root of the subtree is at
    // level `curLevel`.
    // O(n) time partiioning algorithm is used to locate the median element.
    Node* buildTree(iterator start, iterator end, size_t curLevel);

    // Returns the Node that constains pt if it is present in subtree curTree.
    // Returns the Node below which pt should be inserted if pt is not in the
    // subtree
    Node* findNode(Node* curNode, const X& pt) const;

    // Recursive helper method for kNNValue(pt, k)
    void nearestNeighborRecurse(
            const Node* curNode,
            const X& key,
            BoundedPQueue<Y>& pQueue) const;

    // Recursive helper method for copy constructor and assignement operator.
    // Deep copies tree `root` and returns the root of the copied tree.
    Node* deepcopyTree(Node *tree);

    // Recurisvely free up all resources of subtree rooted at `curNode`
    void destoryTree(Node *curNode);
};

/**  -  -  -  -  - KDTree Implementation Details -  -  -  -  -  **/

template <size_t N, typename Y>
KDTree<N, Y>::KDTree():root(nullptr), _size(0) {}

template <size_t N, typename Y>
KDTree<N, Y>::KDTree(vector<sample>& trainData):KDTree() {
    root = buildTree(trainData.begin(), trainData.end(), 0);
    _size = trainData.size();
}

template <size_t N, typename Y>
KDTree<N, Y>::~KDTree() {
    destoryTree(root);
}

template <size_t N, typename Y>
KDTree<N, Y>::KDTree(const KDTree& rhs) {
    if (this == rhs) {
        return;
    }

    root = deepcopyTree(rhs.root);
}

template <size_t N, typename Y>
KDTree<N,Y>& KDTree<N, Y>::operator=(const KDTree& rhs) {
    if (this == rhs) {
        return;
    }
    root = deepcopyTree(rhs.root);
    return this;
}

template <size_t N, typename Y>
size_t KDTree<N, Y>::dimension() const {
    return N;
}

template <size_t N, typename Y>
size_t KDTree<N, Y>::size() const {
    return _size;
}

template <size_t N, typename Y>
bool KDTree<N, Y>::empty() const {
    return _size == 0;
}

template <size_t N, typename Y>
bool KDTree<N, Y>::contains(const X& pt) const {
    // @TODO implement
}

template <size_t N, typename Y>
void KDTree<N, Y>::insert(const X& pt, const Y& value){
    // @TODO implement
}


template <size_t N, typename Y>
typename KDTree<N, Y>::Node*  KDTree<N,Y>::buildTree(
        KDTree::iterator begin,
        KDTree::iterator end,
        size_t curLevel
        ) {

    if (begin >= end) return nullptr;

    int axis = curLevel % N;

    auto cmp = [axis](const sample& x1, const sample& x2) {
        return x1.first[axis] < x2.first[axis];
    };

    // @Todo replace lib nth_element
    size_t len = end - begin;
    KDTree::iterator mid = begin + (len / 2);
    std::nth_element(begin, mid, end, cmp); // linear time partition

    // move left (if needed) so that all the equal points are to the right
    // The tree will still be balanced as long as there aren't many points
    // that are equal along each axis.
    while (mid > begin && (mid - 1)->first[axis] == mid->first[axis]) {
        --mid;
    }

    Node *newNode = new Node(mid->first, curLevel, mid->second);
    newNode->left = buildTree(begin, mid, curLevel + 1);
    newNode->right = buildTree(mid + 1, end, curLevel + 1);

    return newNode;
}

template <size_t N, typename Y>
typename KDTree<N, Y>::Node* KDTree<N, Y>::deepcopyTree(Node* root) {
    if (root == nullptr) return nullptr;
    Node *newNode = new Node(*root);
    newNode->left = deepcopyTree(root->left);
    newNode->right = deepcopyTree(root->right);
    return newNode;
}

template <size_t N, typename Y>
void KDTree<N, Y>::destoryTree(Node *root) {
    if (root) {
        destoryTree(root->left);
        destoryTree(root->right);
        delete root;
    }
}


#endif /* ifndef KD_TREE_H__ */
