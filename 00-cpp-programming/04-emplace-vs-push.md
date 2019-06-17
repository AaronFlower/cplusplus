## emplace_back vs. push_back

对于 vector, list, deque 都这两个方法，那么这两个方法有什么不同那？

1. emplace_back 的参数是传的构造函数时的参数。

2. push_back 传的是相应的成员元素对象。

```c++
vector<vector<int>> res;
res.emplace_back();  // 功能上等价于 vector<int> tmp; res.push_back(tmp);
res.emplace_back(3);  // 功能上等价于 vector<int> tmp(3); res.push_back(tmp);
res.emplace_back(3, 5);  // 功能上等价于 vector<int> tmp(3, 5); res.push_back(tmp);
```

两者在功能上是可以等价的。但是 emplace_back 内部调用的是 move 构造函数，而 push_back 调用的是 copy 构造函数。
