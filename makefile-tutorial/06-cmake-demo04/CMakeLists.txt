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



