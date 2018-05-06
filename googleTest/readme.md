## Google C++ Test Framework

目前 Google C++ test Framework 包含了 GoogleTest 和 GooglMock 两个项目。

首先查看[Google Test Primer](https://github.com/google/googletest/blob/master/googletest/docs/Primer.md) 文档。

### 术语命名

ISTQB(Software Testing Qualifications Board), 国际测试资格委员会。

| Meaning                                            | Google Test Term | ISTQB Term |
| -------------------------------------------------- | ---------------- | ---------- |
| 根据指定的输入值执行一个特定的代码路径并验证结果。 | TEST()           | Test Case  |
| 一个模块的一组测试。                               | Test Case        | Test Suite |

### 设置一个测试项目

编写一个 Google Test 的测试程序，首先需要先安装 Google Test 库，并在你的测试程序中链接进来。对于 GNU make 可以使用 `make` 目录下 Makefile 来安装。

#### 1. clone 

```shell
git clone https://github.com/google/googletest.git
```

#### 2. cmake

```bash
mkdir install
cd install
cmake -DCMAKE_CXX_COMPILER="g++" -DCMAKE_CXX_FLAGS="-std=c++11 -stdlib=libc++" ../

tree -L 1
.
├── CMakeCache.txt
├── CMakeFiles
├── Makefile
├── cmake_install.cmake
├── libgtest.a
└── libgtest_main.a
```

#### 3. 拷贝头文件和静态库文件到 include path 中。

 将 `libgtest.a, libgtest_main.a`拷贝到 `/usr/local/lib` 目录中。

```bash
cp *.a /usr/local/lib
cp -R ../include/gtest /usr/local/include
```

这样就可以在我们系统目录中直接引入 Google Test 了。

#### 4. 测试

```
#include <gtest/gtest.h>

int sum(int a, int b) {
    return a + b;
}


TEST(AddTest, PositiveNumbers) {
    EXPECT_EQ(2, sum(1, 1));
    EXPECT_EQ(1024, sum(1000, 24));
}

TEST(AddTest, NegativeNumbers) {
    EXPECT_EQ(0, sum(-1, 1));
    EXPECT_EQ(23, sum(-1, 24));
    EXPECT_EQ(-23, sum(-1, 24));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

编译执行:

注意在后面执行引入的[静态库 gtest](https://github.com/google/googletest/issues/50).

```bash
g++ -o a.out test.cpp -lgtest
./a.out

[==========] Running 2 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 2 tests from AddTest
[ RUN      ] AddTest.PositiveNumbers
[       OK ] AddTest.PositiveNumbers (0 ms)
[ RUN      ] AddTest.NegativeNumbers
test.cpp:16: Failure
Expected equality of these values:
  -23
  sum(-1, 24)
    Which is: 23
[  FAILED  ] AddTest.NegativeNumbers (0 ms)
[----------] 2 tests from AddTest (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test case ran. (0 ms total)
[  PASSED  ] 1 test.
[  FAILED  ] 1 test, listed below:
[  FAILED  ] AddTest.NegativeNumbers

 1 FAILED TEST
```

### 基本概念

在书写 Google Test 时，首先需要先写断言（assertions）用来检测条件是否为 true. 一个断言可以是成功（success）, nonfatal failure (非致命失败)， fatal failure (致命失败)。如果出现致命失败，则会中止函数的执行，否则程序将正常继续执行。



