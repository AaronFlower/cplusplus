cmake_minimum_required(VERSION 3.9)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(cpp-demo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")

enable_testing()
add_subdirectory(lib/googletest)


include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

add_subdirectory(05-any)
add_subdirectory(04-unions)
add_subdirectory(03-custom-iterator)
add_subdirectory(02-three-clock)
add_subdirectory(01-perfect-forward)

add_executable(cpp-demo test.cpp solution.h)
target_link_libraries(cpp-demo gtest_main gmock_main)
