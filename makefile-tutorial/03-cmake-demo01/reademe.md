## Single File  demo
### 生成 Makefile 信息

执行 `cmake PATH` , PATH 是 `CMakeLists.txt` 文件所在的目录。cmake 生成的信息会放在当前目录。

```
> cd 03-cmake-demo01
> mkdir build
> cd build
> cmake ..
```

### 执行 make 命令

```
> make 

> ./power 2 10 
2 ^ 10 = 1024

> ./power 7 7 
7 ^ 7 = 823543
```
