## CMake BUILD TYPE

在执行 `cmake` 命令时可以指定 `CMAKE_BUILD_TYPE` 的值来设置编译类型。其可取的值为：

- 空
- `Debug`
- `Release`
- `RelWithDebInfo`
- `MinSizeRel`

CMake 预定义了一些属性和变量，通常是 `SOME_VAR_<CONFIG>`, 如 `CMAKE_C_FLAGS_<CONFIG>` 会有预定义变量：

-  `CMAKE_C_FLAGS_DEBUG`
-  `CMAKE_C_FLAGS_RELEASE`
-  `CMAKE_C_FLAGS_RELWITHDEBINFO`
-  `CMAKE_C_FLAGS_MINSIZEREL`

在使用时，如果我们设置了 build type 为 `Debug` , 那么 CMake 会将 `CMAKE_C_FLAGS_DEBUG` 的设置添加到 `CMAKE_C_FLAGS` 上。

我们可以使用 `-LHA` 选项查看 CMake 的预设置。

```
$ cmake -LAH |grep CXX_FLAGS
CMAKE_CXX_FLAGS:STRING=
CMAKE_CXX_FLAGS_DEBUG:STRING=-g
CMAKE_CXX_FLAGS_MINSIZEREL:STRING=-Os -DNDEBUG
CMAKE_CXX_FLAGS_RELEASE:STRING=-O3 -DNDEBUG
CMAKE_CXX_FLAGS_RELWITHDEBINFO:STRING=-O2 -g -DNDEBUG
```

所以可以看到，默认的 `CMAKE_CXX_FLAGS` 为空，只有使用正确的类型才会将相应的标签追加到 `CMAKE_CXX_FLAGS` 上。
