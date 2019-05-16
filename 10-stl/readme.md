## STL

STL (标准模版库，Standard Template Library), 提供四个组件：

- containers
- algorithms
- functions
- iterators

### Containers, 容器

STL 提供的有
1. 顺序容器, sequence containers (vector, list, deque)
2. 关联容器, associative containers (set, multiset, map, multimap, hash_set, hash_map, hash_multiset, hash_multimap).
3. **容器适配器, container adapter (queue, priority_queue, stack)**.
4. 其它容器，如：pair

STL 并不是 C++ 标准，只是大部分已经是 C++ 标准了。而 hash_set, hash_map, hash_multiset, hash_multimap 在引入标准中都换了名字，把 hash 换成了 unordered; 即 unordered_set, unordered_multiset, unordered_map, unordered_multimap.

### Algorithms `#include<algorithm>`

[Algorithms]([http://www.cplusplus.com/reference/algorithm/](http://www.cplusplus.com/reference/algorithm/)) 提供了很多常用的函数供我们使用。最常用的有：[**min**](http://www.cplusplus.com/reference/algorithm/min/)**,** [**max**](http://www.cplusplus.com/reference/algorithm/max/)**,** [**swap**](http://www.cplusplus.com/reference/algorithm/swap/)**,** [**sort**](http://www.cplusplus.com/reference/algorithm/sort/)**,** [**next_permutation**](http://www.cplusplus.com/reference/algorithm/next_permutation/)**,** [**binary_search**](http://www.cplusplus.com/reference/algorithm/binary_search/)**,** [**rotate**](http://www.cplusplus.com/reference/algorithm/rotate/)**,**[**reverse**](http://www.cplusplus.com/reference/algorithm/reverse/); 还有操作集合上操作：set_union，set_intersection，set_difference
set_symmetric_difference，merge, inplace_merge, includes。

### 迭代器

[迭代器](https://zh.wikipedia.org/wiki/迭代器)是泛化的指针，通过使用迭代器，开发者可以操作数据结构而无需关心其内部实现。根据迭代器的操作方式的不同，迭代器分为五种[[3\]](https://zh.wikipedia.org/wiki/标准模板库#cite_note-3)：

- 输入迭代器
- 输出迭代器
- 前向迭代器
- 双向迭代器
- 随机访问迭代器

### References

1.[Data structures and algorithms problems in C++ using STL](https://medium.com/@codingfreak/data-structures-and-algorithms-problems-in-c-using-stl-7900a6ddb1d4)

2. [STL wiki](https://en.wikipedia.org/wiki/Standard_Template_Library)