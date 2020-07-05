//
// Created by eason on 2020/7/5.
//

#ifndef CPP_DEMO_VECTOR_HOLDER_H
#define CPP_DEMO_VECTOR_HOLDER_H

#include <vector>
#include <iostream>


class vector_holder {
    std::vector<int> vec_;

public:
    // constructor.
    // copy a vector into this object.
    vector_holder(const std::vector<int> &vec):vec_(vec) {
        std::cout << "copied!" << std::endl;
    }

    // constructor.
    // move a vector into this object.
    // essentially a transfer of ownership.
    vector_holder(std::vector<int>&& vec):vec_(std::move(vec)) {
        std::cout << "moved!" << std::endl;
    }

    // move constructor.
    // instead of copying, we transfer the internals into this object.
    vector_holder(vector_holder&& other):vec_(std::move(other.vec_)) {
    }




};


#endif //CPP_DEMO_VECTOR_HOLDER_H
