add_executable(02_clock_test clock_test.cpp clock_helper.h)

target_link_libraries(02_clock_test gtest_main gmock_main)

add_test(
        NAME 02_clock_test
        COMMAND 02_clock_test
)