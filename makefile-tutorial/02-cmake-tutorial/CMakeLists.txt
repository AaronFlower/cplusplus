cmake_minimum_required(VERSION 3.15.1)

project("ToDo List")

enable_testing()

add_executable(todo main.cpp todo.cpp)

add_test(todoTest todo)
