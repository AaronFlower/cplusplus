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

###  11.3-thread-exit

```c
./11.3-thread-exit
[+] thread 1: returning
[+] thread 2: returning
[+] thread1: exit code 1
[+] thread2: exit code 2
```

### 11.4-thread-stack-memory

```c
# centos
$ ./11.4-thread-stack-memory

f->a: 1
f->b: 2
f->c: 3
f->d: 4
f->a: -405813504
f->b: 32519
f->c: -397384104
f->d: 32519

```

```c
# Mac
$ ./11.4-thread-stack-memory
f->a: 1
f->b: 2
f->c: 3
f->d: 4
[1]    54344 segmentation fault  ./11.4-thread-stack-memory
```

### 11.5 x01-pthread_create-man

`pthread_cleanup_push, pthread_cleanup_pop` 各系统的实现不定的执行结果 undefined.

```
# mac
./11.5-pthread-cleanup
[+] thread 1: start
[+] thread 2: start
[+] thread 1: push complete
[+] cleanup: thread 1 second handler
[+] thread 2: push complete
[+] cleanup: thread 2 second handler
[1]    61102 segmentation fault  ./11.5-pthread-cleanup

# centos

./11.5-pthread-cleanup
[+] thread 1: start
[+] thread 1: push complete
[+] thread 2: start
[+] thread 2: push complete
[+] thread 1 exit code 1
[+] thread 2 exit code 2

```

### 11.13-pthread-mutex-timedlock

```
$ ./11.13-pthread-mutex-timedlock
[+] mutex is locked
[+] current time is 03:16:10 AM
[+] the time is now 03:16:20 AM
[-] Error lock mutex again: Success
```

### x02-pthread-condition-variable

```c
$ ./x02-pthread-condition-variable
[+] thread main starting
                [+] Thread 0 working (0/2)
                [+] Thread 1 working (0/2)
                [+] Thread 2 working (0/2)
                [+] Thread 3 working (0/2)
[+] thread main : done is 0 which is < 5 so waiting on cond
                [+] Thread 4 working (0/2)
                [+] Thread 3 working (1/2)
                [+] Thread 1 working (1/2)
                [+] Thread 0 working (1/2)
                [+] Thread 2 working (1/2)
                [+] Thread 4 working (1/2)
                [+] Thread 3 done is now 1. Signalling cond.
                [+] Thread 1 done is now 2. Signalling cond.
        [+] thread main: wake - cond was signalled.
[+] thread main : done is 2 which is < 5 so waiting on cond
                [+] Thread 2 done is now 3. Signalling cond.
                [+] Thread 4 done is now 4. Signalling cond.
                [+] Thread 0 done is now 5. Signalling cond.
        [+] thread main: wake - cond was signalled.

[+] thread main: done == 5 so everyone is done
```

#### 11.16-pthread-barrier-sort 

```
# 使用 8 个线程
$ ./11.16-pthread-barrier-sort >sort-8-threads.txt
$ head sort-8-threads.txt
sort took 0.6570 seconds
37
614
858
880
1210
2126
2172
2218
2333

# 使用 1 个线程
$ ./11.16-pthread-barrier-sort >sort-1-threads.txt
$ head sort-1-threads.txt
sort took 2.2588 seconds
37
614
858
880
1210
2126
2172
2218
2333
```
