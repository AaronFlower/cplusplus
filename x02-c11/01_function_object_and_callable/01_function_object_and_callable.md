## Function Object and Callable

### Function Object

在使用 STL 库时经常会看到一些需要传递 Function Object 的参数。如：

```c++
template< class RandomIt, class Compare >
constexpr void sort( RandomIt first, RandomIt last, Compare comp );
```
第三个参数  comp 就是所需要的 Function Object.

comp	-	comparison function object (i.e. an object that satisfies the requirements of Compare) which returns true if the first argument is less than (i.e. is ordered before) the second.

那什么是 Function Object 那？

#### Definition 定义

A FunctionObject type is the type of an object that can be used on the left of the function call operator.

即可以使用 `()` 操作符的对象就是函数对象。所以函数，成员函数，lambda 表达式，以及重载了 `()` 操作符的类实例都是函数对象。

[FunctionObject](https://en.cppreference.com/w/cpp/named_req/FunctionObject)

### Callable Object (可调用对象)

在使用一些 INVOKE 操作时，如：`std::thread, std::bind, std::function, std::invoke` 等需要我们传入 Callable Object。那什么是 Callable Object 那？

满足以下条件的类型 T 就是 Callable Object ：

- `f` 是类型 T 的一个对象。
- `ArgTypes` 是参数类型。
- `R` 返回类型。

则下面的表达式是合法的。

```c++
INVOKE<R>(f, std::declval<ArgTypes>()(...))
```

- 当 `R` 是 `void` 类型时，上面表达式被定义为 `static_cast<void>(INVOKE(f, t1, t2, ..., tN))`, 否则；
- `INVOKE(f, t1, t2, ..., tN)` 将会被隐式转换为 R 类型，其表达式的定义如下：

    - 如果 `f` 是一个指向类 T 的成员函数，则调用类似于。
        ```c++
            (t1.*f)(t2, .., tN);
            // 或
            (t1.get().*f)(t2, ..., tN);
            // 或
            ((*t1).*f)(t2, ..., tN);
        ```
    - 如果 `f` 是一个指向类 T 的成员变量，则调用类似于：
        ```c++
            t1.*f;
            // 或
            t1.get().*f;
            // 或
            (*t1).*f;
        ```

    - 其它情况则，`INVOKE(f, t1, t2, ..., tN)` 等价于 `f(t1, t2, ..., tN)`，即 `f` 是一个 FunctionObject.

**Note**:
    - 对于指向成员函数或变量的指针，t1 可以是一个一般的指针，也可以是重载了 `operator*` 操作符的对象，如 `std::unique_ptr` 或 `std::shared_ptr`。`unique_ptr, shared_ptr` 都重载了操作符 `*`。

    - 指向成员变量的指针也是可调用的 (Callable), 虽然不会函数执行。

##### Standard Library

下面是一些接收 Callable 类型的库函数，不仅仅只接收 FunctionObject.

```
std::function();
std::bind();
std::reference_wrapper();
std::result_of();
std::invoke_result();
std::thread();
std::jthread();
std::call_once();
std::async();
std::packaged_task();
```

C++ 中的可调用对象虽然具有统一的操作形式（除了类成员指针外，都是后面加括号进行调用），但定义方法是五花八门。这样在我们试图使用统一的方式保存，或传递一个可调用对象时，会十分烦琐。

C++11 提供了 `std::function` 和 `std::bind` 统一了可调用对象的各种操作。
