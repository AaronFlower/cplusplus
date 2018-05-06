set (GOOGLE_TEST_FLAGS "-lgtest")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GOOGLE_TEST_FLAGS} -g -Wall -std=c++11")

file (GLOB SRCS *.cpp *.h)

add_executable(test ${SRCS})
