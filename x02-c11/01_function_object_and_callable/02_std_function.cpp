#include <iostream>
#include <functional>   // std::function

void func(void)
{
    std::cout << __FUNCTION__ << std::endl;
}

class Foo
{
public:
    static int foo_func(int a)
    {
        std::cout << __FUNCTION__ << "(" << a << ") ->: ";
        return a;
    }
};

class Bar
{
public:
    int operator()(int a)
    {
        std::cout << __FUNCTION__ << "(" << a << ") ->: ";
        return a;
    }
};

// 1. std::function 的基本用法。
int main(void)
{
    // 1. 绑定一个普通函数
    std::function<void(void)> fr1 = func;    
    fr1();

    // 2. 绑定一个类的静态成员函数
    std::function<int(int)> fr2 = Foo::foo_func;
    std::cout << fr2(89) << std::endl;

    // 2. 绑定一个类的静态成员函数
    Bar bar;
    fr2 = bar;
    std::cout << fr2(64) << std::endl;

    return 0;
}


