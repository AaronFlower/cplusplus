cmake_minimum_required (VERSION 3.0)

project (BinaryTree)


set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

add_executable(test test.cpp binary_tree.cpp) 

