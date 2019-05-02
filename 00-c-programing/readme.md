## All about c

### typedef, 函数指针，指针

typedef, 函数指针，指针的声明都是将新的类型，声明，变量名放在对应变量名或函数名出现的位置。

- 定义结构体并声明变量

```c
struct student {
    char *name;
    int age;
} stu1;
```

那么如果想要用 typedef 定义新的类型，只需要把新的类型放在变量名的位置上即如。如下：

```c
typedef struct student {
    char *name;
    int age;
} student, *studentP;
```

那么我们就定义了两个新类型：student 和 studentP;

再如：

```c
typedef int myInt;
typedef unsigned int size_t;
```

`myInt, size_t` 都是出现在变量名的位置上。

- 函数指针的定义

比如我们有一个 sort 函数，这个函数接收一个函数指针，使得用户可以自定义比较函数。一般的比较函数如下：

```c
int myCompare(const void *p1, const void *p2);
```

那么如果我们想声明一个对应的函数指针，只需要将其函数名替换成我们的函数指针变量名即可，记得指针类型是要用 * 标识的，而且这个指针变量要用括号包住，不然就变成了返回 int * 类型的函数了。即，如下：

```c
int (*cmp)(const void *p1, const void *p2);
```

所以我们的 sort 函数可以定义如下：

```c
void sort(void *data, int (*cmp)(const void *p1, const void *p2)) {
}
```

- 其它类型指定的定义

```c
int *p1;
size_t *p2;
```

### [Why does a C-Array have a wrong sizeof() value when it's passed to a function?](https://stackoverflow.com/questions/2950332/why-does-a-c-array-have-a-wrong-sizeof-value-when-its-passed-to-a-function)

```c
#include <stdio.h>

void PrintSize(int p_someArray[10]);

int main () {
    int myArray[10];
    printf("%d\n", sizeof(myArray)); /* As expected, 40 */
    PrintSize(myArray);/* Prints 4, not 40 */
}

void PrintSize(int p_someArray[10]){
    printf("%d\n", sizeof(p_someArray));
}
```

C 语言的数组在做类型类型传递时，会被隐式的当成指针传递给函数。So,

```c
void PrintSize(int p_someArray[10]) {
    printf("%zu\n", sizeof(p_someArray));
}
```
and

```c
void PrintSize(int *p_someArray) {
    printf("%zu\n", sizeof(p_someArray));
}
```

are equivalent. So what you get is the value of `sizeof(int*)` .

所以一般情况下，都需要再传递长度参数。It's a pointer, that's why it's a common implementation to pass the size of the array as a second parameter to the function.

In general, you should always pass the size (number of elements) of an array along with an array to a function.


### C/C++ Multi-lines

在 C/C++ 被双引号正常包裹的字符串可以写在一起。如下：

```c
#include <stdio.h>


#define STR "Macro String"

int main(void)
{
    char *str1 = "Hello " "world!";
    char *str2 = "Hello "
        "world!";

    char *str3 =
        "Hello "
        "world!";
    printf("%s\n", str1);
    printf("%s\n", str2);
    printf("%s\n", str3);
    printf("This is a " STR);
    return 0;
}

```

程序执行结果：

```
❯ ./a.out
Hello world!
Hello world!
Hello world!
This is a Macro String
```
