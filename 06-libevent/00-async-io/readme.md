## A tiny introduction to asynchronous IO

### 1. Ex1: `./01-http-client-blocked.c`

在这个例子中 `gethostbyname` 是被阻塞的，另外 `connect, recv, send` 都是阻塞的。

有时间使用多线程可以解决等待的问题。

#### 1.1 How To Use

```
$ make
$ ./01-http-client-blocked

HTTP/1.1 200 OK
X-Powered-By: Express
Accept-Ranges: bytes
Content-Type: text/html; charset=UTF-8
Content-Length: 974
ETag: W/"3ce-FAzxitjxgv/83MoA6e7tHm+AU4U"
Date: Sun, 05 May 2019 03:42:59 GMT
Connection: close

<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width,initial-scale=1.0">
    <link rel="icon" href="/favicon.ico">
  <link href="/0.js" rel="prefetch"><link href="/1.js" rel="prefetch"><link href="/2.js" rel="prefetch"><link href="/3.js" rel="prefetch"><link href="/4.js" rel="prefetch"><link href="/5.js" rel="prefetch"><link href="/6.js" rel="prefetch"><link href="/7.js" rel="prefetch"><link href="/8.js" rel="prefetch"><link href="/9.js" rel="prefetch"><link href="/app.js" rel="preload" as="script"></head>
  <body>
    <div id="app"></div>
    <!-- built files will be auto injected -->
  <script type="text/javascript" src="/app.js"></script></body>
</html>
```

### 2. Ex2: `./02-rot13-server.c`

ROT13（回转13位，rotate by 13 places，有时中间加了个连字符称作ROT-13）是一种简易的替换式密码。它是一种在英文网络论坛用作隐藏八卦（spoiler）、妙句、谜题解答以及某些脏话的工具，目的是逃过版主或管理员的匆匆一瞥。ROT13被描述成“杂志字谜上下颠倒解答的Usenet点对点体”。ROT13 也是过去在古罗马开发的凯撒加密的一种变体。

该服务器使用多进程 (`fork()`) 返回 ROT13 加密后的文本。

#### 2.1 How To Use

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

通过 fork 我们的服务器就可以处理多链接了？ 可以高枕无忧了？ 现实并不是这样的。首先 process/thread 的创建是非常昂贵的。在实际应用中，你应该使用线程池而不是通过 fork 新的进程来处理连接。但是即使是 threads 也太好扩展，如果你的服务器同一时间处理上百万个连接，那么在一个 CPU 上同时只有若干个线程被调度的话效率也不会太高的。

如果线程线程解决不了该问题, 那用什么方法可以解决那？ Unix 的世界里，你可以使用 `noblocking` 策略。

即在典型的 socket API 中，一个 non-blocking socket 是指 socket 直接返回，无论 socket 是否被 blocked，然后再用 `select/ poll` 函数去轮询。

> For example in the classic sockets API, a non-blocking socket is one that simply returns immediately with a special "would block" error message, whereas a blocking socket would have blocked. You have to use a separate function such as select or poll to find out when is a good time to retry.

> Non-blocking often refers to polling, i.e. checking whether given condition holds (socket is readable, device has more data, etc.)

参考 [asynchronous vs non-blocking](https://stackoverflow.com/questions/2625493/asynchronous-vs-non-blocking)

使用 `fcntl` 函数，可以将我们的 file descriptor 设置成 non-blocking 的。

```c
fcntl(fd, F_SETFL, O_NONBLOCK)
```

- `fd` 是 socket 的文件描述符。

当我们的 socket 被设置成 non-blocking 后，之后所有在该 fd 上的请求要么会立即完成, 要么会返回一个错误以表示『现在不能处理，请重试』

下面是一个 `busy-polling` 的例子.

```c
/* This will work, but the performance will be unforgivably bad. */
int i, n;
char buf[1024];
for (i=0; i < n_sockets; ++i)
    fcntl(fd[i], F_SETFL, O_NONBLOCK);

while (i_still_want_to_read()) {
    for (i=0; i < n_sockets; ++i) {
        n = recv(fd[i], buf, sizeof(buf), 0);
        if (n == 0) {
            handle_close(fd[i]);
        } else if (n < 0) {
            if (errno == EAGAIN)
                 ; /* The kernel didn't have any data for us to read. */
            else
                 handle_error(fd[i], errno);
         } else {
            handle_input(fd[i], buf, n);
         }
    }
}
```

上面的代码我们使用 non-blocking sockets ，生产环境中的代码不会是这样的，虽然不太可以 work, 但是上面的代码模式性能却是惊人的，有两个原因。

1. 当连接上没有数据可读的时候，上面的死循环会点满你的 CPU cycles.
2. 你需要使用 kernel call 来处理数据。

所以我们需要有一种方法告诉 kernel 上面循环中的 sockets 中有一个 socket 已经 OK 了，可以处理了。最古老的方法就是用 `select()` 来处理了，`select()` 需要会话三个 fds set: 一个用于就读，一个用于写，另一个用于『异常』处理。该函数等待其中一个 set 的某个 scoket 准备完成。

```c
/* Check the first NFDS descriptors each in READFDS (if not NULL) for read
 readiness, in WRITEFDS (if not NULL) for write readiness, and in EXCEPTFDS
 (if not NULL) for exceptional conditions.  If TIMEOUT is not NULL, time out
 after waiting the interval specified therein.  Returns the number of ready
 descriptors, or -1 for errors.

 This function is a cancellation point and therefore not marked with
 __THROW.  */
extern int select (int __nfds, fd_set *__restrict __readfds,
             fd_set *__restrict __writefds,
             fd_set *__restrict __exceptfds,
             struct timeval *__restrict __timeout);

/* Access macros for `fd_set'.  */
#define FD_SET(fd, fdsetp)  __FD_SET (fd, fdsetp)
#define FD_CLR(fd, fdsetp)  __FD_CLR (fd, fdsetp)
#define FD_ISSET(fd, fdsetp)    __FD_ISSET (fd, fdsetp)
#define FD_ZERO(fdsetp)     __FD_ZERO (fdsetp)

```

下面是使用 `select` 的代码：

```c
/* If you only have a couple dozen fds, this version won't be awful */
fd_set readset;
int i, n;
char buf[1024];

while (i_still_want_to_read()) {
    int maxfd = -1;
    FD_ZERO(&readset);

    /* Add all of the interesting fds to readset */
    for (i=0; i < n_sockets; ++i) {
         if (fd[i]>maxfd) maxfd = fd[i];
         FD_SET(fd[i], &readset);
    }

    /* Wait until one or more fds are ready to read */
    select(maxfd+1, &readset, NULL, NULL, NULL);

    /* Process all of the fds that are still set in readset */
    for (i=0; i < n_sockets; ++i) {
        if (FD_ISSET(fd[i], &readset)) {
            n = recv(fd[i], buf, sizeof(buf), 0);
            if (n == 0) {
                handle_close(fd[i]);
            } else if (n < 0) {
                if (errno == EAGAIN)
                     ; /* The kernel didn't have any data for us to read. */
                else
                     handle_error(fd[i], errno);
             } else {
                handle_input(fd[i], buf, n);
             }
        }
    }
}
```

### Ex3. `./03-rot13-select-server.c`

该服务器使用 `select()` 来完成响应。因为生成和读取 `select()` 中的 bit arrays 的耗时与最大的 fd 成正比，当 fd 变大时，`select()` 的性能会变很差。【另外，在用户侧看来读取时间与 fd 下正比，而在内核侧实现时却与正个程序使用的 fd 大小成正比，与用户提供的 fd 参数无关。】

不同的操作提供了不同的 `select()` 替换方案，如：`poll(), epoll(), kqueue(), evports, /dev/poll` 等。这些方案都比 `select()` 的性能要高很多。最优的是 `poll()` 在 adding socket, removing socket, noticing 时的时间复杂度是 O(1)。不幸的是，没一个成为了惟一的标准，第个发行版的实现都不同，这就是为 Libevent 诞生的原因。

通过 `event_base` 结构体来完成，而无需考虑具体的底层实现是使用 `select(), poll(), epoll(), kqueue()` 还是其它。

### Ex4. `./04-rot13-libevent-server.c`
