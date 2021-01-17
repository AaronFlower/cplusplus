#include <iostream>
#include <functional>

struct Foo {
    Foo(int num): num_(num) {}
    void print_add(int i) const 
    {
        std::cout << "Foo " << __FUNCTION__ << " " << num_ + i << '\n';
    }
    int num_;
};

void print_num(int i)
{
    std::cout << "free function " << __FUNCTION__ << " " << i << '\n';
}

struct PrintNum {
    void operator()(int i) const 
    {
        std::cout << "PrintNum " << __FUNCTION__ << " " << i << '\n';
    }
};

int main(void)
{
    // store a free function
    std::function<void(int)> f_display = print_num;     
    f_display(-9);

    // store a lambda
    std::function<void()> f_display_42 = [](){print_num(42); };
    f_display_42();

    // store the result of a call to std::bind
    std::function<void()> f_display_89 = std::bind(print_num, 89);
    f_display_89();

    // store a call to a member function
    std::function<void(const Foo&, int)> f_add_display = &Foo::print_add;

    // create a Foo object explicitly.
    const Foo foo(60);
    f_add_display(foo, 4);

    // create a Foo object implicitly.
    f_add_display(70, 4);

    // store a data member accessor.
    std::function<int(const Foo&)> f_num  = &Foo::num_;
    std::cout << "num_: " << f_num(foo) << '\n';

    // store a call to a member function and object.
    using std::placeholders::_1;
    std::function<void(int)> f_add_display_2 = std::bind(&Foo::print_add, foo, _1);
    f_add_display_2(2);

    // store a call to a member function and object ptr
    std::function<void(int)> f_add_display_3 = std::bind(&Foo::print_add, &foo, _1);
    f_add_display_3(3);

    // store a call to a function object.
    std::function<void(int)> f_display_obj = PrintNum();
    f_display_obj(22);

    return 0;
}

