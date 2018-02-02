## 多目录多源文件

现在将我们的 `power` 函数的实现放在新建目录中。

```
$ tree 
.
├── main.c
└── math
    ├── myPower.c
    └── myPower.h

1 directory, 3 files
```

这种情况下我们需要分别在两个目录中编写 `CMakeLists.txt` 文件。并将 math 目录里的编译成静态库再由 main 函数调用.

### 根目录 `CMakeList.txt` 文件

```
# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.10)

# Project 信息
project(Demo)

# 定义源码目录
aux_source_directory (. DIR_SRCS)

# 添加 math 子目录。
add_subdirectory(math)

# 指定生成目标
add_executable(power ${DIR_SRCS})

# 添加链接库，我们将 math 作为静态链接库引入进来
target_link_libraries(Demo myPower)
```

### `math` 目录下的 `CMakeLists.txt` 

```
# 查找当前目录下的所有源文件
aux_source_directory(. DIR_LIB_SRCS)

# 生成链接库
add_library (myPower ${DIR_LIB_SRCS})
```
