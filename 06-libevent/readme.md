## libevent

### 什么是 libevent?

`libevent` 提供了一种回调机制，即在文件描述符上的具体事件完成时、或者是某个时间点执行相应的 callback 函数的机制。另外, 它也支持 `signals` 的回调以及超时回调。

`libevent` 的目的是替换网络服务器中的 event loop. 应用程序只需要使用 `event_dispatch()` 动态的添加和删除 events 即可。

`libevent` 主要是为了解决，Unix 系统各发行版的事件处理机制不致问题，其对 `/dev/poll, kqueue, event ports, POSIX select, Windows select(), poll(), epoll()` 进行封装，然后提供统一的 API.

`libevent` 可以用在可移植程序中，而多线程的应用程序也可以使用 `libevent`, 可以通过 `event_base` 的隔离可以保证只有一个线程访问，或者通过锁限制访问性。


> 基本的socket编程是阻塞/同步的，每个操作除非已经完成或者出错才会返回，这样对于每一个请求，要使用一个线程或者单独的进程去处理，系统资源没法支撑大量的请求（所谓c10k problem），例如内存(默认情况下每个线程需要占用2～8M的栈空间)，以及进程切换带来的原因等。posix定义了可以使用异步的select系统调用，但是因为其采用了轮询的方式来判断某个fd是否变成active，效率不高[O(n)]，连接数一多，也还是撑不住。于是各系统分别提出了基于异步/callback的系统调用，例如Linux的epoll，BSD的kqueue，Windows的IOCP。由于在内核层面做了支持，所以可以用O(1)的效率查找到active的fd。基本上，libevent就是对这些高效IO的封装，提供统一的API，简化开发。

### 使用 `libevent` 的应用程序

- Chromium
- Memcached
- tmux
- Tor


### References

1. [libevent](http://libevent.org/)
2. [libevent入门教程：Echo Server based on libevent ](https://www.felix021.com/blog/read.php?2068)
