## fork

当父进程 fork() 出一个子进程开始执行的时候，子进程就获得了一份父进程数据的拷贝（注意是拷贝，与父进程的数据是相互独立的）。

你进程需要 wait/waitpid 子进程退出的信号，防止子进程变成 zombie 进程。如是不进程 wait/waitpid 也可以，但要在父进程中设置 ignore SIGCHLD 信号。即下面的形式。

```
main () {
    signal(SIGCHLD, SIG_IGN);   // now i don't have to wait()

    fork();fork();fork();
}
```

## Signals

进程可以捕获信号然后调用对应的 handler 来处理。一个进程也可以抛出一个信号让另一个进程来捕获进行处理。

对于有些进程收到信号后，可以设置 SA_RESTART 重启系统调用。

注意：
1. 在 handler 中我们应该使用线程安全的函数(async safe)，如输出用 write 而不用 printf。
2. 在 handler 中你不能改变任何全局变量。但是声明为 `volatile sig_atomic_t` 类型的全局变量是可以的。
3. 关于 ANSI-C 的 `signal()` 函数是不可靠的，所以最好还是用 `sigaction()` 函数。

一常用的信号:

- SIGABRT       Process abort signal
- SIGALRM       Alarm clock.
- SIGINT        Terminal interrup signal
- SIGKILL       Kill(cannot be caught or ignored)
- SIGQUIT       Terminal quit signal
- SIGUSR1       User-define signal 1
- SIGUSR2       User-define signal 2
- SIGCHLD       Child process terminated or stopped.

## 4. Pipes

没有比 Pipes 更简单的 IPC 了。`pipe(fds)` 会创建两个 fd, 第一个用于读，第二用于写。

There is no form of IPC that is simpler than pipes. `pipe()` takes an array of two ints as an argument. Assuming no errors, it connects two file descriptors and returns them in the array. The first element of the array is the reading-end of the pipe, the second is the writing end.

pipe() 分配的两个 fd ，我在 fork() 出的子进程中应该关闭其一个不需要的 fd, 而在父进程中也应该关闭另外一个。虽然子进程和父进程都拷贝一份，共有两份。系统对同时能打开的 fd 是有上限的，所以不用的 fd 我们还是关掉吧。

- `dup(fd)` 函数会根据 fd 克隆出一个 fd, 其 clone 出来的是第一个可用的描述符（即最小的描述符）

## 5. FIFO

FIFO ("First IN, First Out", pronounced "Fy-Foh") , 也被称之为命名管道 named pipe. 其解决的问题是 pipe 只能用在同一个程序中的进程中，如果多个程序中的进程相互怎么实现通信那？那么使用 FIFO 就可以解决这个问题。

With FIFOs, though, each unrelated process can simply open() the pipe and transfer data through it.

###  A New FIFO is Born

FIFO 其是磁盘上的一个文件，我们需要用 `mknod` 系统调用来创建它。` man mknod` -- make device special file.

```
mknod("myfifo", S_IFIFO | 0644, 0);
```
- 第一个参数是创建特殊文件的名称
- 第二个参数是告诉创建的特殊文件的类型，这里我们创建的是 FIFO, 及创建该文件的权限
- 第三个参数是设备号，在创建 FIFO 文件时可以忽略。

FIFO 文件也可通过 Linux 命令 `mknod` 来创建。


## 6. File Locking

通过简单对文件加锁也是一种很高效的通信机制。关于锁有两种机制：强制型和咨询型 (mandatory and advisory)。在这里我们只讨论 advisory 锁，它双分为：读锁(read locks) 和 写锁 (write locks) 也称为 shared locks, exclusive locks)。

对文件进行加锁可以用 `flock()` 和 `fcntl()` 函数。

### 6.1 Setting a lock

`fcntl()` 函数是一个万能工具函数，可以对文件做一切操作。对文件加锁需要用 `struct flock` 结构体，一般的 code snipet 如下：

```
struct flock fl;
int fd;

fl.l_type   = F_WRLCK;  /* F_RDLCK, F_WRLCK, F_UNLCK    */
fl.l_whence = SEEK_SET; /* SEEK_SET, SEEK_CUR, SEEK_END */
fl.l_start  = 0;        /* Offset from l_whence         */
fl.l_len    = 0;        /* length, 0 = to EOF           */
fl.l_pid    = getpid(); /* our PID                      */

fd = open("filename", O_WRONLY);

fcntl(fd, F_SETLKW, &fl);  /* F_GETLK, F_SETLK, F_SETLKW */
```

### 6.2 Clearing a lock

加锁后，在完成工作后，我需要对文件锁进行清除。一般的 code snippet 如下：

```
fl.l_type = F_UNLCK;        // tell it to unlock the region
fcntl(fd, F_SETLK, &fl);    // set the region to unlocked
```
