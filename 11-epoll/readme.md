## epoll

APUE 没有详细介绍 `epoll`, 这是补充资料，多看 man 就 OK .

### 1. `man epoll`

#### 1.1 Name

epoll - I/O event notification facility. 

#### 1.2 SYNOPSIS

```c
#include <sys/epoll.h>
```

#### 1.3 描述

epoll API 与 poll 类似：用于监测多个 fd 是否可用。epoll 的算法复杂度 O(1), 有两种触发模式，edge-triggerd 和 level-triggered. (这两个触发概念是借鉴于[电路的锁存器的概念](https://www.quora.com/What-is-the-difference-between-level-and-edge-triggered-flip-flops/answer/Rishabh-Gupta-207)) 。我们可以用下面的系统调用来创建管理我们的 epoll 实例：

- `epoll_create(), epoll_create1()` 创建一个 epoll 实例，并且返回一个 fd 来引用该实例。`epoll_create1` 对 `epoll_create`做了功能扩充。
- `epoll_ctl` 用于注册我们感兴趣的 fd。epoll 实例上的所有注册 fd 称为 epoll set.
- `epoll_wait()` 等待 IO 事件，没有事件发生时将会阻塞。

##### level-triggered 与 edge-triggered

epoll 对事件的分发有两种模式，ET(edge-triggered) , LT(level-triggered)。两种机制的差别如下，假设有以下场景：

```c
int fds[2], rfd;
pipe(fds);
rfd = fds[0];
wfd = fds[1];
```

1. 我创建一个管道，返回两个 fds
2. `rfd`  被注册到了 epoll 实例上。
3. 程序管道上写 2KB 的数据
4. 此时 `epoll_wait()` 将返回, 因为 rfd ready.
5. 从 rfd 中读取了 1KB
6. `epoll_wait()` 调用完成

如果 `rfd` 注册是用的 `EPOLLET`(edge-triggered) 标记，在第 5 步的时候，虽然我们只读走了 1 KB, 到第 6 步时 epoll_wait() 还是 done, 即使 rfd 中还有 1KB 的数据。ET 只会在监测的 fd 改变时触发，所以上面的场景，在写 2KB 时触发(第3步)，在第4步时触发的时间被消费了 (the event is comsumed in 4). 但是，因为，第4步在消费 event 的时候并不取走所有数据，epoll_wait() 可能会一直等待。

EPOLLET 的应用场景一般是，1）使用 nonblocking fd 来避免 blocking read, 2) 编写一个 write 任务处理多个 fds 。epoll 使用 ET 的建议如下：

- 使用 nonblocking fd (waiting nonblocking fd; and)
- 如果在 read, write 后，还等待，则返回 EAGAIN. ( by waiting for an event only after read, write return EAGAIN)

相于 ET 的，LT 是默认的标记会触发多次。

##### 使用建议

当使用 `LT` 时，其实现的功能和 poll 类似; 而 `ET` 在使用时需要清理工作以避免在事件循环中停顿 (requires clarification to avoid stalls in the application event loop)。

`man epoll`有具体的例子。

在使用 `ET` 时，为了性能的考虑，通过指定 EPOLLIN | EPOLLOUT 来提高性能。避免在 EPOLLIN, EPOLLOUT 之间切换。

- LT 即支持同步也支持异步；
- ET 只能应用于设置了 `O_NONBLOCK` 的 fd
- ET 效率比 LT 高，但 LT 更加易用，不容易出错。

#### Q&A

1. epoll set 中用什么 key 来区分注册的 fd？

   Key 是 fd number 与 open file description 的组合。

2. 如果一个 fd 注册两次会出现什么情况？

   可能会得到 `EEXIST` 。但是通过 `dup, dup2, fcntl` duplicated 的 fd 是可注册的。

3. 一个 fd 可以被两个 epoll 实例监测吗？

   可以！如被注册到多个实例，当 ready 时将会触发多次。应该避免这种情况出现。

4. epoll 返回的 fd 可以用在 poll/epoll 中吗？

   可以！用来监测 fd readable 进触发。

5. 返回的 fd 的 epoll 实例同是注册该 fd ，会出现什么情况？

   `epoll_ctl` 将会出错(EINVAL). 你可以将返回的 fd 注册到其它 epoll 实例中，但不是要自身的实例中。

6. 可以通过 Unix 域将 epoll 实例的 fd 传给其它进程吗？

   可以，但是没有意义。因为接收进程不会复制 epoll set.

7. 关闭注册后 fd 后，会从 epoll set 删除吗？

   是的会删除。但是，应该注意，一个 fd 只是对 file table entry 中的一个引用，在使用 dup, dup2, fcntl duplicated 的 fd 是指向同一个引用的。只有关闭掉所有引用，file table entry 才会被关闭。所以, 只有引用上所有的 fd 都被关闭， epoll set 中才会移除该 fd。所以 duplicated 的 fd 要注意。

8. 如果在 epoll_wait 时，发生了多个事件，它们会分别触发吗？

   不会分别触发，而是会被组合(combined)。

9. fd  ready了，但是事件还没上报，此时又发生了的操作，会影响已经收集到的还没上报的事件吗？(Does an operation on a file descriptor affect the already collected but not yet reported events?)

   You  can  do  two operations on an existing file descriptor.  Remove would be meaningless for this case。 Modify will reread available I/O.(解释不太理解)

10. 当使用 `ET` 后，我需要持续 `read/write` fd 直到 EAGAIN 吗？

    分情况的。

    Receiving  an  event from epoll_wait(2) should suggest to you that such file descriptor is ready for the
    requested I/O operation.  You must consider it ready until  the  next  (nonblocking)  read/write  yields
    EAGAIN.  When and how you will use the file descriptor is entirely up to you.

    For  packet/token-oriented  files  (e.g.,  datagram socket, terminal in canonical mode), the only way to
    detect the end of the read/write I/O space is to continue to read/write until EAGAIN.

    For stream-oriented files (e.g., pipe, FIFO, stream socket), the condition that the read/write I/O space
    is  exhausted can also be detected by checking the amount of data read from / written to the target file
    descriptor.  For example, if you call read(2) by asking to read a certain amount  of  data  and  read(2)
    returns  a  lower  number  of bytes, you can be sure of having exhausted the read I/O space for the file
    descriptor.  The same is true when writing using write(2).  (Avoid this latter technique if  you  cannot
    guarantee that the monitored file descriptor always refers to a stream-oriented file.)

#### 避免可能的陷阱

- 饥饿，starvation(ET)

  当有一个很大 IO 空间出现时，为了完成这一个的处理，可能不会处理其它 fd. 这就导致饥饿出现。这不是 epoll 所特有的，其它 poll/select 也会出现。

  解决方法是维护一个 ready list, 标记对应的 fd 为 ready，允许应用程序处理其它  fd.

- 使用用 event cache 的陷阱

  如果你用 cache 缓存 epoll_wait 返回的 fd, 要保证正确关闭。假设收到了 100 个 events, 在 $47 号中我们关闭了 #13 号 event, 但是缓存可能还是在等待 #13.

  解决方法是，直接用 `epoll_ctl` 删除 13 号。 

### 2. 相关数据结构

```c
typedef union epoll_data {
	void *ptr;
	int fd;
	uint32_t u32;
	uint64_t u64;
} epoll_data_t; // 注意一个 union 联合结构体。

struct epoll_event {
  uint32_t events; 		// Epoll events
  epoll_data_t data; 	// user data variable
};
```

#### 3. 相关函数

#### 3.1 `epoll_create`

`man epoll_create`,  `epoll_create(), epoll_create1()` - 打开一个 epoll fd.

```c
#include <sys/epoll.h>

int epoll_create(int size);
int epoll_create1(int flags);

// Returns: fd, or -1 on error.
```

`epoll_create()` 创建一个 epoll 实例。`size` 传一个大于 0 的数就行了，返回从 Linux 2.6.8 之后，该参数是被 ignored。

`epoll_create1()`  当 `flags` 参数为 0 时，与 `epoll_create()` 创建的相同。`flags` 可以为 `EPOLL_CLOEXEC`, 会将返回的 fd flag 设置为 `close-on-exec` . (`man open ` 查看与 `close-on-set` 的信息，在多线程中很重要)。

Note: `epoll_create(size)` 中的 `size` 参数起初是为了在创建 epoll 实例时，指定 epoll 实例最多可添加多少 fd, 然后根据 size 分配空间。现在是动态分配的了，所以不用传。但是为了兼容，还是传个大于 0 的数。

#### 3.2  `epoll_ctl` 

`man epoll_ctl` 用来操作 epoll 实例，注册 fd .

```c
#include <sys/epoll.h>

int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);

// Returns: 0 on success, or -1 on error.
```

- `epfd` 是 `epoll_create1()` 返回的 fd

- `op` 的可选值如下：

  ```c
   /* Valid opcodes ( "op" parameter ) to issue to epoll_ctl().  */
   #define EPOLL_CTL_ADD 1 /* Add a file descriptor to the interface.  */
   #define EPOLL_CTL_DEL 2 /* Remove a file descriptor from the interface.  */
   #define EPOLL_CTL_MOD 3 /* Change file descriptor epoll_event structure.  */
  ```

- `event` 参数是一个结构体

  ```c
  typedef union epoll_data {
       void        *ptr;
       int          fd;
       uint32_t     u32;
       uint64_t     u64;
   } epoll_data_t; // 注意是一个 union 结构体
  
   struct epoll_event {
       uint32_t     events;      /* Epoll events */
       epoll_data_t data;        /* User data variable */
   };
  ```

  `events` 的取值定义如下：

  ```c
    enum EPOLL_EVENTS
      {
        EPOLLIN = 0x001, 		// ready for read
    #define EPOLLIN EPOLLIN
        EPOLLPRI = 0x002, 	// ready for read(There is urgent data available for read)
    #define EPOLLPRI EPOLLPRI
        EPOLLOUT = 0x004, 	// ready for write
    #define EPOLLOUT EPOLLOUT
        EPOLLERR = 0x008,  	// error on one fd
    #define EPOLLERR EPOLLERR
        EPOLLHUP = 0x010, 	// hang up on one fd
    #define EPOLLHUP EPOLLHUP
        EPOLLONESHOT = 1u << 30,
    #define EPOLLONESHOT EPOLLONESHOT
        EPOLLET = 1u << 31 		// 设置 ET 触发，默认是 LT 触发的。
    #define EPOLLET EPOLLET
      };
  ```

#### 3.3 `epoll_wait()`

```c
 #include <sys/epoll.h>

 int epoll_wait(int epfd, struct epoll_event *events,
                int maxevents, int timeout);
 int epoll_pwait(int epfd, struct epoll_event *events,
                int maxevents, int timeout,
                const sigset_t *sigmask);
// Returns: number of ready fds; 0 on timesout; -1 on error.
```

- `epfd` 参数是 `epoll_create1()` 返回的实例 fd。
- `events`是指定接收 events 的内存地址指针。
- `maxevents` 最大能返回的 events 数, 必须大于 0.
- `timeout` 指定 epoll_wait() 等待阻塞的时间(单位为 milliseconds). 
  - 为 -1 时会一直等待，
  - 为 0 进直接返回，没有事件可用。

返回的 `events` 与 `epoll_ctl()`设置时的数据结构是一样的。

`epoll_pwait()` 的 p 是 POSIX 的标准，与 `select/pselect` 的关系类似。

#### References

1. [man epoll]([http://man7.org/linux/man-pages/man7/epoll.7.html](http://man7.org/linux/man-pages/man7/epoll.7.html))
2. [Level-triggered and edge-triggered](https://www.quora.com/What-are-the-key-differences-between-edge-triggered-and-level-triggered-interrupts) 