## boost

### Install

1. 下载源文件解压

```
$ cd /usr/local
$ tar --bzip2 -xvf /download/path/boost_1_68_0.tar.bz2
```

2. Hello World

boost 的很多函数和库是不需要编译的，因为是在头文件直接写的 inline 函数。直接引入就行了。

```c++
#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>


int main(void)
{
    using namespace boost::lambda;
    typedef std::istream_iterator<int> in;

    std::for_each(in(std::cin), in(), std::cout << (_1 * 3) << " ");
    return 0;
}
```

3. 编译执行

```
$ g++ -I /usr/local/boost_1_68_0 main.cpp
$ echo 1 2 3 | ./a.out
```

4. vim YCM 支持

在 vim 中通过 `:YcmDebugInfo` 可以查看相关的 Include 信息。在 `ycm_extra_conf.py` 中的 Flags 加入：

```python
[
    '-I',
    '/usr/local/boost_1_68_0'
]
```

### Header-Only Libraries

大部分的 Boost 库都只是头文件，头文件中包含相应的棋牌和 inline 函数，直接引用不用编译就可以使用。

但是也有一部分 Boost Libraries 也需要单独编译, 如下：

- Boost.Chrono
- Boost.Context
- Boost.Filesystem
- Boost.GraphParallel
- Boost.IOStreams
- Boost.Locale
- Boost.Log (see build documentation)
- Boost.MPI
- Boost.ProgramOptions
- Boost.Python (see the Boost.Python build documentation before building and installing it)
- Boost.Regex
- Boost.Serialization
- Boost.Signals
- Boost.System
- Boost.Thread
- Boost.Timer
- Boost.Wave

而下面的一些库，两种模式都是支持的，即可按头文件引入的方式，也可以单独编译：

- Boost.DateTime has a binary component that is only needed if you're using its to_string/from_string or serialization features, or if you're targeting Visual C++ 6.x or Borland.
- Boost.Graph also has a binary component that is only needed if you intend to parse GraphViz files.
- Boost.Math has binary components for the TR1 and C99 cmath functions.
- Boost.Random has a binary component which is only needed if you're using random_device.
- Boost.Test can be used in “header-only” or “separately compiled” mode, although separate compilation is recommended for serious use.
- Boost.Exception provides non-intrusive implementation of exception_ptr for 32-bit _MSC_VER==1310 and _MSC_VER==1400 which requires a separately-compiled binary. This is enabled by #define BOOST_ENABLE_NON_INTRUSIVE_EXCEPTION_PTR.

### Build and Install

如果用到需要单独编译的 Boost libraries, 那我们就需要编译二进制文件了。

```
$ cd /usr/local/boost_1_68_0
$ ./bootstrap.sh --help
$ ./bootstrap.sh --show-libraries

Building Boost.Build engine with toolset darwin... tools/build/src/engine/bin.macosxx86_64/b2

The following Boost libraries have portions that require a separate build
and installation step. Any library not listed here can be used by including
the headers only.

The Boost libraries requiring separate building and installation are:
    - atomic
    - chrono
    - container
    - context
    - contract
    - coroutine
    - date_time
    - exception
    - fiber
    - filesystem
    - graph
    - graph_parallel
    - iostreams
    - locale
    - log
    - math
    - mpi
    - program_options
    - python
    - random
    - regex
    - serialization
    - signals
    - stacktrace
    - system
    - test
    - thread
    - timer
    - type_erasure
    - wave
```
