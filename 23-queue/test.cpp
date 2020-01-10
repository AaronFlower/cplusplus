#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "solution.h"

#include <iostream>

TEST(test, INIT) {
    std::cout << "Hello 23-queue" << std::endl;
    Solution s;
    s.testQueue();

}
