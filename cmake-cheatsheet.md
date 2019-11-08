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
