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

## 7 Message Queues

System 中的 IPC 通信方式消息队列是一个很棒的设计，好多平台都实现了这个功能，当然包含 （linux) 了。

Message Queue 的工作方式和 FIFO 类似。通常消息队列是按顺序进行处理的。一个进程可以创建新的消息队列，也可以选择去连接一个已经存在的消息队列，所以进程之前可以通过消息队列进行通信。

需要注意一点是，即使所有进程都退出，创建的消息队列还是存在的。所以可以用 `ipcs` 来检查是否还有未销毁的队列，然后可以用 `ipcrm` 来销毁该队列。

- `ipcs` : Display information about resources used in IPC (Inter-process Communication).
- `ipcrm`: remove the specified message queues, semaphore sets, and shared memory segments

### 7.1 Where's my queue?

```
int msgget(key_t key, int msgflg);
```

msgget 链接一个队列，如果队列不存在则创建它。成功的话会返回 queue ID ，出错的话返回 -1 并且会置全局 (errno).

- key 参数是一个系统的全局惟一标识，可以用于连接也可用于创建。其它进程通过这个 key 来进行连接。
- msgflg 参数用于指明操作，IPC_CREATE 说明是创建一个队列，也可与其它权限值进行 OR, 消息队列与标准文件的权限是一样的也有 user-id, group-id.

### 7.2 "Are you the key Master?"

如果你指定的 key 是无效的怎么办？可能其它进程也用到了同样的一个 key 怎么办？我们可以用 `ftok` 函数来生成一个Key.

```
#include <sys/ipc.h>
key_t ftok(const char *path, int id)
```

- ftok  -- create IPC identifier from path name

- path 参数通常是进程可以读取一个文件
- id 参数可是任意的字符，如 'A'.

ftok 函数利用文件的信息如 (inode number) 和 id 生成一个惟一的 key 供 msgget() 使用。其它进程想使用这个队列，需要使用相同的参数获取同样的 key.

常用的 code snippet:

```
#include <sys/ipc.h>

key = ftok("/home/beej/somefile", 'b');
msgid = msgget(key, 0666 | IPC_CREAT);
```

### 7.3 Sending to the queue

向队列发送信息的话，需要使用 `struct msgbuf`, 每个信息有两部分组成 ：

```
#include <sys/msg.h>

struct msgbuf {
    long mtype;
    char mtext[1];
};
```

- mtype ：任何大于 0 的数，在后面检索信息的时候会用到。
- mtext ：向队列中添加的数据 。

从上面的结构体看，我们仅能向队列上一次添加一个字符。 其实，我们可以一次向队列中添加任意结构的数据，只要我们的第一个元素是 long 类型。比如我们可自己定义下面的结构体：

```
struct pirate_msgbuf {
    long mtype;         /* must be positive */
    struct pirate_info {
        char name[30];
        char ship_type;
    } info;
};
```

定义好消息后，我们就可以用 `msgsnd()` 函数发送数据了：

```
int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
```

- msgid: msgget() 返回的 id
- msgp : 发送消息结构体的指针
- msgsz: 自定义消息的大小（不包含 mtype 成员的大小）
- msgflg: 我们可以忽略，直接设置成 0 即可

所以一完整的发送 code snippet 如下：

```
#include <sys/msg.h>
#incldue <stddef.h>

key_t key;
int msqid;
struct pirate_msgbuf pmb = {2, {"L'Olonais", 'S'}};

key = ftok("/home/somefile", 'b');
msqid = msgget(key, 0666 | IPC_CREAT);

msgsnd(msqid, &pmb, sizeof(struct pirate_info), 0);
```

### 7.4 Receiving from the queue

与 `msgsnd()` 对应的是 `msgrcv()` ， 我们可以用它进行接收信息。

```
int msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
```

我们需要关注提 `msgtyp` 参数，其取值如下：

| msgtyp | Effect|
|--------| ------|
| 0      | 从 queue 中检索下一个 message|
| Positive| 取 与 msgsnd 中的 mtype 相等的消息|
| Negative| 取队列中 mtype 绝对值小于 msgtyp 的第一个 message|

所以如果我们只是取队列中下一个消息，只需要设置 msgtyp 为 0 即可。

### 7.5 Destroying a message queue

当需要释放资源要销毁队列时，我们可以使用两种方式：
1. 使用 `ipcs` 和 `ipcrm` 命令。
2. 使用 `msgctl()` 函数。

`msgctl()` 函数定义如下：

```
int msgctl(int msqid, int cmd, struct msqid_ds *buf);
```

- msqid: msgget() 返回的 id
- cmd: 用于指明函数的具体操作，在这里我们只需要使用  IPC_RMID 删除队列即可。
- buf: 当 cmd 为 IPC_RMID 时，该参数可以传空。

所以销毁队列的 code snippet 如下：

```
#include <sys/msg.h>

msgctl(msqid, IPC_RMID, NULL);
```

## 8 Semaphores

Semaphores 信号量可以看成真正能用的加锁机制。使用 Semaphores 可以用来控制：files, shared memory 等。一个 semaphore 的三个基本操作是： set it , check it, wait until it clears then set it("test-n-set").

### 8.1 Grabbing some semaphores

在创建 semaphores 时，我们其实创建的是一个 semaphore set，其创建函数和 msgget 类似：

```
#include <sys/sem.h>
int semget(key_t key, int nsems, int semflg);
```

- key: 参考与 msgget 中的 key 参数一样，需要用 `ftok` 函数生成。
- nsems: 指定创建 semaphores set 的大小。
- semflg: 指定 semget 的行为，如：IPC_CREAT|0644

和 message queue 一样我们可以用 `ipcs, ipcrm` 命令来管理 semaphore set.

**注意**: semaphore set 创建后需要初始化，但是创建初始化不是原子操作。如果两个进程操作会出现 race condition. 解决方法用 IPC_EXCL 标记来进行排它，只有创建的进程才能有初始化的权限，其它进程只能在初始化完成后才能使用。

### 8.2 Controlling your semaphore with semctl()

当你新建了 semaphore set 后，需要将它们初始化成 positive value 后才能使用。`semctl()` 可以保证对 semaphores 操作的原子性。

```
int semctl(int semid, int semnum, int cmd, .../*arg*/);
```

- semid: semget() 返回的 id
- semnum: the ID of the semaphore that you wish to manipulate the value of.
- cmd: 你想对 semaphore 的操作行为
- arg: 如果需要传入的话，是一个`union semun` 类型。

`union semun` 的定义如下：

```
union semun {
    int val;               /* used for SETVAL only */
    struct semid_ds *buf;  /* used for IPC_STAT and IPC_SET */
    ushort *array;         /* used for GETALL and SETALL */
};
```
cmd	        Effect
SETVAL	    Set the value of the specified semaphore to the value in the val member of the passed-in union semun.

GETVAL	    Return the value of the given semaphore.

SETALL	    Set the values of all the semaphores in the set to the values in the array pointed to by the array member of the passed-in union semun. The semnum parameter to semctl() isn't used.

GETALL	    Gets the values of all the semaphores in the set and stores them in the array pointed to by the array member of the passed-in union semun. The semnum parameter to semctl() isn't used.

IPC_RMID	Remove the specified semaphore set from the system. The semnum parameter is ignored.

IPC_STAT	Load status information about the semaphore set into the struct semid_ds structure pointed to by the buf member of the union semun.


针对最后两个选项 `IPC_RMID, IPC_STAT` 所影响的结构体 `struct semid_ds` 定义如下：

```
struct semid_ds {
    struct ipc_perm sem_perm;  /* Ownership and permissions
    time_t          sem_otime; /* Last semop time */
    time_t          sem_ctime; /* Last change time */
    unsigned short  sem_nsems; /* No. of semaphores in set */
};
```

### 8.3 semop(): Atomic power

`semop()` 系统调用可以完成 `set, get, test-n-set` 操作.

semop -- atomic array of operations on a semaphore set

```
#include <sys/sem.h>

int semop(int semid, struct sembuf *sops, unsigned int nspos);
```

The semop() system call atomically performs the array of operations indicated by **sops** on the semaphore set indicated by **semid**. The length of **sopes** is indicated by nsops. Each operation is encoded in a **struct sembuf**, which is defined as follows:

而  struct sembuf 的定义如下：

```
/* Warning!  Members might not be in this order! */

struct sembuf {
    ushort sem_num;     /* semaphore number #*/
    short sem_op;       /* semaphore operation */
    short sem_flg;      /* operation flags */
};
```

- sem_num: 要操作的信号量 number.
- sem_op: 具体的行为, 其取值的含义为：
    - Negative: A negative value for sem_op generally means that a process is waiting for a resource to become available
    - Positive: When sem_op is positive and the process has alter permission, the semaphore's value is incremented by sem_op's value. If SEM_UNDO is sepecified, the semaphore's adjust on exit value is decremented by sem_op's value. A positive value for sem_op generally corresponds to a process releasing a resource associcated with the semaphore.
    - Zero:     等待对应的 semaphore 变成 0
- sem_flg: 指定标记来改变 semop() 的行为。


### 8.4 Destroying a semaphore

和 `msgctl` 一样也可以用 `semctl` 来销毁一个 semaphore set. 常用的代码片断为：

```
int semid;
semid = semget();

...
semctl(semid, 0, IPC_RMID);
```

下面将用文件访问的例子来举例，虽然我们使用 `fcntl()` 锁可能更方便。但是信号量会更快些。另外信号量一般会和 Shared Memory Segments 一起使用。

## 9 Shared Memory Segments

Shared Memory Segment 即多个进程可以共享内存段. 其创建 `shmget()` 和 `msgget(), semget()` 类似，关闭操作也可以用 ipcs, ipcrm 来操作。

所以其创建的函数原型和代码片段为：

```
int shmget(key_t key, size_t size, int shmflg);
```

```
key_t key;
int shmid;

key = ftok("/my/shm/file.c", 'R');
shmid = shmget(key, 1024, 0664 | IPC_CREAT)
```

### 9.2 Attach me - getting a pointer to the segment

进程要使用共享的内存，需要用 `shmat()` 将共享内存 attach 到你想要访问的内存位置。其函数原型为：

```
void *shmat(int shmid, void *shmaddr, int shmflg);   // at 是 attach 的缩写。
```

`shmat()` maps the shared memory segment associated with the shared memory indentifier **shmid** into the address space of the calling process.

- shmid : shmget() 函数返回的 ID
- shmaddr: 自己可以指定进程要访问的地址空间进程映射，但是推荐使用 `(void *)(0) ` ，让 OS 为你分配。
- shmflg: 一些操作标记，如：SHM_RDONLY 等。

该函数出错时会返回 -1 并设置全局 errno, 其常用的代码片段为：

```
data = shmat(shmid, (void *)0, SHM_RDONLY);
if (data == (char *)(-1)) {
    perror("shmat");
}
```

### 9.3 Reading and Writing

有了 `data` 指针我们就可对这段内存地址进行操作。假设 data 是有 `\0` 字符结尾，那我们可以用下面的方式进行读写：

```
printf("shared contents: %s \n", data);
```

```
printf("Enter a string: ");
gets(data)
```

### 9.4 Detaching from and deleting segments

上面我们用 `shmat` 将共享内存映射到我们进程的可以的地址空间，那么当我们不在使用的时候，可以将其 unmap (detach) 掉。我需要使用 `shmdt()` 函数，dt 是 detach 的缩写。

```
int shmdt(void *shmaddr)
```
- shmaddr: shmat 返回的地址，这个函数很简单。

同样在共享内存不需要后，我们可以将其销毁，可以使用 `ipcs, ipcrm` 命令，也可以使用 `shmctl()` 函数来操作。

```
shmctl(shmid, IPC_RMID, NULL);
```
- [ ] 父进程与子进程映射的地址空间一样的吗？打印下地址。

### 9.5 Concurrency, 并发

因为我们是多个进程同时访问操作共享内存，所以进行并发控制是很有必要的。可以使用 semaphore 对其进行加锁。具体的并发控制还是要自己实现的。

- [ ] 如何实现并发那？

## 11 Unix sockets, Unix Domain Socket

FIFOs 像管道一样只能进行单身发送数据。而 Unix Domain Sockets 可支持双向发送，是一个全双工的管道。其 API 和网络 socket 类似。

### 11.1 Overview

虽然 Unix Sockets 类似于全双工的 FIFOs, 但是操作时需要用 socket api, 而不是用 file api, 即用 (socket, bind, recv ) 而不是用 (open, read)。

Unix socket 用文件路径来标识，使用下面的结构体：

```
struct sockaddr_un {
    unsigned short sun_family;          // AF_UNIX
    char sun_path[108];
}
```

### 11.2 What to to be a Server?

怎么才成为一个服务器那？分下面几个步骤：

1. `socket()` : 创建一个 Unix socket
2. `bind()` : 将 socket 绑定到一个 Unix domain 的地址上。
3. `listen()`: 在该地址上进行监听
4. `accept`: 接收客户端的请求，返回一个新的 socket ，新的 socket 用于与客户端进行通信，而老的 socket 继续监听。
5. Handle the connection: send(), recv() 进行全双工交互。
6. `close()` : 关闭 socket.

### 11.3 What to do be a client

怎么才能成为一个客户端那？分以下几步：
1. `socket()` : 创建一个 socket
2. `connect()`: 设置好 `struct sockaddr_un` 服务器地址信息，进行链接。
3. `send(), recv()`: 进行全双式交互.

### 11.4 `socketpair()` - quick full-duplex pipes

`pipe()` 返回的两个描述符是有方向性的：`fds[2]`, fds[0] 用于读， fds[1] 用于写。如果我想创建全双工的怎么办？那就使用 Unix socket 了，但是 Unix socket 进行 bind, listen, accept 还是比较繁琐。

`socketpaire()` 可以为我们创建一对已经连接好的 sockets。这样我不需要额外的工作，只负责通信通信就行了，十分简单吧。

下面的一个例子，我们创建两个进程，第一个进程发送一个字符给第二个进程，第二个进程接收到后转换成大写字符后再返回给第一个进程。

```
int main(void)
{
    int socks[2];
    char buf;
    pid_t pid;

    if (socketpair(AF_UNIX, SOCK_STREAM, 0, socks) == -1) {
        perror("[-] Error socketpair");
        exit(1);
    }

    if ((pid =fork()) == -1) {
        perror("[-] Error fork");
        exit(1);
    } else if (pid == 0) {
        close(socks[0]);
        read(socks[1], &buf, 1);
        printf("child: read '%c'\n", buf);
        buf = toupper(buf);
        write(socks[1], &buf, 1);
        printf("child: sent '%c' \n", buf);
    } else {
        close(socks[1]);
        write(socks[0], "b", 1);
        printf("parent: sent 'b' \n");
        read(socks[0], &buf, 1);
        printf("parent: read '%c' \n", buf);
        wait(NULL); // wait for child to die
    }
    return 0;
}
```


## References
1. [Beej's Guide to Unix IPC](http://beej.us/guide/bgipc/html/multi/index.html)
