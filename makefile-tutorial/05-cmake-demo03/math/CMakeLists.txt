# 查找当前目录下的所有源文件
aux_source_directory(. DIR_LIB_SRCS)

# 生成链接库
add_library (myPower ${DIR_LIB_SRCS})
