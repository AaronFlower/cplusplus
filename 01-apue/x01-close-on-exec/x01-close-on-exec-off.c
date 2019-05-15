#include <stdio.h>
#include <stdlib.h>     // exit
#include <unistd.h>     // for fork(), execl()
#include <fcntl.h>      // for fcntl()

#define BUF_SIZE    4

int main(void) {
    int fd;
    pid_t pid;
    int val;
    char buf[BUF_SIZE];
    char fd_str[10];

    if ((fd = open("marks.txt", O_RDONLY)) < 0) {
        perror("[-] Error open");
        exit(1);
    }

    val = fcntl(fd, F_GETFD);
    // close-on-exec off ,  默认就是关闭的，没有FD_CLOEXEC 标记
    if (fcntl(fd, F_SETFD, val) < 0) {
        perror("[-] Error fcntl");
        exit(1);
    }

    printf("Turn close-on-exec flag OFF\n");

    if ((pid = fork()) < 0) {
        perror("[-] Error fork");
        exit(1);

    } else if (pid == 0) {
        printf("[+] Child(%d): fd is %d \n", getpid(), fd);
        if (read(fd, buf, BUF_SIZE - 1) < 0) {
            buf[BUF_SIZE - 1] = '\0';
            perror("[-] Error read in child");
            exit(1);
        }
        printf("[+] Child(%d): read %s\n", getpid(), buf);


        sprintf(fd_str, "%d", fd);
        if (execl("./x02-exec", "x02-exec", fd_str, NULL) < 0) {
            perror("[-] Error execl");
            exit(1);
        }
        /* close(fd); // close 释放引用, 不会影响父进程的引用 */
        /* printf("[+] Child(%d): close fd\n"); */
    } else {
        sleep(1);
        printf("[+] Parent(%d): fd is %d \n", getpid(), fd);
        if (read(fd, buf, BUF_SIZE - 1) < 0) {
            buf[BUF_SIZE - 1] = '\0';
            perror("[-] Error read in parent");
            exit(1);
        }
        printf("[+] Parent(%d): read  %s\n", getpid(), buf);
        close(fd); // close 释放引用，不会影响子进程的引用
        printf("[+] Parent(%d): close fd\n", getpid());
        waitpid(pid, NULL, 0);
    }

    return 0;
}
