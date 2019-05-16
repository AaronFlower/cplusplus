## Usage

### 3.11-file-status-flags

该程序的执行很有意思，可以灵活的使用 `<`, `>` 重定向符。

```
$ ./3.11-file-status-flags 0 </dev/tty
ready only

$ ./3.11-file-status-flags 1 >foo.txt

$ cat foo.txt
write only

$ ./3.11-file-status-flags 1 >>foo.txt

$ cat foo.txt
write only
write only
append

$ ./3.11-file-status-flags 5 5<>foo.txt
read write
```

`5 <> foo.txt` 是打开 temp.foo 文件，并且指定 fd 为 5.
