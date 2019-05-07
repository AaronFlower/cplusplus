## Give me 15 minutes and I'll change your view of GDB

```
$ gdb a.out
start
list
ctrl x a  // ctrl+x 2
next
ctrl+l // ctrl + p, ctrl+n


// 还可以执行 python
> python print('Hello')
> python
import os
print ('my pid is %d' % os.getpid())

> b main
> b 9
> python print(gdb.breakpoints())
> python print(gdb.breakpoints()[0].location)


 > bubble_sort.c

$ while ./a.out; do echo OK; done
$ ls -lth core*
$ gdb -c core.14276

> b main
> b _exit.c:32
> p $pc ; // programming counter
> bt
>
```

### References

1. [gdb Debugging Full Example (Tutorial): ncurses](http://www.brendangregg.com/blog/2016-08-09/gdb-example-ncurses.html)
2. [Give me 15 minutes and I'll change your view of GDB](https://www.youtube.com/watch?v=PorfLSr3DD)
