## All about c

### typedef, 函数指针，指针

typedef, 函数指针，指针的声明都是将新的类型，声明，变量名放在对应变量名或函数名出现的位置。

- 定义结构体并声明变量

```
struct student {
    char *name;
    int age;
} stu1;
```

那么如果想要用 typedef 定义新的类型，只需要把新的类型放在变量名的位置上即如。如下：

```
typedef struct student {
    char *name;
    int age;
} student, *studentP;
```

那么我们就定义了两个新类型：student 和 studentP;

再如：

```
typedef int myInt;
typedef unsigned int size_t;
```

`myInt, size_t` 都是出现在变量名的位置上。

- 函数指针的定义

比如我们有一个 sort 函数，这个函数接收一个函数指针，使得用户可以自定义比较函数。一般的比较函数如下：

```
int myCompare(const void *p1, const void *p2);
```

那么如果我们想声明一个对应的函数指针，只需要将其函数名替换成我们的函数指针变量名即可，记得指针类型是要用 * 标识的，而且这个指针变量要用括号包住，不然就变成了返回 int * 类型的函数了。即，如下：

```
int (*cmp)(const void *p1, const void *p2);
```

所以我们的 sort 函数可以定义如下：

```
void sort(void *data, int (*cmp)(const void *p1, const void *p2)) {
}
```

- 其它类型指定的定义

```
int *p1;
size_t *p2;
```
