#include <iostream>
#include <functional>
#include <vector>

template <typename T>
void Func(T t)
{
    std::cout << __FUNCTION__ << ' ' << t << '\n';
}


int main(void)
{

    int i = 1;
    char c = 's';

    // 初始化一个容器，该容器用于保存无返回值 Callable Object,
    // 而我们 Lambda 就是最合适的 Callable Object.
    std::vector<std::function<void()>> v;

    // 类型擦除，闭包中隐藏了具体的类型，将闭包保存起来；
    v.push_back([i]{Func(i);});
    v.push_back([c]{Func(c);});

    // 遍历所有 Callable Object 并调用。
    for (auto &fn:v) {
        fn();
    }

    return 0;

}
