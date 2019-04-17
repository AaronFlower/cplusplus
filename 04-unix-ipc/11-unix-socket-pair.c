#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

/*
 * 下面的一个例子，我们创建两个进程，第一个进程发送一个字符给第二个进程，
 * 第二个进程接收到后转换成大写字符后再返回给第一个进程。
 */
int main(void)
{
    int socks[2];
    char buf;
    pid_t pid;

    if (socketpair(AF_UNIX, SOCK_STREAM, 0, socks) == -1) {
        perror("[-] Error socketpair");
        exit(1);
    }

    if ((pid =fork()) == -1) {
        perror("[-] Error fork");
        exit(1);
    } else if (pid == 0) {
        close(socks[0]);
        read(socks[1], &buf, 1);
        printf("child: read '%c'\n", buf);
        buf = toupper(buf);
        write(socks[1], &buf, 1);
        printf("child: sent '%c' \n", buf);
    } else {
        close(socks[1]);
        write(socks[0], "b", 1);
        printf("parent: sent 'b' \n");
        read(socks[0], &buf, 1);
        printf("parent: read '%c' \n", buf);
        wait(NULL); // wait for child to die
    }
    return 0;
}
