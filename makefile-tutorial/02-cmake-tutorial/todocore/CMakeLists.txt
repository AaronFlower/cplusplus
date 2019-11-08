message("default library type is : ${BUILD_SHARED_LIBS}")

add_library(toDoCore todo.cpp todo.h)

add_subdirectory(unit_test)
