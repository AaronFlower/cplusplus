set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++11")

file (GLOB SRCS *.cpp *.h)
add_executable(test ${SRCS})
