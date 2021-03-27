
#include <iostream>
#include <vector>

using std::vector;

int kth(vector<int>::iterator a_begin, vector<int>::iterator a_end, vector<int>::iterator b_begin, vector<int>::iterator b_end, int k)
{
    if (a_begin >= a_end) {
        return *(b_begin + k);
    }

    if (b_begin >= b_end) {
        return *(a_begin + k);
    }

    int i = (a_end - a_begin) / 2;
    int j = (b_end - b_begin) / 2;

    /* std::cout << "i = " << i << " j = " << j << std::endl; */

    if (i + j >= k) {
        if (*(a_begin + i) > *(b_begin + j)) {
            return kth(a_begin, a_begin + i, b_begin, b_end, k);
        } else {
            return kth(a_begin, a_end, b_begin, b_begin + j, k);
        }
    } else {
        if (*(a_begin + i) < *(b_begin + j)) {
            return kth(a_begin + i + 1, a_end, b_begin, b_end, k - i - 1);
        } else {
            return kth(a_begin, a_end, b_begin + j + 1, b_end, k - j - 1);
        }
    }
}

void test_1()
{
    std::cout << "test_1 \n\n";
    vector<int> a{1, 2, 3, 4, 5};
    vector<int> b{6, 7, 8, 9, 10};
    for (int i = 0; i <= 9; ++i) {
        std::cout << i << "th = " << kth(a.begin(), a.end(), b.begin(), b.end(), i) << std::endl;
    }
}

void test_2()
{
    std::cout << "test_2 \n\n";
    vector<int> a{2, 4, 6, 8, 10};
    vector<int> b{1, 3, 5, 7, 9};
    for (int i = 0; i <= 9; ++i) {
        std::cout << i << "th = " << kth(a.begin(), a.end(), b.begin(), b.end(), i) << std::endl;
    }
}

void test_3()
{
    std::cout << "test_3 \n\n";
    vector<int> a{1, 2};
    vector<int> b{3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i <= 9; ++i) {
        std::cout << i << "th = " << kth(a.begin(), a.end(), b.begin(), b.end(), i) << std::endl;
    }
}

int main(void)
{
    test_1();
    test_2();
    test_3();
    return 0;
}
