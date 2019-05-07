## A tiny introduction to asynchronous IO

### `./01-http-client-blocked.c`

在这个例子中 `gethostbyname` 是被阻塞的，另外 `connect, recv, send` 都是阻塞的。

有时间使用多线程可以解决等待的问题。

### `./02-rot13-server.c`

ROT13（回转13位，rotate by 13 places，有时中间加了个连字符称作ROT-13）是一种简易的替换式密码。它是一种在英文网络论坛用作隐藏八卦（spoiler）、妙句、谜题解答以及某些脏话的工具，目的是逃过版主或管理员的匆匆一瞥。ROT13被描述成“杂志字谜上下颠倒解答的Usenet点对点体”。ROT13 也是过去在古罗马开发的凯撒加密的一种变体。

该服务器使用多进程 (`fork()`) 返回 ROT13 加密后的文本。

### How To Use

- 编译启动服务器

```
$ make
$ ./02-rot13-server
```

- 启动多个客户端来访问服务器

```
$ nc localhost 8082
$ nc localhost 8082
$ nc localhost 8082
```
客户端如果主动断开，那么服务器中从父进程 `fork()` 出来的子进程可能就成为了 Zombie 进程。我们要捕获下 `SIGCHLD` 信号，或者用 `wait/waitpid` 来处理。