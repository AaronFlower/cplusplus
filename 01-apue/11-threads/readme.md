## pthread

1. 有关 pthread 的函数，在编译时需要加上 `-pthread` 选项。

### 11.2-pthread-ids

可以看出 `pthread_self()` 返回的 pthread_id 是入口地址。

```
$ ./11.2-pthread-ids
main thread: pid 700 tid 140563722151744 (0x7fd78aba2740)
new thread:  pid 700 tid 140563713771264 (0x7fd78a3a4700)
```

### 11.2-pthread-exit-terminate-process

`11.2-pthread-exit-terminate-process` 在线程中直接调用了 `exit, _Exit, _exit` 会终止所在的进程。 

```
$ ./11.2-pthread-exit-terminate-process
new thread:  pid 1114 tid 140558249920256 (0x7fd6448e8700)
$ ./11.2-pthread-ids
main thread: pid 1123 tid 140649059047232 (0x7feb6933d740)
new thread:  pid 1123 tid 140649050666752 (0x7feb68b3f700)
```



### x01-pthread_create-man

在 Unix 标准中，默认创建线程分配的 stack 大小是 8M. 我们通过 `pthread_attr_t` 来修改 stack 的大小。

可以看到一个线程的大小 (0x7fb9c1ffeee8 - 0x7fb9c1efdee8)/1024 = 1028, 1028/1024 = 1 , 余数为 4 。即 1MB + 4K 
```c
➜  11-threads git:(master) ✗ ./x01-pthread_create-man -s 0x100000 hello world kid
Thread 1: top of stack near 0x7fb9c27fbee8; arg = hello
Thread 3: top of stack near 0x7fb9c1efdee8; arg = kid
Thread 2: top of stack near 0x7fb9c1ffeee8; arg = world
Joined with thread 1; returned value was HELLO
Joined with thread 2; returned value was WORLD
Joined with thread 3; returned value was KID
```

((0x7f850705eee8 - 0x7f850685dee8)/1024 - 4)/1024 = 8, 即默认是  8MB + 4KB

```c
$./x01-pthread_create-man  hello world kid
Thread 2: top of stack near 0x7f850685dee8; arg = world
Thread 1: top of stack near 0x7f850705eee8; arg = hello
Joined with thread 1; returned value was HELLO
Joined with thread 2; returned value was WORLD
Thread 3: top of stack near 0x7f850605cee8; arg = kid
Joined with thread 3; returned value was KID
```

