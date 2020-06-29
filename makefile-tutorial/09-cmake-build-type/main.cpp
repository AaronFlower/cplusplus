#include <iostream>

int main(int argc, char *argv[])
{
    int sum = 0;
    for (int i  = 0 ; i < 10; ++i ) {
        bool is_even = i % 2 == 0;
        if (is_even) {
            sum += i;
        }
    }

    std::cout << "sum = " << sum << std::endl;

    int *data = nullptr;

    std::cout << "data[2]:" << data[2] << std::endl;

    return 0;
}
