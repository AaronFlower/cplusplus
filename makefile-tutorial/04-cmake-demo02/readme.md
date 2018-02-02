## CMake 多源文件

我们可以将 `power` 函数单独实现。

```
$ tree -I build 
.
├── CMakeLists.txt
├── main.c
├── myPower.c
├── myPower.h
└── readme.md
```

### 更新 CMakeLists.txt 文件配置

出现两个文件，我们只需要简单的更新 `add_executable ` 命令就行了。即

```
add_executable(power main.c myPowr.c)
```

但是如果源文件很多，把所有的源文件都添加进去，就比较繁琐了。所以我们可以使用 `aux_source_directory` 命令来指定到目录中添加所有源文件。所以最终的我们的 `CMakeLists.txt` 文件的内容如下：

```
# CMake version
cmake_minimum_required (VERSION 3.10)

# Project info
project (Demo)

# 为了避免在 add_executable 添加太多源文件，我们可以直接指定目录来添加
# 查找当前目录下的所有源文件，并将名称保存到 DIR_SRCS 变量
aux_source_directory (. DIR_SRCS)

# add executable file
add_executable (power ${DIR_SRCS})
```
