## APUE

APUE source code

### How to use.

Example: chapter11 -- thread create

- build

```
# example
cd 11-threads/02-create
gcc main.c -I../../include -w
```
- execute

```
./a.out
```

### What is the difference between `sdtout` and `STDOUT_FILENO`

在 `stdio.h` 定义中：

```
  #define stdin   __stdinp
  #define stdout  __stdoutp
  #define stderr  __stderrp
```

在 `unistd.h` 定义中:

```
#define	 STDIN_FILENO	0	/* standard input file descriptor */
#define	STDOUT_FILENO	1	/* standard output file descriptor */
#define	STDERR_FILENO	2	/* standard error file descriptor */
```

可以看出 `stdin, stdout, stderr` 是文件指针，而 `STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO` 是文件描述符。

两者的关系是：

```
STDOUT_FILENO = fileno(stdout);
```
