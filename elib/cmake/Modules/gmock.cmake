set(GOOGLE_TEST_DIR ${CMAKE_SOURCE_DIR}/external/googletest)

add_subdirectory(${GOOGLE_TEST_DIR} ${CMAKE_BINARY_DIR}/gtest)

include_directories(${GOOGLE_TEST_DIR}/gtest/include)
include_directories(${GOOGLE_TEST_DIR}/gmock/include)

# define google test function
#
# add_gmock_test(<target> <source>...)
#
# Adds a Google Mock based test executable.
#

function(add_gmock_test target)

    add_executable(${target} ${ARGN})
    target_link_libraries(${target} gmock_main)

    add_test(${target} ${target})

endfunction()
