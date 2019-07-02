#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "solution.h"

#include <iostream>
#include <chrono>

TEST(test, TimeElapsed) {
    Solution s;

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    std::cout << "fib(42) = " << s.fib(42) << std::endl;
    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "Finished at :" << std::ctime(&end_time);
    std::cout << "Elapsed Time:" << elapsed.count() << "s\n";
}
