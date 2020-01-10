cmake_minimum_required(VERSION 3.15)
project(grpc)

set(CMAKE_CXX_STANDARD 17)

# GRPC libraries
list(APPEND CMAKE_PREFIX_PATH "/usr/local")

# Cmake find modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(GRPC REQUIRED)
find_package(Protobuf REQUIRED)

include_directories(SYSTEM ${GRPC_INCLUDE_DIR})


add_executable(hello main.cpp)
add_executable(wordbreak 139-word_break.cpp)
add_executable(wordbreak2 139-word_break_2.cpp)

add_executable(greeter_server greeter_server.cpp protos/helloworld.grpc.pb.cc protos/helloworld.pb.cc)

target_link_libraries(greeter_server gRPC::grpc++_reflection protobuf::libprotobuf)

add_executable(greeter_client greeter_client.cpp protos/helloworld.grpc.pb.cc protos/helloworld.pb.cc)

target_link_libraries(greeter_client gRPC::grpc++_reflection protobuf::libprotobuf)
