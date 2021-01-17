#include <iostream>
#include <functional>

// class A 的构函数需要一个 Callable Object 作为回调。
// 初始化我们可以传入任何 Callable Object, 当然我们也可以传入任何的 Function Object.
class A
{
public:
    A (std::function<void()> f): callback_(f) {};

    void notify(void)
    {
        callback_();
    }

private:
    std::function<void()> callback_;
};

struct Foo {
    void operator()(void) 
    {
        std::cout << "Foo " << __FUNCTION__ << " " << '\n';
    }
};

// std::function 作为回调函数的示例。
int main(void)
{
    const Foo f;
    A a(f);
    a.notify();
        
    return 0;
}
