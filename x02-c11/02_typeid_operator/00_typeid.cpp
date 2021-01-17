#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <string>

// non-polymorphic
struct Base {};
struct Derived : Base {};

// polymorphic
struct Base2 {
    virtual void foo() {};
};
struct Derived2 : Base2 {};

int main(void)
{
    int my_int = 89;
    std::string my_str = "sq";
    double *my_double_ptr = nullptr;

    std::cout
        << "        my_int has type: " << typeid(my_int).name()
        << ", type_index: " << std::type_index(typeid(my_int)).hash_code() << '\n'
        << "        my_str has type: " << typeid(my_str).name() << '\n'
        << " my_double_ptr has type: " << typeid(my_double_ptr).name() << '\n';

    // std::cout << my_int is a glvalue expression of polymorphic type;
    // it is evaluated.
    const std::type_info &r1 = typeid(std::cout << my_int); // side-effects: prints 50
    std::cout << '\n' << "std:cout << my_int has type: " << r1.name() << '\n';

    // std::printf() is not a glvalue expression of polymorphic type; NOT evaluated.
    const std::type_info &r2 = typeid(std::printf("%d\n", my_int));
    std::cout << "std::printf(\"%d\\n\", my_int) has type: " << r2.name() << '\n';

    // Non-polymorphic lvalue is a static type
    Derived d1;
    Base &b1 = d1;
    std::cout << "reference to non-polymorphic base: " << typeid(b1).name() << '\n';

    Derived2 d2;
    Base2 &b2 = d2;
    std::cout << "reference to polymorphic base: " << typeid(b2).name() << '\n';

    try {
        // dereference a null pointer: okay for a non-polymorphic expression
        std::cout << "my_double_ptr points to " << typeid(*my_double_ptr).name() << '\n';

        // derefreceing a null pointer: not okay for a polymorphic lvalue.
        Derived2 *bad_ptr = nullptr;
        std::cout << "bad_ptr points to ...";
        std::cout << typeid(*bad_ptr).name() << '\n';
    } catch(const std::bad_typeid &e) {
        std::cout << " caught " << e.what() << '\n';
    }

    return 0;
}
