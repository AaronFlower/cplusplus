## `close-on-exec`

每一个 fd 上都一个 flags, file descriptor flags. 其实目前仅有一个标记 `FD_CLOEXEC`.  这个标记与 fd status flags 是不同的， fd status flags 是控制读写的标记。

- `FD_CLOEXEC` : 是在 fork 的子进程中，如果使用 exec 函数执行另一个程序，那么这个标记就是用来控制执行的程序是否还能继续访问从父进程继承的 fd .

### fd 设置 `close-on-exec` 的方法

1. 使用 `fcntl` 函数设置

```c
// #include <fcntl.h>

int val = fcntl(fd, F_GETFD);

if (fcntl(fd, F_SETFD, val | FD_CLOEXEC) < 0) {
    perror("[-] Error fcntl");
    exit(1);
}

```

2. 使用 `open` 系统调用时指定 ()

```c
// #include <fcntl.h>

int fd;
if ((fd = open("marks.txt", O_RDONLY | O_CLOEXE)) < 0) {
    perror("[-] Error open");
    exit(1);
}
```

### demo 执行结果

- 默认是没有 `close-on-exec` FLAG 的

```
$ ./x01-close-on-exec-off
Turn close-on-exec flag OFF
[+] Child(36149): fd is 3
[+] Child(36149): read ###
  [+] Exec(36149): I was executed by execl, fd = 3
  [+] Exec(36149): fd is 3
  [+] Exec(36149): ***
[+] Parent(36144): fd is 3
[+] Parent(36144): read  $$$
[+] Parent(36144): close fd
$ ./x01-close-on-exec-off
```

- 开启 `close-on-exec` FLAG 后

```
$ ./x01-close-on-exec-on
Turn close-on-exec flag ON
[+] Child(37450): fd is 3
[+] Child(37450): read ###
  [+] Exec(37450): I was executed by execl, fd = 3
  [-] Error read in exec: Bad file descriptor
[+] Parent(37446): fd is 3
[+] Parent(37446): read  ***
[+] Parent(37446): close fd
```

可以看到父子进程是共享 fd (offset, status), 在各进程中关闭 fd 只是关闭一个引用而已，并不会影响其它进程的 fd. 虽然可以看到父子进程输出的 fd 值都是 `3`.
