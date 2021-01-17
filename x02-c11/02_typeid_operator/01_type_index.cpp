#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <string>
#include <memory>


// This program is an example of an efficient type-value mapping.

struct A {
    virtual ~A() {}
};

struct B: A {};
struct C: A {};

int main(void)
{
    std::unordered_map<std::type_index, std::string> type_names{
        {std::type_index(typeid(int)), "int"},
        {std::type_index(typeid(double)), "double"},
        {std::type_index(typeid(A)), "A"},
        {std::type_index(typeid(B)), "B"},
        {std::type_index(typeid(C)), "C"},
    };

    int i;
    double d;
    A a;
    std::unique_ptr<A> b(new B);
    std::unique_ptr<A> c(new C);

    std::cout << "i is " << type_names[std::type_index(typeid(i))] << '\n';
    std::cout << "d is " << type_names[std::type_index(typeid(d))] << '\n';
    std::cout << "a is " << type_names[std::type_index(typeid(a))] << '\n';
    std::cout << "b is " << type_names[std::type_index(typeid(*b))] << '\n';
    std::cout << "c is " << type_names[std::type_index(typeid(*c))] << '\n';

    return 0;
}
