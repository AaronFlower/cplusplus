## 13-reserve

reserve:

n. 储备，存储；自然保护区；储备金；
vt. 储备; 保留; 预约
vi. 预订

### Allocator

在初始化 vector 的时候我们可以传入自己的 [Allocator](https://en.cppreference.com/w/cpp/named_req/Allocator)。

实现一个 Allocator A 的必选内容有:

- `A::value_type`
- `A::allocate()`
- `A::deallocate()`

### 相关知识点

1. template, 注意要避免 declaration of 'T' shadows template parameter
2. `static_cast`
3. `::operator new(n), ::operator delete(p)`, [Scope for operator new Functions](https://docs.microsoft.com/en-us/cpp/cpp/new-and-delete-operators?view=vs-2019#scope-for-operator-new-functions)


### Output

```bash
[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from test
[ RUN      ] test.INIT

Using Reserve
[+] Allocating 400bytes
[-] Deallocating 400bytes


Without Using Reservre
[+] Allocating 4bytes
[+] Allocating 8bytes
[-] Deallocating 4bytes
[+] Allocating 16bytes
[-] Deallocating 8bytes
[+] Allocating 32bytes
[-] Deallocating 16bytes
[+] Allocating 64bytes
[-] Deallocating 32bytes
[+] Allocating 128bytes
[-] Deallocating 64bytes
[+] Allocating 256bytes
[-] Deallocating 128bytes
[+] Allocating 512bytes
[-] Deallocating 256bytes
[-] Deallocating 512bytes
[       OK ] test.INIT (0 ms)
[----------] 1 test from test (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (0 ms total)
[  PASSED  ] 1 test.
```

### References

1. [std::vector<T, Allocator>::reserve](https://en.cppreference.com/w/cpp/container/vector/reserve)
2. [Scope resolution operator :: (C++ only)](https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.cbclx01/cplr175.htm)
