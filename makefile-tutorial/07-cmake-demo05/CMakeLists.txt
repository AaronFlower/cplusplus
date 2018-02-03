#CMake Version
cmake_minimum_required (VERSION 3.10)

# 项目信息
project(Demo4)

# 是否使用我们自己的 Math 函数
option(USE_MYMATH
	"Use myMath implementation " ON)


# 配置头文件，可以和源文件传递定义的参数。
configure_file (
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
	)

# 添加 include 目录, 为了能找到 config.h
include_directories("${PROJECT_BINARY_DIR}")

# 根据 USE_MYMATH 来判断是否加入 myPower 库。
if (USE_MYMATH)
	include_directories ("${PROJECT_SOURCE_DIR}/math")
	add_subdirectory (math)
	set (EXTRA_LIBS ${EXTRA_LIBS} myPower)
endif (USE_MYMATH)

# 定义源文件目录
aux_source_directory (. DIR_SRCS)

# add the executable
add_executable (power ${DIR_SRCS})
target_link_libraries (power ${EXTRA_LIBS})

# 安装规则
# object file
install (TARGETS power DESTINATION bin)
# header file
install (FILES "${PROJECT_BINARY_DIR}/config.h" DESTINATION include)


# 启用测试
enable_testing()

# 测试程序是否成功运行
add_test (test_run power 2 3)

# 测试程序是否可以正常提示
add_test (test_usage power)
set_tests_properties(
	test_usage 
	PROPERTIES PASS_REGULAR_EXPRESSION "Usage: .* base exponent"
)

# 测试 Case 
add_test(test_5_2 power 5 2)
set_tests_properties(
	test_5_2
	PROPERTIES PASS_REGULAR_EXPRESS "= 25"
)

# 测试 Case 
add_test(test_2_10 power 2 10)
set_tests_properties(
	test_2_10
	PROPERTIES PASS_REGULAR_EXPRESS "= 1024"
)


# 测试 Case 
add_test(test_2_10 power 2 10)
set_tests_properties(
	test_2_10
	PROPERTIES PASS_REGULAR_EXPRESS "= 1024"
)

# 测试 Case 
add_test(test_2_10 power 2 10)
set_tests_properties(
	test_2_10
	PROPERTIES PASS_REGULAR_EXPRESS "= 1024"
)

