## bitset

### 1. Bit Reresentation Class

下图是 252 用 bitset 的表示形式，在 bitset 中最高位是在 0 元素的位置。

![image-20190521112033879](/Users/easonzhan/Library/Application Support/typora-user-images/image-20190521112033879.png)

### 2. Constructing Bitset

- bitset 可以从一个二进制字符串中构建 `bitset<8> bs("11001101");`
- bitset 可以从一个数字中构建  `bitset<8> bs(127)`;
- bitset 默认的构建的 set 中的 bit 默认都为 `0`.

### 3. Setting and Resetting Bits

`bitset` 提供两个成员函数：`set(), reset()`.

- `set(i)`, 将第 i 位置 1; 如果不传参数 i 的话，则将全部 bit 置 1.
- `reset(i)`将第 i 位置 0; 如果不传参数 i 的话，则将全部 bit 置 0.

### 4. Testing the State of Bit

测试 bitset 的方法有以下几种：

- `bs[i] ? "set" : "unset"`;
- `bs.test(i) ? "set" : "unset"`;
- `bs[i] == 1 ? "set" : "unset"`;

即除下用下标访问外，还提供了一个 `test(i)` 函数。遍历 set 可以用下面代码。

```c++
cout << bitset3 << endl; 	// bitset 参 << 进行了重载.
for (int i=0; i<bitset3.size(); i++)
{
    if (bitset3.test(i))
        cout << "Bit " << i << " is Set" << endl;
    else
        cout << "Bit " << i << " is Not Set" << endl;
}
```

#### 5. 其它 API

- `count()` 统计被置 1 的位数；
- `size()` 返回 bitset 的 size.
- `all()` 是否全部被 set
- `none()` 是否全部 unset
- `any()` 如果有一个被 set
- `flip(i)` toggle 一个 bit 位, 参数不传进行全部 toggle.
- `to_long()`
- `to_ullong`
- `to_string()`

### References

1.[C++ Bitset With Example](https://owlcation.com/stem/C-bitset-with-example)

2.[bitset](http://www.cplusplus.com/reference/bitset/bitset/?kw=bitset)

