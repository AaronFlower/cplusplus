#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

int main(void)
{
    int fds[2];
    char buf[30];

    if (pipe(fds) == -1) {
        perror("[-] Error pipe");
        exit(1);
    }

    printf("writing to file descriptor #%d \n", fds[1]);
    write(fds[1], "test", 5);
    printf("reading from file descriptor #%d \n", fds[0]);
    read(fds[0], buf, 5);
    printf("read '%s' \n", buf);
    return 0;
}
