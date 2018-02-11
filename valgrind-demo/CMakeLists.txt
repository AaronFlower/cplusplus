cmake_minimum_required( VERSION 3.10)

#set(CMAKE_C_COMPILER "gcc")
set(CMAKE_C_FLAGS "-Wall -g -O0")

project (testValgrind)

add_executable(testVal main.c)
