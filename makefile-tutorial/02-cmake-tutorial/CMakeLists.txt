cmake_minimum_required(VERSION 3.15.1)

project("ToDo List")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")

enable_testing()
include(gmock)


# find boost
if (APPLE OR WIN32)
    set(Boost_USE_STATIC_LIBS TRUE)
endif()

find_package(Boost REQUIRED COMPONENTS program_options)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})


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


include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(todocore)

add_executable(todo main.cpp)

target_link_libraries(todo toDoCore ${Boost_LIBRARIES}) # Boost is case sensitive

add_test(maintest todo)
