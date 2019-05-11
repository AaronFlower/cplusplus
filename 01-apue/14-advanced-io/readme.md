## Advanced IO

### 14.1-large-noblocking-write.c

将 stdout 设置成非阻塞 IO。

```
./14.1-large-noblocking-write </etc/services >tmp.out 2>stderr.out
```

### 14.7-process-deadlock.c

父子进程读写同一文件时产生的死锁检测。
