#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using std::placeholders::_1;
using std::less;

int main(void)
{
    std::vector<int> data{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};


    int count_ge_3 = std::count_if(data.begin(), data.end(), std::bind(less<int>(), 3, _1));
    std::cout << "count = " << count_ge_3 << '\n';

    int count_lt_3 = std::count_if(data.begin(), data.end(), std::bind(less<int>(), _1, 3));
    std::cout << "count = " << count_lt_3 << '\n';

    return 0;
}
