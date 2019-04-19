## Multithreaded Programming (POSIX pthreads Tutorial)

为什么大多数程序都是 sequential (顺序执行的）？因为好多程序猿并不擅长写多线程并行程序。

### 1. What is a Thread ?

#### 1.1 Analogy, 类比

- What is a thread? Isn't that something you put through an eye of a sewing needle ?
  什么是线？是缝衣服时针里穿的线吗？

- Yes.
  是的

What does it relate to programming then?

   我们可以把一个处理器当成针头，程序中的线程当成线纤维。如果你有两个针，只有一个线，那么在完成一个工作的时候就需要花费很长的时间，因为有一根针是闲置的 (idle).

Think of sewing needles as the processors and the threads in a program as the thread fiber. If you had two needles but only one thread, it would take longer to finish the job (as one needle is idle) than if you split the thread into two and used both needles at the same time. Taking this analogy a little further, if one needle had to sew on a button (blocking I/O), the other needle could continue doing other useful work even if the other needle took 1 hour to sew on a single button. If you only used one needle, you would be ~1 hour behind!

#### 1.2 Definition


A computer program becomes a **process** when it is loaded from some store into the computer's memory and begins execution. A process can be executed by a processor or a set of processors. A process description in memory contains vital information such as the program counter which keeps track of the current position in the program (i.e. which instruction is currently being executed), registers, variable stores, file handles, signals, and so forth.

A **thread** is a sequence of such instructions within a program that can be executed independently of other code.

![process](https://randu.org/tutorials/threads/images/process.png)

#### 1.3 Terminology 术语

- Lightweight Process (LWP) , 轻量级进程。Lightweight Process (LWP) can be thought of as a virtual CPU where the number of LWPs is usually greater than the number of CPUs in the system. Thread libraries communicate with LWPs to schedule threads. LWPs are also sometimes referred to as kernel threads.

- **X-to-Y** model. The mapping **between LWPs and Threads**. Depending upon the operating system implementation and/or user-level thread library in use, this can vary from 1:1, X:1, or X:Y. **Linux, some BSD kernels, and some Windows versions use the 1:1 model**. User-level threading libraries are commonly in the X:1 class as the underlying kernel does not have any knowledge of the user-level threads. The X:Y model is used in Windows 7.
- **Contention Scope** is how threads compete for system resources (i.e. scheduling).
- **Bound threads** have system-wide contention scope, in other words, these threads contend with other processes on the entire system.
- **Unbound threads** have process contention scope.
- **Thread-safe** means that the program protects shared data, possibly through the use of mutual exclusion.
- **Reentrant** code means that a program can have more than one thread executing concurrently.
- **Async-safe** means that a function is reentrant while handling a signal (i.e. can be called from a signal handler).
- **Concurrency vs. Parallelism** - They are not the same! Parallelism implies simultaneous running of code (which is not possible, in the strict sense, on uniprocessor machines) while concurrency implies that many tasks can run in any order and possibly in parallel.

#### 1.4 Amdahl's Law and the Pareto Principle

如果你的程序，50% 都是不能并行的，那么通过并行处理，你最高能得到 2 倍的提升，无论你使用多少外理器。这就是 Amdahls Law。

$$
S \leq \frac{1}{1 - a + \frac{a}{n}}
$$

- a 是并行计算所占比例
- n 是并行处理结点个数

当 $ 1 - a = 0 $ 时，即全部都是可以并行的，没有串行，那么最大加速比为 n，即和处理器个数直线相关。

当 $1 - a = 1 $ 时，即全部都是串行的，没有可并行的，那么没有加速。

当 $1 - a = 0.5$ 时，即有 50 %是可并行的，那么并行处理的总体性能不可能超过 2 。

### 2. Thread Design Pattern

在一个程序中怎么使用线程有多种方式，没有那个最优的，需要根据要处理的问题类型来分析使用那种类型。常有三种模式

#### 2.1 Thread pool (Boss/Worker) 

One thread dispatches other threads to do useful work which are usually part of a *worker thread pool*. This thread pool is usually pre-allocated before the boss (or master) begins dispatching threads to work. Although threads are lightweight, they still incur overhead when they are created.

#### 2.2 Peer(work crew) 一起工作

The peer model is similar to the boss/worker model except once the worker pool has been created, the boss becomes the another thread in the thread pool, and is thus, a peer to the other threads.

#### 2.4 Pipeline

Similar to how pipelining works in a processor, each thread is part of a long chain in a processing factory. Each thread works on data processed by the previous thread and hands it off to the next thread. You must be careful to equally distribute work and take extra steps to ensure non-blocking behavior in this thread model or you could experience pipeline "stalls."

### 3. Protecting shared resources

#### 3.1 Mutual Exclusion 互斥

锁的类型一般有：

- Recursive
- Queuing
- Reader/Writer
- Scoped

Potential Traps 是要避免死锁。

#### 3.2 Atomic Operations

原子操作允许并行的进程在不互斥的情况下操作数据。一些编程语言会提供相应的原子操作函数。

### 4. Thread Synchronization Primitives

线程同步原语。Mutexes 是用来处理共享资源的同步策略，但进程之间是怎么同步的那？

#### 4.1 Join

A thread join is a protocol to allow the programmer to *collect* all relevant threads at a logical synchronization point. 

For example, in fork-join parallelism, threads are spawned to tackle parallel tasks and then join back up to the main thread after completing their respective tasks (thus performing an implicit barrier at the join point). Note that a thread that executes a join has terminated execution of their respective thread function.

#### 4.2  Condition Variables

Condition variables allow threads to synchronize to a value of a shared resource. Typically, condition variables are used as a notification system between threads. 

![cv](https://randu.org/tutorials/threads/images/condition_wait.png)

#### 4.3 Barriers

Barriers are a method to synchronize a set of threads at some point in time by having all participating threads in the barrier wait until all threads have called the said barrier function. This, in essence, blocks all threads participating in the barrier until the slowest participating thread reaches the barrier call.

#### 4.5 Spinlocks

Spinlocks are locks which *spin* on mutexes. Spinning refers to continuously polling until a condition has been met. In the case of spinlocks, if a thread cannot obtain the mutex, it will keep polling the lock until it is free. The advantage of a spinlock is that the thread is kept active and does not enter a sleep-wait for a mutex to become available, thus can perform better in certain cases than typical blocking-sleep-wait style mutexes. Mutexes which are heavily contended are poor candidates for spinlocks. 

Spinlocks should be avoided in uniprocessor contexts. Why is this?

#### 4.5 Semaphores

Semaphores are another type of synchronization primitive that come in two flavors: binary and counting. Binary semaphores act much like simple mutexes, while counting semaphores can behave as *recursive mutexes*. Counting semaphores can be initialized to any arbitrary value which should depend on how many resources you have available for that particular shared data. Many threads can obtain the lock simultaneously until the limit is reached. This is referred to as *lock depth*. 

Semaphores are more common in multiprocess programming (i.e. it's usually used as a synch primitive between processes).

### 5. POSIX pthreads

#### 5.1 Preminaries

- 引用头文件: `#include <phtread>`
- 在使用 `gcc` 编译时加上 `pthread` 选项。

#### 5.2 Creating pthreads

线程的数据类型是 `pthread_t` , 创建一个线程可以使用下面的函数：

```c
int pthread_create(pthread_t *thread, pthread_attr_t *attr, void *(*start_routine)(void *), *arg);
```

1. `pthread_t *thread`: the actual thread object that contains pthread id
2. `pthread_attr_t *attr`: attributes to apply to this thread
3. `void *(*start_routine)(void *)`: the function this thread executes
4. `void *arg`: arguments to pass to thread function above

```c++
void pthread_exit(void *value_ptr);
```

`pthread_exit()` terminates the thread and provides the pointer `*value_ptr` available to any `pthread_join()` call. 

```c++
int pthread_join(pthread_t thread, void **value_ptr);
```

`pthread_join()` suspends the calling thread to wait for successful termination of the thread specified as the first argument `pthread_t thread` with an optional `*value_ptr` data passed from the terminating thread's call to `pthread_exit()`. 

`pthread_join()` 不能等自己，两个线程也不能互相等待，不然会发生死锁。

pthread_join waits for the thread identified by the first argument to terminate. The calling thread's id cannot be the first argument which means a thread cannot wait for itself to terminate. Also, two threads cannot wait for each other to terminate. In all these cases the error EDEADLK is returned. If *retval* is not NULL, the pointer to the exit status of the thread is copied in **retval*. However, if the thread was cancelled, PTHREAD_CANCELED is copied in **retval*.

#### 5.3 pthread condition Variables

通过下面的宏或者调用 `pthread_cond_init()` 函数我们可以创建 pthread condition variables.

```c++
int pthread_cond_init(pthread_cond_t *cond, pthread_condattr_t *cond_attr);
# 或者
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
```

在`pthread_cond_init()`函数中也可能通过第二个参数设定相应的属性，使用默认属性第二个参数传 NULL 就行了。

线程可以根据条件变量做三种操作：`wait, signal, broadcast`:

```c++
int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
int pthread_cond_signal(pthread_cond_t *cond);
int pthread_cond_broadcast(pthread_cond_t *cond);
```

- `pthread_cond_wait()` 让当前线程进入 sleep 状态。需要关联一个 mutex 去等待。
- `pthread_cond_signal()` 从 sleep 的线程中唤醒一个线程。
- `pthread_cond_broadcast()` 唤醒在该条件变量等待的所有线程。

#### 5.4 pthread barrier

通 Barrier 也可对线程进行同步。在 barrier 使用之前也需要进行初始化。

```c++
int pthread_barrier_init(pthread_barrier_t *barrier, pthread_barrierattr_t *barrier_attr, unsigned int count);
 
pthread_barrier_t barrier = PTHREAD_BARRIER_INITIALIZER(count);

int pthread_barrier_wait(pthread_barrier_t *barrier);
 
```

- `count` 参数定义了线程数，这些线程必须 join the barrier, 这样 barrier 才会完成然后唤醒等待  barrier 的进程。(The count barrier defines the number threads that must join the barrier for the barrier to reach completion and unlock all threads waiting at the barrier).

#### 5.4 Miscellaneous

使用线程需要注意的问题：

1. 关于 pthread 的调用要检查函数返回值。
2. 对于想一直执行的线程，可以把它放到一人死循环中。

其它相关的函数：

- `pthread_kill()` can be used to deliver signals to specific threads.
- `pthread_self()` returns a handle on the calling thread.
- `pthread_equal()` compares for equality between two pthread ids
- `pthread_once()` can be used to ensure that an initializing function within a thread is only run once.

#### 6. Performance Considerations

- **Lock granularity** , 锁粒度。How "big" (coarse) or "small" (fine) are your mutexes? Do they lock your whole structure or fields of a structure? The more fine-grained you make your locks, the more concurrency you can gain, but at the cost of more overhead and potential deadlocks.
- **Lock ordering** - Make sure your locks are always locked in an agreed order (if they are not, make sure you take steps to rectify situations where locks are obtained in an out-of-order fashion, e.g. by using trylock/unlock calls).
- **Lock frequency** - Are you locking too often? Locking at unnecessary times? Reduce such occurences to fully exploit concurrency and reduce synchronization overhead.
- **Critical sections** - This has been mentioned before, but you should take extra steps to minimize critical sections which can be potentially large bottlenecks.
- **Worker thread pool** - If you are using a Boss/Worker thread model, make sure you pre-allocate your threads instead of creating threads on demand. It doesn't matter to the user how long it took your server to initialize, it only matters how fast it processes his or her request!
- **Contention scope** - Do your threads perform better when they are in contention with all of the system's processes? Or do they perform better when individually scheduled by the thread library itself? Only experimentation can give you the answers.
- **Scheduling class** - We have not touched on this topic, but changing the thread scheduling class from FIFO to RR can give better response times. But is this what you really want? Refer to Nichols or Lewis book for more information on thread scheduling classes.
- **Too many threads?** - At what point are there too many threads? Can it serverely impact and degrade performance? Again, only experimentation will give you the real answers to this question.

### References

1. [Multithreaded Programming (POSIX pthreads Tutorial)](https://randu.org/tutorials/threads/#resources)
2. [POSIX Threads Programming in C](https://www.softprayog.in/programming/posix-threads-programming-in-c)

