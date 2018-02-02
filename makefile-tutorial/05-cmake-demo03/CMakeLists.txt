# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.10)

# Project 信息
project(Demo3)

# 定义源码目录
aux_source_directory (. DIR_SRCS)

# 添加 math 子目录。
add_subdirectory(math)

# 指定生成目标
add_executable(power ${DIR_SRCS})

# 添加链接库，我们将 math 作为静态链接库引入进来
target_link_libraries(power myPower)

