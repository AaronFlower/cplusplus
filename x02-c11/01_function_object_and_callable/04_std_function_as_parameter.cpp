#include <iostream>
#include <functional>

// std::function 作为函数入参, 比函数指针更加灵活。
void call_when_even(int x, const std::function<void(int)> &f)
{
    if (!(x & 1)) {
        f(x);
    }
}

void output(int x)
{
    std::cout << x << ' ';
}

int main(void)
{
    for (int i = 0; i < 10; ++i) {
        call_when_even(i, output);
    } 
    std::cout << std::endl;
    return 0;
}
