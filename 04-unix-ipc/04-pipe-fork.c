#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
    int fds[2];
    pid_t pid;
    char buf[30];

    if (pipe(fds) == -1) {
        perror("[-] Error pipe");
        exit(1);
    }

    if ((pid = fork()) == -1) {
        perror("[-] Error fork");
        exit(1);
    } else if (pid == 0) {
        close(fds[0]);
        printf(" Child: writing to the pipe \n");
        write(fds[1], "hello", 6);
        printf(" Child: exiting\n");
        exit(0);
    } else {
        close(fds[1]);
        printf("Parent: reading from the pipe \n");
        read(fds[0], buf, 6);
        printf("Parent: read '%s' \n", buf);
        wait(NULL);
    }
    return 0;
}
