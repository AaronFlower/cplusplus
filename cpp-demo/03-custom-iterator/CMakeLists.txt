add_executable(03_custom_iterator mylist.cpp mylist.h)

target_link_libraries(03_custom_iterator gtest_main gmock_main)

add_test(
        NAME 03_custom_iterator
        COMMAND 03_custom_iterator
)