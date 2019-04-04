## Server-Client

### How to use

```
make

# run the server

./server.o

# run the the client, you can run mulitple clients.
./client
./client
```

### Zombie Process

Because we don't use `wait, waitpid`，when one client disconnected from the server the process will become one zombie process.

- [ ] Handle Zombie Process.

```
❯ ps aux|grep server.o
easonzhan         6160   0.0  0.0  4268036    720 s009  S+    4:15PM   0:00.00 ./server.o
easonzhan        21795   0.0  0.0        0      0 s009  Z+    4:20PM   0:00.00 (server.o)
easonzhan        15598   0.0  0.0        0      0 s009  Z+    4:18PM   0:00.00 (server.o)
easonzhan         7023   0.0  0.0        0      0 s009  Z+    4:15PM   0:00.00 (server.o)
easonzhan         9419   0.0  0.0        0      0 s009  Z+    4:16PM   0:00.00 (server.o)
easonzhan         6579   0.0  0.0        0      0 s009  Z+    4:15PM   0:00.00 (server.o)
easonzhan        30407   0.0  0.0  4268060    832 s013  S+    7:54PM   0:00.00 grep --color=auto --exclude-dir=.bzr --exclude-dir=CVS --exclude-dir=.git --exclude-dir=.hg --exclude-dir=.svn server.o
```

`Z+` 表示的是 Zombie 僵死进程。
