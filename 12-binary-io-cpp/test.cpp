#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "solution.h"

#include <iostream>

TEST(test, WriteComplexData) {
    Solution s;

    node data[3] = {{'1', 3.14}, {'2', 0.618}, {'3', 2.718}};
    s.writeComplexData("data-node.bin", data, 3);
}

TEST(test, ReadComplexData) {
    Solution s;

    node *data = new node[3];
    s.readComplexData("data-node.bin", data, 3);

    std::cout << "node size : " << sizeof(node) << std::endl;

    for (size_t i = 0; i < 3; ++i) {
        std::cout << data[i].key << ":" << data[i].value << std::endl;
    }

    delete []data;
}
