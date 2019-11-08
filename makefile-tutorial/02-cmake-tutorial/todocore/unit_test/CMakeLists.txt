set(GOOGLE_TEST_DIR "/Users/eason/code/github.com/AaronFlower/leetcode/lib/googletest")

add_subdirectory(${GOOGLE_TEST_DIR} ${CMAKE_BINARY_DIR}/gtest)

include_directories(SYSTEM ${GOOGLE_TEST_DIR}/gtest/include)
include_directories(SYSTEM ${GOOGLE_TEST_DIR}/gmock/include)

add_executable(todoTest todo_test.cpp)
target_link_libraries(todoTest toDoCore gmock_main gtest_main)

add_test(todotest todoTest)
