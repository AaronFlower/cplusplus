#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "solution.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

TEST(test, INIT) {
    std::cout << "Hello stl" << std::endl;
    std::vector<int> v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> v2;
    std::vector<int> vecEven;

    std::copy(v1.begin(), v1.end(), std::back_inserter(v2));
    /* std::copy(v1.begin(), v1.end(), std::front_inserter(v2)); */

    std::for_each(v1.begin(), v1.end(), [](int &x) {x = x * x;});

    for (auto i : v1) {
        std::cout << i << "\t";
    }
    std::cout << std::endl;

    for (auto i : v2) {
        std::cout << i << "\t";
    }
    std::cout << std::endl;

    std::copy(v1.begin(), v1.begin() + 5, v2.begin());

    for (auto i : v2) {
        std::cout << i << "\t";
    }
    std::cout << std::endl;

    std::sort(v2.begin(), v2.end(), [](int x, int y) {return x < y;});

    for (auto i : v2) {
        std::cout << i << "\t";
    }
    std::cout << std::endl;

    std::copy_if(v2.begin(), v2.end(), std::back_inserter(vecEven), [](int x) {
            return x % 2 == 0;
            });
    for (auto i : vecEven) {
        std::cout << i << "\t";
    }
    std::cout << std::endl;

    int sum = 0, product = 1;
    std::for_each(v1.begin(), v1.begin() + 6, [&sum, &product](int x) {
            sum += x;
            product *= x;
            });
    std::cout << sum << "\t" << product << "\t" << std::endl;

    std::string str{"Hello world!"}, upper;
    std::transform(str.begin(), str.end(), std::back_inserter(upper),
            [](char c) {
            return toupper(c);
            });
    std::cout << "Original: " <<  str << std::endl;
    std::cout << "Transformed: " <<  upper << std::endl;

    std::function<int(int)> fib = [&](int n){
        return n < 2 ? n : fib(n - 1) + fib(n - 2);
    };

    std::cout << "fib(10) = " << fib(10) << std::endl;

    auto Fib = [&](int n)->int {
        return n < 2 ? n : fib(n - 1) + fib(n - 2);
    };
    std::cout<< Fib(10) << std::endl;
}

TEST(test, CPP17) {
    std::unordered_map<std::string, int> m;
    m.insert({"apple", 0});
    m.insert({"banana", 1});

    for (auto it = m.begin(); it != m.end(); ++it) {
        auto [key, value] = *it;
        std::cout << key << ": " << value << std::endl;
    }
}
