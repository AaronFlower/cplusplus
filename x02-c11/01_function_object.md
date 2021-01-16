## Function Object

在使用 STL 库时经常会看到一些需要传递 Function Object 的参数。如：

```c++
template< class RandomIt, class Compare >
constexpr void sort( RandomIt first, RandomIt last, Compare comp );
```
第三个参数  comp 就是所需要的 Function Object.

comp	-	comparison function object (i.e. an object that satisfies the requirements of Compare) which returns true if the first argument is less than (i.e. is ordered before) the second.

那什么是 Function Object 那？

### Definition 定义

A FunctionObject type is the type of an object that can be used on the left of the function call operator.

即可以使用 `()` 操作符的对象就是函数对象。所以函数，成员函数，lambda 表达式，以及重载了 `()` 操作符的类实例都是函数对象。

[FunctionObject](https://en.cppreference.com/w/cpp/named_req/FunctionObject)
