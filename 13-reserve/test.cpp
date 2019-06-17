#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "solution.h"

TEST(test, INIT) {
    Solution s;

    std::cout << "\nUsing Reserve "  << std::endl;

    s.usingReserve(100);

    std::cout << "\n\nWithout Using Reservre " << std::endl;
    s.notUsingReserve(100);
}
