cmake_minimum_required(VERSION 3.15.1)

project("ToDo List")

enable_testing()

message("cmake complier: ${CMAKE_CXX_COMPILER_ID}")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
        "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR
        "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")

    set(warnings "-Wall -Wextra -Werror")

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")

    set(warnings "/W4 /Wx /EHsc")

endif()

set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${warnings}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings}")


add_executable(todo main.cpp todo.cpp)

add_test(todoTest todo)
