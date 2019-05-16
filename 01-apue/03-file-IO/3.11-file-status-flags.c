#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int val;

    if (argc != 2) {
        printf("usage: a.out <descriptor> \n");
        exit(1);
    }

    int fd = atoi(argv[1]);

    if ((val = fcntl(fd, F_GETFL, 0)) < 0) {
        perror("[-] Error fcntl F_GETFL error");
        exit(1);
    }

    // 访问属性
    switch (val & O_ACCMODE) {
        case O_RDONLY:
            printf("ready only\n");
            break;
        case O_WRONLY:
            printf("write only\n");
            break;
        case O_RDWR:
            printf("read write\n");
            break;
        default:
           perror("[-] Error unknow access mode");
           exit(1);
    }

    if (val & O_APPEND) {
        printf("append\n");
    }

    if (val & O_NONBLOCK) {
        printf("nonblocking\n");
    }
    if (val & O_SYNC) {
        printf("synchronous writes\n");
    }

    return 0;
}
