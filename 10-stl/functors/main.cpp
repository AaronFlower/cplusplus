#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::for_each;
using std::cout;

struct Sum {
    Sum():sum(0) {};
    void operator()(int n) { sum += n;};
    int sum;
};


int main(void)
{
    vector<int> nums{3, 4, 2, 8, 15, 267};

    auto print = [](int n) {cout << n << "\t";};

    cout << "Before: \n";
    for_each(nums.cbegin(), nums.cend(), print);

    cout << "\nAfter +1: \n";
    for_each(nums.begin(), nums.end(), [](int &i){++i;});
    for_each(nums.cbegin(), nums.cend(), print);

    cout << "\nSum: ";

    // for_each 返回的我们传入的 UnaryFunction functor, 函数对象。
    // 函数对象，functor，重载了 `()` 操作的类称为函数对象.
    // 函数对象允许被当作普通函数来调用，就像 Sum() 对象与 print 函数一样，都可以传入 for_each 中
    // 函数对象与函数指针相比有两个优点：1. 函数对象内部可以保持状态，如我们求合调用；
    // 2. 编译器在执行函数对象时可以以内联方式来执行。
    Sum s = for_each(nums.begin(), nums.end(), Sum());
    cout  << s.sum << "\n";

    return 0;
}
