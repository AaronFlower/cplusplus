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
