#include <iostream>
#include <functional>
#include <random>
#include <memory>

void f(int n1, int n2, int n3, int n4, int n5)
{
    std::cout << n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << ' ' << n5 << '\n';
}

int g(int n1)
{
    return n1;
}

struct Foo {
    void print_sum(int n1, int n2)
    {
        std::cout << n1 + n2 << '\n';
    }

    int data = 10;
};

int main(void)
{
    using namespace std::placeholders;  // for _1, _2, _3...

    // demonstrates argument reordereding and pass-by-reference
    int n = 7;
    // (_1, and _2 are from std::placeholders, and represent future
    // arguments that will be passed to f1)
    auto f1 = std::bind(f, _2, 42, _1, std::cref(n), n);

    n = 10;
    f1(111, 222, 1001); // 111 is bound by _1; 222 is bound by _2, 1001 is unused.

    // nested bind subexpressions share the placeholders
    auto f2 = std::bind(f, _3, std::bind(g, _3), _3, 4, 5);
    f2(10, 11, 12); // makes a call to f(12, g(12), 12, 4, 5);

    // common use case: binding a RNG with a distribution.
    std::default_random_engine e;
    std::uniform_int_distribution<> d(0, 10);
    auto rnd = std::bind(d, e);

    for (int i = 0; i < 10; ++i) {
        std::cout << rnd() << ' ';
    }
    std::cout << '\n';


    // bind to a pointer to member function
    Foo foo;
    auto f3 = std::bind(&Foo::print_sum, &foo, 95, _1);
    f3(5);

    // bind to a pointer to data member.
    auto f4 = std::bind(&Foo::data, _1);
    std::cout << "data = " << f4(foo) << '\n';

    // smart pointers can be used to call members of the referenced objects, too
    std::cout << "using shared_ptr " <<  f4(std::make_shared<Foo>(foo)) << '\n' ;
    std::cout << "using unique_ptr " <<  f4(std::make_unique<Foo>(foo)) << '\n' ;

    return 0;
}


