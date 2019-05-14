## epoll

- 对 accept 返回的新的 fd，初始化是一定是可写的，所以我们向其写入一个 『welcom kid』, 写入后等待客户端的写入。
- 客户端写入后，fd 则变成可读的， 因为是 ET 触发，所以我们需要保证取完，所以用 while 来实现，当再次出现 EAGAIN 时说明已经读完了，read 需要重新等待了，所以我们可向其写东西, 即写已经 ready 了，所以我们将相询必为 EPOLLOUT, 立即就可以得到可 write 的 event.


### References

1. [Linux epoll 详解](http://blog.lucode.net/linux/epoll-tutorial.html)

