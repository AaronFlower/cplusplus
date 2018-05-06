cmake_minimum_required (VERSION 3.0)

project (binarySearchTree)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++11")

add_executable(test test.cpp binary_search_tree.cpp)
