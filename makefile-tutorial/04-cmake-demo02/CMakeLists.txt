# CMake version
cmake_minimum_required (VERSION 3.10)

# Project info
project (Demo)

# 为了避免在 add_executable 添加太多源文件，我们可以直接指定目录来添加
# 查找当前目录下的所有源文件，并将名称保存到 DIR_SRCS 变量
aux_source_directory (. DIR_SRCS)

# add executable file
add_executable (power ${DIR_SRCS})
