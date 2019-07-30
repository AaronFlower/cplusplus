cmake_minimum_required(VERSION 3.9)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(02-inner-product-op)

# get tensorflow include dirs, see https://www.tensorflow.org/how_tos/adding_an_op/
execute_process(COMMAND python3 -c "import tensorflow; print(tensorflow.sysconfig.get_include())" OUTPUT_VARIABLE Tensorflow_INCLUDE_DIRS)
execute_process(COMMAND python3 -c "import tensorflow as tf; print(' '.join(tf.sysconfig.get_link_flags()), end='')" OUTPUT_VARIABLE Tensorflow_LINK_FLAGS)
execute_process(COMMAND python3 -c "import tensorflow as tf; print(' '.join(tf.sysconfig.get_compile_flags()), end='')" OUTPUT_VARIABLE Tensorflow_COMPILE_FLAGS)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")
# C++11 required for tensorflow
set(CMAKE_CXX_FLAGS "-std=c++11 ${Tensorflow_COMPILE_FLAGS} ${CMAKE_CXX_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "-Wl -undefined dynamic_lookup ${Tensorflow_LINK_FLAGS} ${CMAKE_SHARED_LINKER_FLAGS}")

# build the actual operation which can be used directory
include_directories(${Tensorflow_INCLUDE_DIRS})
add_library(inner_product SHARED inner_product.cc)
