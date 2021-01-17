## `typeid` operator

C++ 还有一个 `typeid` 操作符？It's crazy.

看一下它的介绍吧。

`typeid` queries information of a type. 用来查询一个类型的相关信息。用于动态类型识别和多态的场景下。

### Syntax

```c++
typeid( type );         // (1)
typeid( expression );   // (2)
```

使用 `typeid` 必须要引入 `<typeinfo>` 头文件，否则执行时会出错。

#### `typeid(type)`

该方法返回一个 `std::type_info` 对象，用于说明 type 的类型。

#### `typeid(expresson)`

检测 expression 的类型。

- typeid 会忽略所有的 top-level cv-qualifiers. 即 `typeid(const T) == typeid(T)`
- typeid 的操作对象 operand 是一个类时，该类一定是要完整定义的，不能是 incomplete type.

#### Notes

1. 在多态类型应用 `typeid` 时，可能会有性能开销(a virtual table lookup), 在其它情况下 `typeid` 可以在编译时解析出来。

2. 在程序结束的 `typeid` 所引用的对象析构函数是否会被调用也是未定义的。

3. 对于同样的类型在执行 `typeid` 时引用的可能不是同一个 `std::type_info` 对象，但可以保证的是 `std::type_info::hash_code` 是一样的, `std::type_index` 是一样的的。

即有如下描述:

```c++
const std::type_info &ti1 = typeid(A);
const std::type_info &ti2 = typeid(A);

assert(&ti1 == &ti2);                                   // Not Guaranteed.
assert(ti1.hash_code() == ti2.hash_code());             // Guaranteed.
assert(std::type_index(ti1) == std::type_index(ti2));   // Guaranteed.
```
