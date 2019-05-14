## Usage

epoll 有 ET, LT 两种触发模式。

LT 在触发时如果缓冲区的数据没有完全取走就会一直触发，直到完全取走为止。

ET 只会触发一次，如果没有完全取走，在下次内容发生改变是时才能继续读取。(在改变时触发)

### main-lt 执行结果 

```
$ ./main-lt

ll: polling for input ...
[+] Epoll: 0 ready events           # 等待计时结束，还没有 OK, while 循环继续执行; 

[+] Epoll: polling for input ...
[+] Epoll: 0 ready events           # 等待计时结束

[+] Epoll: polling for input ...
a
[+] Epoll: 1 ready events
[+] Epoll: Reading file descriptor '0' -- 2 bytes read.  # 输入 a, 读到 "a\n" 两个字符
Read 'a
'

[+] Epoll: polling for input ...
b
[+] Epoll: 1 ready events
[+] Epoll: Reading file descriptor '0' -- 2 bytes read. # 输入 a, 读到 "a\n" 两个字符
Read 'b
'

[+] Epoll: polling for input ...
hello
[+] Epoll: 1 ready events
[+] Epoll: Reading file descriptor '0' -- 6 bytes read. # 读到 "hello\n" 6 个字符  
Read 'hello
'

[+] Epoll: polling for input ...
This is  a very text for input
[+] Epoll: 1 ready events
[+] Epoll: Reading file descriptor '0' -- 10 bytes read. # 输入 OK, 但是一次性没有完全取走，触发第一次读取："This is  a"
Read 'This is  a'

[+] Epoll: polling for input ...
[+] Epoll: 1 ready events
[+] Epoll: Reading file descriptor '0' -- 10 bytes read. # 触发第二次: " very test"
Read ' very text'

[+] Epoll: polling for input ...
[+] Epoll: 1 ready events
[+] Epoll: Reading file descriptor '0' -- 10 bytes read. # 触发第三次: " for input"
Read ' for input'

[+] Epoll: polling for input ...
[+] Epoll: 1 ready events
[+] Epoll: Reading file descriptor '0' -- 1 bytes read. # 触发第四次: "\n"
Read '
'

[+] Epoll: polling for input ... # 计时结束
[+] Epoll: 0 ready events

[+] Epoll: polling for input ... # 计时结束
quit
[+] Epoll: 1 ready events        # 触发，读取 "quit\n" 结束
[+] Epoll: Reading file descriptor '0' -- 5 bytes read.
Read 'quit
'
```

### main-et 执行结果 

```
$ ./main-et
[+] Epoll: polling for input...             # 计时结束, 0 events ready
waiting you input...

[+] Epoll: polling for input...             # ready, 读取 "a\n"
a
[+] Epoll: 1 is ready -- 2 bytes read.
[+] Read: 'a
'

[+] Epoll: polling for input...
b
[+] Epoll: 1 is ready -- 2 bytes read.      # ready, 读取 "b\n"
[+] Read: 'b
'

[+] Epoll: polling for input...
hello
[+] Epoll: 1 is ready -- 6 bytes read.      # ready, 读取 "hello\n"
[+] Read: 'hello
'

[+] Epoll: polling for input...     
This si a long test
[+] Epoll: 1 is ready -- 10 bytes read.    # ready, 读取 "this si a ", 显然，我们没有完全取走，但是也不会触发了
[+] Read: 'This si a '

[+] Epoll: polling for input...
quit
[+] Epoll: 1 is ready -- 10 bytes read.   # ready, 我们再次输入触发，从上一次开始读取，读取的是 "long test" 而不是 "quit"
[+] Read: 'long test
'

[+] Epoll: polling for input...           
last
[+] Epoll: 1 is ready -- 5 bytes read.    # ready, 再次触发, 读取 "quit" 退出。 而我们 "last\n" 就被丢弃了。 
[+] Read: 'quit
'
```



