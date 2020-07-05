add_executable(01_perfect_forward_test perfect_forward_test.cpp)

target_link_libraries(01_perfect_forward_test gtest_main gmock_main)


add_test(
        NAME perfect_forward_test
        COMMAND 01_perfect_forward_test
)
