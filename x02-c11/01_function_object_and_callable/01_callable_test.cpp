#include <iostream>

void func(void)
{
    std::cout << "void pure function" << std::endl;
}

struct Foo {
    void operator()(void) 
    {
        std::cout << "foo overload operator() " << std::endl;
    }
};

struct Bar {
    using fr_t = void(*)(void);
    typedef void(*fp_t)(void);

    static void func(void)
    {
        std::cout << "Bar static func" << std::endl;
    }

    operator fr_t(void)
    {
        return func;
    }
};

struct A {
    int a_;
    void mem_func(void)
    {
        std::cout << "A member func" << std::endl;
    }
};


/*
C++ 中的可调用对象虽然具有统一的操作形式（除了类成员指针外，都是后面加括号进行调用），但定义方法是五花八门。这样在我们试图使用统一的方式保存，或传递一个可调用对象时，会十分烦琐。

C++11 提供了 `std::function` 和 `std::bind` 统一了可调用对象的各种操作。
*/


int main(void)
{
    void (* func_ptr)(void) = &func;    // 1. 函数指针；
    func_ptr();

    Foo foo;                            // 2. 仿函数
    foo();

    Bar bar;                            // 3. 可以转换为函数指针的类对象
    bar();
    
    // 指向类成员函数的指针，及调用方法。
    void (A::*mem_func_ptr)(void);      // 4. 指向类成员函数的指针。
    mem_func_ptr = &A::mem_func;

    A aa;
    (aa.*mem_func_ptr)();

    // 指向类成员变量的指针，及调用方法。
    int A::*mem_obj_ptr;
    mem_obj_ptr = &A::a_;

    A bb;
    bb.*mem_obj_ptr = 123;

    std::cout << "bb.a_ = " << bb.a_ << std::endl;

    return 0;
}
