## IoC

### 类型擦除

在实现一个 IoC 容器时，我们为了通用性可能需要将某些类型进行隐藏。下面是一些常用的类型擦除方法。

1. 通过多态；
2. 通过模板；
3. 通过某种类型容器，如 `std::Variant`;
4. 通过某种能用类型, 如 `std::Any`
5. 通过闭包来擦除类型。

上面 5 种方法都有自己的优缺点：

通过多态需要与基类型进行耦合; 模板也需要始终为某个具体的类型；Variant, Any 在具体初始化和使用时也需要指定类型; 相比较而言闭包会更加方便宜用些。

#### 如何实现一个 Any 类？

我们可能需要依赖于 C++ 的 [types support library](https://en.cppreference.com/w/cpp/types), 另外还需要 `typeid` 操作符。

##### `typeid` 操作符

C++ 还有一个`typeid` 操作符吗？