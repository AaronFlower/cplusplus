#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    (void)argv;
    int fd;

    /* struct flock fl = { */
    /*     F_WRLCK, // l_type */
    /*     SEEK_SET, // l_whence */
    /*     0, // l_start */
    /*     0, // l_len */
    /*     0, // l_pid */
    /* }; */

                    /* l_type   l_whence  l_start  l_len  l_pid   */
    struct flock fl = {F_WRLCK, SEEK_SET,   0,      0,     0 };
    fl.l_pid = getpid();

    if (argc > 1) {
        fl.l_type = F_RDLCK;
    }

    if ((fd = open("06-lock-demo.c", O_RDWR)) == -1) {
        perror("[-] Error open");
        exit(1);
    }

    printf("Press <RETURN> to try get lock: \n");
    getchar();
    printf("Trying to get lock...\n");
    if (fcntl(fd, F_SETLKW, &fl) == -1) {
        perror("[-] Error fcntl");
        exit(1);
    }
    printf("got lock \n");
    printf("Press <RETURN> to  release lock: \n");
    getchar();

    fl.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLK, &fl) == -1) {
        perror("fcntl");
        exit(1);
    }

    printf("Unlocked. \n");
    close(fd);

    return 0;
}
