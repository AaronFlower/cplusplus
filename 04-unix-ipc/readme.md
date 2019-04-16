## fork

当父进程 fork() 出一个子进程开始执行的时候，子进程就获得了一份父进程数据的拷贝（注意是拷贝，与父进程的数据是相互独立的）。

你进程需要 wait/waitpid 子进程退出的信号，防止子进程变成 zombie 进程。如是不进程 wait/waitpid 也可以，但要在父进程中设置 ignore SIGCHLD 信号。即下面的形式。

```
main () {
    signal(SIGCHLD, SIG_IGN);   // now i don't have to wait()

    fork();fork();fork();
}
```
