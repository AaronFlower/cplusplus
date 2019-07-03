/**
 * File: point.h
 * A class representating a point in N-dimensional space
 * Point is parameterized over an integer N.
 * This allows the compiler to verify the type being used correctly
 */

#ifndef POINT_HEAD__
#define POINT_HEAD__

#include <cassert>    // for cassert
#include <algorithm>  // for equal

using std::size_t;

template<size_t N>
class Point {
public:
    // Types representating iterators that can traverse and optionally modify
    // the elements of the Point.
    typedef double* iterator;
    typedef const double* const_iterator;

    size_t size();

    // Queries or retrieves the value of the point at a particular point.
    double& operator[](size_t index);
    double operator[](size_t index) const;

    // Returns iterators delineating the full range of elements in the Point.
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

private:
    double coords[N];
};

// Using non-member method to overload operator `==` and `!=`
template <size_t N>
bool operator==(const Point<N> &lhs, const Point<N> &rhs);

template <size_t N>
bool operator!=(const Point<N> &lhs, const Point<N> &rhs);

// Return the Squared Euclidean distance between two points.
template <size_t N>
double EuclideanDistance(const Point<N> &lhs, const Point<N> &rhs);

/** - - - - - Implimentation - - - - -  **/

template <size_t N>
size_t Point<N>::size() {
    return N;
}

template <size_t N>
double& Point<N>::operator[](size_t index) {
    assert(index < N);
    return &coords[index];
}

template <size_t N>
double Point<N>::operator[](size_t index) const {
    assert(index < N);
    return coords[index];
}


template <size_t N>
typename Point<N>::iterator Point<N>::begin() { // Don't miss typename
    return coords;
}

template <size_t N>
typename Point<N>::iterator Point<N>::end() {
    return coords + N;
}

template <size_t N>
typename Point<N>::const_iterator Point<N>::begin() const {
    return coords;
}

template <size_t N>
typename Point<N>::const_iterator Point<N>::end() const {
    return coords + N;
}

template <size_t N>
bool operator==(const Point<N> &lhs, const Point<N> &rhs) {
    return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <size_t N>
bool operator!=(const Point<N> &lhs, const Point<N> &rhs) {
    return !(lhs == rhs);
}

template <size_t N>
double EuclideanDistance(const Point<N> &lhs, const Point<N> &rhs) {
    double dist = 0.0;
    for (size_t i = 0; i < N; ++i) {
        double diff = lhs[i] - rhs[i];
        dist += diff * diff;
    }
    return dist;
}

#endif /* ifndef POINT_HEAD__ */
