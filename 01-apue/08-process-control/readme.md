## fork

`fork()` create a new process. 调用一次，返回两次。创建的子进程和父进程共享资源，有些资源是完全 copy 一份的 (描述符文件引用共享，堆栈资源共享，但其上的变量会复制一份）。所以 `8.1` 例子真的非常经典，在 console 中执行和重定向执行时共享标准输出，变量。

在网络编程时，父进程的 socket 也会被共享，我们可以在子进程关闭它。

fork() causes creation of a new process. The new process (child process) is an exact copy of the calling process (parent process) except for the following:
    - The child process has a unique process ID.
    - The child process has a different parent process ID.
    - The child process has its own copy of the parent's descriptors.  These descriptors reference the same underlying objects, so that, for instance, file pointers in file objects are shared between the child and the parent, so that an lseek(2) on a descriptor in the child process can affect a subsequent read or write by the parent.  This descriptor copying is also used by the shell to establish standard input and output for newly created processes as well as to set up pipes.

### 例子1：`01-fork.c`

- 在 console 中执行得到结果如下：

```
❯ ./1.out
a write to stdout
before fork
pid = 48434, glob = 7, var = 89
pid = 48428, glob = 6, var = 88

```
- 而在重定向文件中执行得到如下：

```
❯ ./1.out > 1.txt
~/code/github.com/AaronFlower/cplusplus/01-apue/08-process-control master*
❯ cat 1.txt
a write to stdout
before fork
pid = 49042, glob = 7, var = 89
before fork
pid = 49036, glob = 6, var = 88

```
这是因为在命令行中直接输出会受缓冲区 flush 的影响，而在重重定向后父进程和子进程的文件描述符是共享的，标准输出被拷贝了一份所以输出是分离的。

### `02-fork.c`

```
❯ ./a.out
a write to stdout
before fork
pid = 60342, glob = 6, var = 88
pid = 60348, glob = 7, var = 89
pid = 60348, glob = 7, var = 89
pid = 60342, glob = 6, var = 88
pid = 60348, glob = 7, var = 89
pid = 60342, glob = 6, var = 88
pid = 60348, glob = 7, var = 89
pid = 60342, glob = 6, var = 88
pid = 60348, glob = 7, var = 89
pid = 60342, glob = 6, var = 88

~/code/github.com/AaronFlower/cplusplus/01-apue/08-process-control master
❯ ./2.out >2.txt

~/code/github.com/AaronFlower/cplusplus/01-apue/08-process-control master
❯ cat 2.txt
a write to stdout
before fork
pid = 60930, glob = 7, var = 89
pid = 60930, glob = 7, var = 89
pid = 60930, glob = 7, var = 89
pid = 60930, glob = 7, var = 89
pid = 60930, glob = 7, var = 89
before fork
pid = 60924, glob = 6, var = 88
pid = 60924, glob = 6, var = 88
pid = 60924, glob = 6, var = 88
pid = 60924, glob = 6, var = 88
pid = 60924, glob = 6, var = 88
```

分析结果是一样的。

### apue -> 08.3

APUE 8.3 介绍的很清楚，可以多看几遍。

### man fork

FORK(2)                     BSD System Calls Manual                    FORK(2)

NAME
     fork -- create a new process

SYNOPSIS
     #include <unistd.h>

     pid_t
     fork(void);

DESCRIPTION
     fork() causes creation of a new process.  The new process (child process) is an exact copy of the
     calling process (parent process) except for the following:

           o   The child process has a unique process ID.

           o   The child process has a different parent process ID (i.e., the process ID of the parent
               process).

           o   The child process has its own copy of the parent's descriptors.  These descriptors reference
               the same underlying objects, so that, for instance, file pointers in file objects are shared
               between the child and the parent, so that an lseek(2) on a descriptor in the child process
               can affect a subsequent read or write by the parent.  This descriptor copying is also used
               by the shell to establish standard input and output for newly created processes as well as
               to set up pipes.

           o   The child processes resource utilizations are set to 0; see setrlimit(2).

RETURN VALUES
     Upon successful completion, fork() returns a value of 0 to the child process and returns the process
     ID of the child process to the parent process.  Otherwise, a value of -1 is returned to the parent
     process, no child process is created, and the global variable errno is set to indicate the error.

LEGACY SYNPOSIS
    #include <sys/types.h>
    #include <unistd.h>
