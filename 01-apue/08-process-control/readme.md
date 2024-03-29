## fork

`fork()` create a new process. 调用一次，返回两次。创建的子进程和父进程共享资源，有些资源是完全 copy 一份的 (描述符文件引用共享，堆栈资源共享，但其上的变量会复制一份）。所以 `8.1` 例子真的非常经典，在 console 中执行和重定向执行时共享标准输出，变量。

在网络编程时，父进程的 socket 也会被共享，我们可以在子进程关闭它。

fork() causes creation of a new process. The new process (child process) is an exact copy of the calling process (parent process) except for the following:
    - The child process has a unique process ID.
    - The child process has a different parent process ID.
    - The child process has its own copy of the parent's descriptors.  These descriptors reference the same underlying objects, so that, for instance, file pointers in file objects are shared between the child and the parent, so that an lseek(2) on a descriptor in the child process can affect a subsequent read or write by the parent.  This descriptor copying is also used by the shell to establish standard input and output for newly created processes as well as to set up pipes.

### 例子1：`8-1.fork-1.c`

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

### 例子2：`8-1.fork-2.c`

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

### 例子 8-6.exit-status.c

```
# 运行结果

❯ ./8.6-exit-status
normal termination, exit status = 7
abnormal termination, signal number = 6
abnormal termination, signal number = 8

```

每 fork 一个子进程都用一个 wait 函数来等待它。这样就可以获得每个子进程退出的状态。如果我们在第一个子进程中的 exit(7); 注释掉，我们可以看到其 wait 就会报错，而之后的代码还是会执行，最终是在 return 0 中执行。

```
# 注释掉 exit(7);
❯ ./8.6-exit-status
wait error
abnormal termination, signal number = 126(core file generated)
abnormal termination, signal number = 6
abnormal termination, signal number = 8
normal termination, exit status = 0
abnormal termination, signal number = 6
abnormal termination, signal number = 8

```

### apue -> 08.3

APUE 8.3 介绍的很清楚，可以多看几遍。

### apue -> 08.5 : exit Functions

一个进程正常终止的方式有 5 种：

- 在 main 函数中执行 return , 这和 exit 等价。
- 调用 exit 函数，在 `stdlib.h` 头文件中定义, 该函数会调用各终止处理程序(在 aexit() 函数中注册的)，关闭所有标准 IO 流等。
- 调用 `_exit()` 系统调用, 与 exit 不同，该方式提供一种无需运行终止处理程序或信号处理程序的方式。
- 进程的最后一个线程在其启动的例程中执行 return 语句。但是该线程的返回值不用作进程的返回值，当最后一个线程从其启动例程返回时，该进程以终止状态 0 返回。
- 进程的最后一个线程调用 `pthread_exit` 函数。如同前面的一样，在这种情况下中，进程终止状态总是 0.

非正常终止的 3 种方式：

- 调用 abort 函数
- 接收一某种信号。
- 最后一个线程执行了 cancellation 请求。

无论进程以那种方式终止，我们都希望能够通知其父进程子进程是以何种方式终止的。父进程可以通过 `wait, waitpid` 函数来获取进程的终止状态。

在 Unix 系统中，如果一个进程已经结束了，但是其父进程并没有接收其终止状态信号，那么该里程虽然已经结束，但是也变成了僵尸 Zombie 进程，内核还是会为该僵死进程保留一部分信息如：进程 ID, 进程终止状态，执行时长等。所以我们最好还是要处理下进程的终止状态，防止僵死进程的出现 。

使用 `ps` 命令，进程状态展示为 `Z` 的进程就是僵死进程。

### apue -> 08.6 `wait, waitpid` 函数

当一个进程终止时（无论是正常还异常终止），内核都会发关一个 SIGCHLD 信号通知其父进程。因为子进程的终止是一个异步事件，它可以在父进程运行的任何时候执行，信号是异步通知给父进程的。父进程默认是忽略这些信号的，现在我们需要用 wait, waitpid 函数来处理这些信号：


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
