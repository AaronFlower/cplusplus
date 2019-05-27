#include <stdio.h>

int main(void)
{
    // 通过数组是会 stack 上分配空间的，所以可以赋值修改的。
    char s[] = "Hello";
    s[0] = 'a';

    printf("%s\n", s);

    return 0;
}
