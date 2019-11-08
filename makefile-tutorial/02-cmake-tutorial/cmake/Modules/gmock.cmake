set(GOOGLE_TEST_DIR "/Users/eason/code/github.com/AaronFlower/leetcode/lib/googletest"
    CACHE PATH "The path to the GoogleMock test framework.")

add_subdirectory(${GOOGLE_TEST_DIR} ${CMAKE_BINARY_DIR}/gtest)

include_directories(SYSTEM ${GOOGLE_TEST_DIR}/gtest/include)
include_directories(SYSTEM ${GOOGLE_TEST_DIR}/gmock/include)


# define a function
#
# add_gmock_test(<target> <source>...)
#
# Adds a Google Mock based test executable, <target>, built from <sources> and
# adds the test so that CTest will run it. Both the executable and the test
# will be named <target>
#
#

function(add_gmock_test target)
    add_executable(${target} ${ARGN})
    target_link_libraries(${target} gmock_main)

    add_test(${target} ${target})

endfunction()
