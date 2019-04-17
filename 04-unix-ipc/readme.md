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
