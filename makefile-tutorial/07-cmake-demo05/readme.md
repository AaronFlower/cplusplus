## 安装 

可以利用 CMake 来生成安装 target. 

### Math 目录下 `CMakeLists.txt` 添加

```cmake
# 指定安装路径
# Object file
install (TARGETS myPower DESTINATION bin)
# header file
install (FILES myPower.h DESTINATION include)
```

### 根目录 `CMakeLists.txt` 添加

```cmake
# 安装规则
# object file
install (TARGETS power DESTINATION bin)
# header file
install (FILES "${PROJECT_BINARY_DIR}/config.h" DESTINATION include)
```

### ccamke && make install
对应的文件会安装到默认的 `/usr/local` 目录中。这个目录也是可以配置的。

```bash
$ make install 
Scanning dependencies of target myPower
[ 25%] Building C object math/CMakeFiles/myPower.dir/myPower.c.o
[ 50%] Linking C static library libmyPower.a
[ 50%] Built target myPower
Scanning dependencies of target power
[ 75%] Building C object CMakeFiles/power.dir/main.c.o
[100%] Linking C executable power
[100%] Built target power
Install the project...
-- Install configuration: ""
-- Installing: /usr/local/bin/power
-- Installing: /usr/local/include/config.h
-- Installing: /usr/local/bin/libmyPower.a
-- Installing: /usr/local/include/myPower.h

```


- `/usr/local/bin/power` 可执行文件
- `/usr/local/include/config.h` 可执行头文件
- `/usr/local/bin/libmyPower.a` 以 `.a` 结尾静态库文件。
- `/usr/local/include/myPower.h` 静态库对应的头文件。

因为我们的系统 PATH 配置了 `/usr/local` ，所以现在就可以直接执行 `power` 命令了。

```bash
$ power
Usage: power base exponent

$ power 2 3 
Now we use our own Math library.
 2 ^ 3 = 8

$ which power    
/usr/local/bin/power
```

### 添加测试

CMake 提供了一个 CTest 的测试工具。通过 `add_test` 命令来添加一些测试。

```cmake
# 启用测试
enable_testing()

# 测试程序是否成功运行
add_test (test_run power 2 3)

# 测试程序是否可以正常提示
add_test (test_usage power)
set_tests_properties(
	test_usage 
	PROPERTIES PASS_REGULAR_EXPRESSION "Usage: .* base exponent"
)

# 测试 Case 
add_test(test_5_2 power 5 2)
set_tests_properties(
	test_5_2
	PROPERTIES PASS_REGULAR_EXPRESS "= 25"
)

# 测试 Case 
add_test(test_2_10 power 2 10)
set_tests_properties(
	test_2_10
	PROPERTIES PASS_REGULAR_EXPRESS "= 1024"
)
```

然后执行 `make test`。

```bash
> make test 
Running tests...
Test project /Users/easonzhan/learning/git_repos/cpplus/makefile-tutorial/07-cmake-demo05/build
    Start 1: test_run
1/4 Test #1: test_run .........................   Passed    0.01 sec
    Start 2: test_usage
2/4 Test #2: test_usage .......................   Passed    0.01 sec
    Start 3: test_5_2
3/4 Test #3: test_5_2 .........................   Passed    0.01 sec
    Start 4: test_2_10
4/4 Test #4: test_2_10 ........................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 4

Total Test time (real) =   0.04 sec
```

