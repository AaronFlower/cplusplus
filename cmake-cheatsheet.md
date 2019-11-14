## CMake Cheatsheet

### Terms

- target: 目标文件, 用 `make help` 可以查看下有那些 targets.


### Commands


1. `project(name)`

为自己的项目起一个名字，可以指定版本、语言、描述；如果项目名称之间有空格需要用 `""` 字符串。

- Synopsis

```
project(<PROJECT-NAME> [<language-name>...])
project(<PROJECT-NAME>
        [VERSION <major>[.<minor>[.<patch>[.<tweak>]]]]
        [DESCRIPTION <project-description-string>]
        [HOMEPAGE_URL <url-string>]
        [LANGUAGES <language-name>...])
```

2. `add_executable(name)`

添加一个可执行文件. 后面跟的是 source 源文件，也可以把头文件加进来；支持 IDE 时会需要这些信息。

```
add_executable(<name> [WIN32] [MACOSX_BUNDLE]
               [EXCLUDE_FROM_ALL]
               [source1] [source2 ...])
add_executable(<name> IMPORTED [GLOBAL])
add_executable(<name> ALIAS <target>)
```

3. `cmake_minimum_required()`

设置 CMake 的最低版本。

4. `enable_testing()`

为当前和子目录开启测试功能.

5. `add_test(testname executable [arg1 ...])`

在用 `enable_testing()` 开启了测试之后，就可以使用该命令来指定测试。该测试命令会被 CTest 执行，测试命令可以是一个测试程序，如：Google Test， script 等。

注意：Tests 并不会自动执行，另外，如果测试程序是项目构建时的一部分，测试 target 并不保证是最新的。最佳实践是在运行测试程序之前先把其它 target 构建好。

在使用了 `enable_testing` 和 `add_test()` 之后，CMake 会在 Makefile 为我们生成一个 test target, 我可以执行 `make test` 来执行测试了, 但是前提是先执行 `make` 。


6. `if(...), elseif(...), else(...), endif(...)`

CMake 中的条件控制流。CMake 的命令都需要用`()` 。

- `if(NOT UNDEFINED_VARIALBE)`, CMake 对于未定义的变量会判断为 `false`. 另外，对于 0, N, NO, OFF, FALSE, NOTFOUND, or varaible-NOTFOUND 也会被判断为 `false`.

7. `set(variableName value...)`

用来设置变量的值。

8. `set(variableName value ... CACHE type docstring [FORCE])`

这种 `set` 允许将变量保存在 CMake 的 cache 中，这个 Cache 是全局和持久的。设置内存很有用，但使用时也要小心。

- type, type 的取值有以下可能的取值。

    - FILEPATH, 文件路径
    - PATH, 文件夹路径
    - STRING, 任意的字符串
    - BOOL, 值为 of/off 的值
    - INTERNAL, 任何类型的值，在 GUI 中没有入口。用来持久化全局变量。

- doctring, 用来描述变量的作用
- FORCE, 如果变量已经存在了，强制更新。

- ex. `set(CMAKE_CXX_FLAGS "${warnings}" CACHE STRING "Flags used by the compiler during all build types." FORCE)`

两个不常用的 target, 可以了解下。

- `make rebuild_cache`
- `make edit_cache`

------------

### Libraries and Subdirectories

添加第三方库和子目录。

在 C/C++ 中一个单独的子目录就是一个 Library, 我们需要配置如何将 Library 给引进来。

9. `include_directories(directories)`

将`directories` 添加到 Include path 中, 当有子目录时需要使用这个命令。

- `CMAKE_CURRENT_SOURCE_DIR` 当前 CMake 运行的目录。

10. `add_subdirectory(source_dir [binary_dir] [EXCLUDE_FROM_ALL])`

添加源文件子目录，子目录必须包含 `CMakeLists.txt` 文件。当目录不是子目录时，需要指定相应的 `binary_dir` 目录用来说明目标文件应该存放在那个目录下。


11. `target_link_libraries(target library...)`

为 `target` 添加依赖的 Library target.

12. `add_library(target [STATIC | SHARED | MODULE] sources...)`

该命令从 sources 中创建一个新的 Library.

- STATIC 是静态库，直接在链接到目标文件上。
- SHARED 是共享库，在运行时加载。

默认可能是 STATIC 或 SHARED 取决于 `BUILD_SHARED_LIBS` 变量, 通常默认是 STATIC  的。

----------

#### Testing -- for real

Google Test 和 Google Mock 提供它们自己的 CMakeLists.txt 文件。

13. `add_subdirectory(${GOOGLE_TEST_DIR} ${CMAKE_BINARY_DIR}/gtest)`

在引用第三方 Library 时，需要指定构建时的 `binary_dir` 的存放目录，可以存储到当前目录下。

- `CMAKE_BINARY_DIR` 运行 `cmake` 命令时的目录。

14. `include_directories([AFTER|BEFORE] [SYSTEM] directory...)`

- `AFTER|BEFORE` 用于指定 include 目录是 append 还 prepend 的方式追加到当前的 include 目录中。
- `SYSTEM` 是否所加到系统目录中。



### Variable

1. `CMAKE_BUILD_TYPE`

`CMAKE_BUILD_TYPE` 用来设置构建的类型，其取值可以是 `Debug, Release, RelWithDebInfo, MinSizeRel`.

CMake 会相应的设置 `CMAKE_<LANG>_FLAGS_<BUILD_TYPE> ` 到 `CMAKE_<LANG>_FLAGS'.

8. `CMAKE_<LANG>_COMPLIER_ID`


- `CMAKE_C_COMPILER_ID`
- `CMAKE_CXX_COMPILER_ID`

用来标识编译器信息。


### function

在 CMake 中，我们可以自定义函数来避免重复自己。定义函数的语法格式:

```
function(<name> [<arg1> ...])
  <commands>
endfunction()
```

- `function(add_gmock_test target)` , `add_gmock_test` 是函数名，`target` 是函数的每一个参数，后面多余的参数被存储在 `ARGN` list 中。
- 另外的魔术变量还有：
    - `ARGC`: 参数的个数
    - `ARGV`: 所有参数
    - `ARG0, ARG1, .... ARGn`: 参数.

### Modules

CMake 也支持用 Modules 来组织文件。

1. `list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)`

将自定义的 Modules 目录添加到 `CMAKE_MODULE_PATH` 中.

2. `include(gmock)`

引入我们的自定义 Moduel, cmake 会搜索 `gmock.cmake` 文件。

3. `list(APPEDN list elements)`

将元素添加到 list 列表中。

### Lists

CMake 内置了两种数据类型：`strings` 和 `list`. 一些 list 的操作:

```
set(myList a b c)
set(myList a;b;c)

list(APPEND myList a b c)  # 推荐使用这种方式，可以明确是一个 list.
```

### Chapter 6: Realistically Getting a Boost

当我们的系统中使用 Boost 第三方库，那我们在构建时怎么把 Boost 给加进来那？

1. `find_package()`


CMake 提供了 `find_package()` 来查找类似于 Boost 的命令。

- [深入理解CMake(3):find_package()的使用](https://www.jianshu.com/p/39fc5e548310)

 CMake searches for a file called Find<package>.cmake in the CMAKE_MODULE_PATH followed by the CMake installation. If the file is found, it is read and processed by CMake. It is responsible for finding the package, checking the version, and producing any needed messages.

ex:

```
find_package(Boost 1.32 REQUIRED COMPONENTS program_options)
```

CMake 会在 `CMAKE_MODULE_PATH` 中寻找到 FindBoost.cmake 文件，然后执行该文件处理相应的信息。 在 Mac 下是去 `/usr/local/Cellar/cmake/3.15.1/share/cmake/Modules` 目录中寻找。

那么 `FindBoost.cmake` 做了那些工作那，暴露出那些变量了那？我们可以使用 `cmake --help-module FindBoost` 来查看。

- `cmake --help-module FindBoost`
- `cmake --help-module FindJpeg`

```
❯ cmake --help-module FindJpeg
FindJPEG
--------

Find the Joint Photographic Experts Group (JPEG) library (``libjpeg``)

Imported targets
^^^^^^^^^^^^^^^^

This module defines the following ``IMPORTED`` targets:

``JPEG::JPEG``
  The JPEG library, if found.

Result variables
^^^^^^^^^^^^^^^^

This module will set the following variables in your project:

``JPEG_FOUND``
  If false, do not try to use JPEG.
``JPEG_INCLUDE_DIRS``
  where to find jpeglib.h, etc.
``JPEG_LIBRARIES``
  the libraries needed to use JPEG.
``JPEG_VERSION``
  the version of the JPEG library found

Cache variables
^^^^^^^^^^^^^^^

The following cache variables may also be set:

``JPEG_INCLUDE_DIRS``
  where to find jpeglib.h, etc.
``JPEG_LIBRARY_RELEASE``
  where to find the JPEG library (optimized).
``JPEG_LIBRARY_DEBUG``
  where to find the JPEG library (debug).

Obsolete variables
^^^^^^^^^^^^^^^^^^

``JPEG_INCLUDE_DIR``
  where to find jpeglib.h, etc. (same as JPEG_INCLUDE_DIRS)
``JPEG_LIBRARY``
  where to find the JPEG library.

```

一般 Module 会至少定义以下变量：

- Package_FOUND: 标识是否找到
- Package_INCLUDE_DIRS : include 目录，供 `include_directories()` 命令使用。
- Package_LIBRARIES : 库文件，供 `target_link_libraries()` 命令使用.
- Package_DEFINITIONS

```
❯ cmake ..
-- Found JPEG: /usr/local/lib/libjpeg.dylib (found version "90")
CMake Error at /usr/local/Cellar/cmake/3.15.1/share/cmake/Modules/FindPackageHandleStandardArgs.cmake:137 (message):
  Could NOT find Boost (missing: Boost_INCLUDE_DIR program_options)
Call Stack (most recent call first):
  /usr/local/Cellar/cmake/3.15.1/share/cmake/Modules/FindPackageHandleStandardArgs.cmake:378 (_FPHSA_FAILURE_MESSAGE)
  /usr/local/Cellar/cmake/3.15.1/share/cmake/Modules/FindBoost.cmake:2142 (find_package_handle_standard_args)
  CMakeLists.txt:24 (find_package)


-- Configuring incomplete, errors occurred!
See also "/Users/eason/code/github.com/AaronFlower/cplusplus/makefile-tutorial/02-cmake-tutorial/build/CMakeFiles/CMakeOutput.log".
```

发现找不到 Boost 库，是因为本地没有安装，用 homebrew 安装一下 boost 就行了.



我们可以使用 `cmake --find-pacakge` 来查找相应的库, 使用该选项会执行 [CMakeFindPackageMode](https://cmake.org/cmake/help/v3.0/module/CMakeFindPackageMode.html) 该模块文件，它需要用 `-D` 指定四个变量参数。

```
NAME = name of the package
COMPILER_ID = the CMake compiler ID for which the result is, i.e. GNU/Intel/Clang/MSVC, etc.
LANGUAGE = language for which the result will be used, i.e. C/CXX/Fortan/ASM
MODE = EXIST : only check for existence of the given package
       COMPILE : print the flags needed for compiling an object file which uses the given package
       LINK : print the flags needed for linking when using the given package
QUIET = if TRUE, don't print anything
```

```
❯ cmake --find-package -DNAME=Boost -DCOMPILER_ID=Clang -DLANGUAGE=CXX -DMODE=EXIST
Boost not found.
CMake Error: Problem processing arguments. Aborting.


❯ cmake --find-package -DNAME=JPEG -DCOMPILER_ID=Clang -DLANGUAGE=CXX -DMODE=EXIST
JPEG found.

❯ cmake --find-package -DNAME=JPEG -DCOMPILER_ID=Clang -DLANGUAGE=CXX -DMODE=COMPILE
-I/usr/local/include

❯ cmake --find-package -DNAME=JPEG -DCOMPILER_ID=Clang -DLANGUAGE=CXX -DMODE=LINK
/usr/local/lib/libjpeg.dylib

❯ brew info jpeg
jpeg: stable 9c (bottled)
Image manipulation library
https://www.ijg.org/
/usr/local/Cellar/jpeg/9c (21 files, 741.7KB) *
  Built from source on 2019-10-09 at 00:09:03
From: https://github.com/Homebrew/homebrew-core/blob/master/Formula/jpeg.rb
==> Analytics
install: 118,249 (30 days), 329,462 (90 days), 1,304,832 (365 days)
install_on_request: 3,823 (30 days), 12,489 (90 days), 55,152 (365 days)
build_error: 0 (30 days)

❯ ll /usr/local/lib/libjpeg.dylib
lrwxr-xr-x  1 eason  admin    35B Oct  9 00:09 /usr/local/lib/libjpeg.dylib -> ../Cellar/jpeg/9c/lib/libjpeg.dylib
```

#### `cmake --help-modules` 可以查看所有可用的 Module.

#### 编写自己的 `FindModule` 可以参考下面的链接

[cmake-developer](https://cmake.org/cmake/help/v3.14/manual/cmake-developer.7.html#id2)

​	