## C++ Binary File I/O

C++ 对文件的操作通常用 `<fstream.h>` 中的三个类来实现。

- ifstream , 仅读文件
- ofstream , 仅写文件
- fstream  , 读写文件

一般，对于二进制文件，你不能使用 `<<` 或 `>>` 操作符；因为二进制文件一般都有约定好的协议。

下面除非明确说明，都是二进制文件。

### Basic Model for File I/O

在 C++ 文件中，文件流类的设计思想是将一个文件看成一个简单的数据流，仅仅是二进制字节的序列。为了方便，字节的序列是从下标 0 开始。

每一个打开的文件都有两个位置。

1. `get pointer`, 当前的读取位置，返回的是下一个将要读取的字节下标。
2. `put pointer`, 当前的写入位置，返回的是下一个将要写入的字节下标。

单字节读取可以使用 `get()` 方法, 而单字节写入可以使用 `put()` 方法。

### Getting The Size fo a File

一般获取文件的大小信息可以使用 C 语言中的 `stat()` 函数。

```c
#include <sys/stat.h>

struct stat res;

if (stat("input.bin", &res) == 0) {
    // The size of the file in bytes is in
    // res.st_size
} else {
    // An error occured
}
```

可以通过 `man 2 stat` 来查询 `stat` 相关说明。

### Opening a File

给出文件名和 IO mode 就可以打开文件了。一般形式如下：

```c
ifstream myFile("data.bin", std::ios::in | std::ios::binary);
ofstream myFile("data.bin", std::ios::out | std::ios::binary);
fstream myFile("data.bin", std::ios::in | std::ios::out | std::ios::binary);
```

另外，还有两个 IO mode.

- `ios::ate` 打开文件后，将指定位的文件尾。
- `ios::trunc` 打开文件后，将文件内容清空。

### Reading From a file

读取文件使用 stream 类的成员函数  `read()`

```c++
basic_istream& read( char_type* s, std::streamsize count );
```

An Example:

```c++
#include <fstream.h>
...
char buffer[100];
ifstream myFile ("data.bin", ios::in | ios::binary);
myFile.read (buffer, 100);
if (!myFile) {
    // An error occurred!
    // myFile.gcount() returns the number of bytes read.
    // calling myFile.clear() will reset the stream state
    // so it is usable again.
}
...
if (!myFile.read (buffer, 100)) {
    // Same effect as above
}
```

### 重定位 "Get" 指针, Repositioning the "Get" Pointer

```c++
basic_istream& seekg( pos_type pos );
basic_istream& seekg( off_type off, std::ios_base::seekdir dir);
```

可以使用 `myFile.tellg()` 来获取当前的 Get 指针位置。

`myFile.seekg(0); // rewind the pointer`

### Writing To a File

```c++
basic_ostream& write( const char_type* s, std::streamsize count );
```

### 重定位 "Put" 指针, Repositioning the "Put" Pointer

```c++
basic_ostream& seekp( pos_type pos );
basic_ostream& seekp( off_type off, std::ios_base::seekdir dir );
```

可以使用 `myFile.seekp()` 来获取当前的 Put 指针位置。

### 读写结构体

通过指针转换，我们可以对结构体进行读写。直接对类和结构体完成序列化真是赞。但是对于

```c++
    #include <fstream.h>
    ...
    class Data {
        int    key;
        double value;
    };

    Data x;
    Data *y = new Data[10];

    fstream myFile ("data.bin", ios::in | ios::out | ios::binary);
    myFile.seekp (location1);
    myFile.write ((char*)&x, sizeof (Data));
    ...
    myFile.seekg (0);
    myFile.read ((char*)y, sizeof (Data) * 10);
```

### peek() 函数

- `file.peek()` 该函数返回下一个位置的字符，但并不移动指针，所以可以用来窥探文件是否到达了文件尾。

### Closing the file

最后别忘记要关闭文件。

```c++
myFile.close();
```

### References

1. [C++ Binary File I/O](https://courses.cs.vt.edu/cs2604/fall02/binio.html)
2. [Binary Files with C++](http://www.eecs.umich.edu/courses/eecs380/HANDOUTS/cppBinaryFileIO-2.html)
