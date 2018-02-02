# 添加当前目录变量
aux_source_directory (. DIR_LIB_SRCS)

# 指定生成 myPower 链接库

add_library (myPower ${DIR_LIB_SRCS})
