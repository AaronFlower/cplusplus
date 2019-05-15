/**
 * 父进程打开的 fd 会被 子进程继承共享，offset 相互影响；
 * 运行时，可以通过 read 的结果可以看到 offset 是想到影响的。
 */
#include <stdio.h>
#include <stdlib.h>     // exit
#include <unistd.h>     // for fork
#include <fcntl.h>      // for fcntl()

#define BUF_SIZE    32

int main(void) {
    int fd;
    pid_t pid;
    int val;
    char buf[BUF_SIZE];

    if ((fd = open("x02-fork-inherit-fd.c", O_RDONLY)) < 0) {
        perror("[-] Error open");
        exit(1);
    }

    val = fcntl(fd, F_GETFD);
    if (fcntl(fd, F_SETFD, val | FD_CLOEXEC) < 0) {
        perror("[-] Error fcntl");
        exit(1);
    }

    if ((pid = fork()) < 0) {
        perror("[-] Error fork");
        exit(1);

    } else if (pid == 0) {
        printf("[+] Child: fd is %d \n", fd);
        if (read(fd, buf, BUF_SIZE) < 0) {
            perror("[-] Error read in child");
            exit(1);
        }
        printf("[+] Child: read %s\n", buf);
        close(fd);
    } else {
        sleep(1);
        printf("[+] Parent: fd is %d \n", fd);
        if (read(fd, buf, BUF_SIZE) < 0) {
            perror("[-] Error read in parent");
            exit(1);
        }
        printf("[+] Parent: read  %s\n", buf);
        close(fd);
    }

    return 0;
}
