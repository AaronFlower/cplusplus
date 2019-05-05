## All about c

### 1. typedef, 函数指针，指针

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

### 2. [Why does a C-Array have a wrong sizeof() value when it's passed to a function?](https://stackoverflow.com/questions/2950332/why-does-a-c-array-have-a-wrong-sizeof-value-when-its-passed-to-a-function)

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


### 3. C/C++ Multi-lines

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
### 4. `restrict` 关键字

在 C99 标准后，C 引入了一个新的关键字，即 `restrict`.

- `restrict` 关键字主要用于指针的声明中，用于修饰指针，是一个指针修饰符(pointer qualifier).
- 它并不提供任何新的功能，只是用来告诉编译器可以优化编译。
- 当我们用 `restrict` 来修饰指针后，它只是告诉编译器，该指针所指向的对象只有一种访问方式，那就是通过该指针，编译器不需要做其它任何检查。
- 如果程序员使用了 `restrict` 修饰符，但是实际上却违反了上面的限制，那么编译的结果是 undefined 的。
- c++ 不支持 `restrict`, 仅 C 支持。

如查不使用 `restrict` 关键字，编译会做什么检查那？ 以下面两个函数为例，

```c
int foo(int *a, int *b)
{
    *a = 5;
    *b = 6;
    return *a + *b;
}

int rfoo(int *restrict a, int *restrict b)
{
    *a = 5;
    *b = 6;
    return *a + *b;
}
```

假设我们在调用时候参数是指向同一个地址：

```
int i = 0;
int *a = &i;
int *b = &i;
foo (a, b);
rfoo(a, b);
```

在 foo() 函数执行到 `return *a + *b` 时，还需要重新检查一遍 `*a` 的值，因为可能会被改变 （如这里 b 也指定了同样的地址）。所以编译出来的汇编指令如下：

```
foo:
    movl    $5, (%rdi)    # store 5 in *a
    movl    $6, (%rsi)    # store 6 in *b
    movl    (%rdi), %eax  # read back from *a in case previous store modified it
    addl    $6, %eax      # add 6 to the value read from *a
    ret
```

即会多一个 `movl    (%rdi), %eax` 语句。但是如果我们程序员确保调用时，指针的访问只能一个入口，那么就可以加上 `restrict` 关键字，即 `rfoo()` 函数，编译出的指令如下：

```
rfoo:
    movl      $11, %eax   # the result is 11, a compile-time constant
    movl      $5, (%rdi)  # store 5 in *a
    movl      $6, (%rsi)  # store 6 in *b
    ret
```

这样性能就会有所提高了。 但如果用了 restrict 去修饰两个指针，但是在调用时它们在作用域内又指向同一地址，那么是未定义行为.
一般而言，编写代码时通常会忽略pointer aliasing 的问题。更常见是在性能剖测时，通过反编译看到很多冗余的读取指令，才会想到加入restrict 关键字来提升性能。

参考：1.[restrict 关键字](https://www.zhihu.com/question/41653775)

另外，在我们阅读 Unix 源码时，会发现系统在实现时并不是直接加上 `restrict` 关键字，而是用一个宏来完成，因为毕竟 `restrict` 关键字是 C99 之后才实现的，如是 C99 之前就应该为空。

```c
/*
 * We use `__restrict' as a way to define the `restrict' type qualifier
 * without disturbing older software that is unaware of C99 keywords.
 */
#if __STDC_VERSION__ < 199901
#define __restrict
#else
#define __restrict      restrict
#endif
```

而在使用时直接用 `__restrictg` 来替换就可以了。

```c
int rfoo(int *__restrict a, int *__restrict b);
```
