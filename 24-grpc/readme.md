## GRPC C++ Helloworld

### Use `protoc` generates cpp files

```shell script
$ cd protos
$ protoc -I ./ --grpc_out=. --plugin=protoc-gen-grpc=/usr/local/bin/grpc_cpp_plugin ./helloworld.proto
$ protoc -I ./ --cpp_out=. ./helloworld.proto
```

### build and run

```c++
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./greeter_server
$ ./greeter_client
```

### Todos

- [ ] Use CMake to generate cpp proto files.

### References
1. [google grpc](https://github.com/grpc/grpc)
2. [google grpc helloworld cpp](https://github.com/IvanSafonov/grpc-cmake-example)
