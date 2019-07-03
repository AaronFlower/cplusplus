#ifndef BOUNDED_PRIORITY_QUEUE_H__
#define BOUNDED_PRIORITY_QUEUE_H__

/**
 * Code Reference: Author: Keith Schwarz (htiek@cs.stanford.edu)
 * https://github.com/junjiedong/KDTree/blob/master/src/BoundedPQueue.h
 *
 * A bounded priority queue is in many ways like a regular priority queue.
 * It stores a collection of elements tagged with a real-valued priority,
 * and allows for access to the element whose priority is the smallest.
 *
 * However, unlike a regular priority queue, the number of elements in a
 * bounded priority queue has a hard limit that is specified in the constructor
 *
 * We use a multimap to implement the priority queue instead of a heap.
 *
 *  Internally, the elements in a map are always sorted by its key following a
 *  specific strict weak ordering criterion indicated by its internal
 *  comparison object (of type Compare).
 *
 * @TODO use heap to implement the bouned priority queue.
 *
 */

#include <map>
#include <algorithm>
#include <limits>

using std::size_t;

template <typename T>
class BoundedPQueue {
public:
    explicit BoundedPQueue(size_t maxSize);

    void enqueue(const T& value, double priority);

    T dequeueMin();

    size_t size() const;
    size_t maxSize() const;
    bool empty() const;

    // best() returns the smallest priority of an element in the container.
    double best() const;

    // best() returns the largest priority of an element in the container.
    double worst() const;

private:
    std::multimap<double, T> elems;
    size_t maximumSize;
};

/**  -  -  -  -  - BoundedPQueue Implementation details - - - - - **/

template <typename T>
BoundedPQueue<T>::BoundedPQueue(size_t size):maximumSize(size) {}

template <typename T>
void BoundedPQueue<T>::enqueue(const T& value, double priority) {
    elems.emplace(priority, value);

    if (elems.size () > maximumSize) {
        // we can erase(begin()), but we can not erase(rbegin())
        // because begin() return iterator and rbeing() return reverse_iterator
        // elems.erase(elems.rbegin());
        auto last = elems.end();
        --last;
        elems.erase(last);
    }
}

template <typename T>
T BoundedPQueue<T>::dequeueMin() {
    if (empty()) {
        throw std::out_of_range("access out of range");
    }

    T v = elems.begin()->second;
    elems.erase(elems.begin());
    return v;
}

template <typename T>
size_t BoundedPQueue<T>::size() const {
    return elems.size();
}

template <typename T>
size_t BoundedPQueue<T>::maxSize() const {
    return maximumSize;
}

template <typename T>
bool BoundedPQueue<T>::empty() const {
    return elems.empty();
}

template <typename T>
double BoundedPQueue<T>::best() const {
    if (empty()) {
        throw std::out_of_range("access out of range");
    }
    return elems.begin()->first;
}

template <typename T>
double BoundedPQueue<T>::worst() const {
    if (empty()) {
        throw std::out_of_range("access out of range");
    }
    return elems.rbegin()->first;
}

#endif /* ifndef BOUNDED_PRIORITY_QUEUE_H__ */
