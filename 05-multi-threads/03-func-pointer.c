#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(int (*cmp)(char *, char *)) {
    char *a = "123";
    char *b = "45";
    return cmp(a, b);
}

int numCmp(char* a, char * b) {
    int na = atoi(a);
    int nb = atoi(b);
    return na < nb;
}

int asciiCmp(char *a, char *b) {
    return strcmp(a, b);
}

int main(void)
{
    printf("Hello world!\n");
    printf("The numeric comparision result is : % d\n", compare(numCmp));
    printf("The ascii comparision result is : % d\n", compare(asciiCmp));
    return 0;
}
