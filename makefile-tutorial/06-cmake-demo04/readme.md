## 自定义编译选项

我们在用 CMake 来生成 Makefile 的时候，可以指定配置选择来决定编译的方式。在这个 demo 中，我们通过添加一个可配置 `USE_MYMATH` 宏来决定是否使用我们自己的编写的库函数。

### `CMakeLists.txt`

```
#CMake Version
cmake_minimum_required (VERSION 3.10)

# 项目信息
project(Demo4)

# 是否使用我们自己的 Math 函数
option(USE_MYMATH
	"Use myMath implementation " ON)


# 配置头文件，可以和源文件传递定义的参数。
configure_file (
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
	)

# 添加 include 目录, 为了能找到 config.h
include_directories("${PROJECT_BINARY_DIR}")

# 根据 USE_MYMATH 来判断是否加入 myPower 库。
if (USE_MYMATH)
	include_directories ("${PROJECT_SOURCE_DIR}/math")
	add_subdirectory (math)
	set (EXTRA_LIBS ${EXTRA_LIBS} myPower)
endif (USE_MYMATH)

# 定义源文件目录
aux_source_directory (. DIR_SRCS)

# add the executable
add_executable (power ${DIR_SRCS})
target_link_libraries (power ${EXTRA_LIBS})
```

- `option` 命令：定义一个 CMake 可以设置的宏。
- `configure_file` 命令：定义输入输出头文件。
- `if` 通过判断在执行 `ccmake ..` 时是否设置了 `USER_MYMATH` 选项。

math 子目录下 `CMakeLists.txt` 内容不变。


### ccmake

执行交互式 `ccmake` , 会生成 `config.h` 文件。
```
> mkdir build
> cd build
> ccmake .. # 交互式编译
```

当 `USE_MYMATH` 为 `ON` 时，生成的 `config.h` 的内容如下：

```
#define USE_MYMATH
```

为 `OFF` 时，生成的 `config.h` 内容如下：
```
/* #undef USE_MYMATH */
```

### `USE_MYMATH ON` make & exec

会链接静态库。

```
> make 
Scanning dependencies of target myPower
[ 25%] Building C object math/CMakeFiles/myPower.dir/myPower.c.o
[ 50%] Linking C static library libmyPower.a
[ 50%] Built target myPower
Scanning dependencies of target power
[ 75%] Building C object CMakeFiles/power.dir/main.c.o
[100%] Linking C executable power
[100%] Built target power

> ./power 2 3  
Now we use our own Math library.
 2 ^ 3 = 8
``` 

### `USE_MYMATH OFF` make & exec
```
> make  
Scanning dependencies of target power
[ 50%] Building C object CMakeFiles/power.dir/main.c.o
[100%] Linking C executable power
[100%] Built target power

> ./power 2 3
Now we use standard library.
 2 ^ 3 = 8
```