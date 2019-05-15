#include <stdio.h>
#include <stdlib.h>         // for atoi()
#include <strings.h>
#include <unistd.h>         // for read()

#define BUF_SIZE 4

int main(int argc, char *argv[])
{
    (void)argc;
    char buf[BUF_SIZE];
    int fd = atoi(argv[1]);
    pid_t pid = getpid();

    bzero(buf, BUF_SIZE);

    printf("  [+] Exec(%d): I was executed by execl, fd = %d\n", pid, fd);
    if (read(fd, buf, BUF_SIZE - 1) < 0) {
        perror("  [-] Error read in exec");
        exit(1);
    } else {
        printf("  [+] Exec(%d): fd is %d\n", pid,  fd);
        printf("  [+] Exec(%d): %s \n", pid, buf);
    }

    return 0;
}
