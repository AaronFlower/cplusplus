#include <stdio.h>

int main(void)
{
    /**
     * 执行结果:[1] 5111 bus error
     */
    // 通过数组是会 stack 上分配空间的，所以可以赋值修改的。
    char s1[] = "Apple";
    s1[0] = 'a';

    // 而 const char * 是在 heap 上分配的，因为是 const char * 的， 所以不可以修改.
    // 会出现 bus error, 运行时错误。
    char *s2 = "Hello";
    s2[0] = 'a';

    printf("%s\n", s1);
    printf("%s\n", s2);

    return 0;
}
