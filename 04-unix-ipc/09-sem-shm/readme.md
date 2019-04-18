## How to use

这个例子是在主进程中 fork 出一个子进程，父子进程同时向共享内存进行累加，直到累加和到 1000。

### 版本 1
版本 1 我们只使用共享内存，进程在写的时候不做并发控制。这个版本是有问题的。
- `shm_write_counter.c` : 创建两个进程同时向共享内存的数据进行累加。
- `shm_read_counter.c` : 读取共享内存中的数据。

### 版本 2
在这个版本中，我们引入了 semaphore 来解决主子进程的并发问题。

- `shm_write_counter_with_sem.c`: 引入 semophore 版本的写程序
- `shm_read_counter.c` : 读取共享内存中的数据。
