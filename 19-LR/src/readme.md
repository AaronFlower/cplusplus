## src

### Test LR with gtest

```bash
$ cd src
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./lr
```

### Generate the Python moudle

```bash
$ cd src
$ make
$ make test
$ make install
$ make clean
```

### Tips

在使用 SWIG 来封装 c++ 时，需要注意的点有：

1. Python 的 headers, 和库文件版本也指定正确。
2. C++ 中声明的方法要实现。
