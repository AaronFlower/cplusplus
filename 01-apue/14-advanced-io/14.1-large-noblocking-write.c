#include <stdio.h>
#include <stdlib.h> // exit,
#include <unistd.h>
#include <fcntl.h>
#include <errno.h> // errno

char buf[500000]; // 500,000 bytes.

void clr_fl(int fd, int flags) {
    int val = fcntl(fd, F_GETFL, 0);
    if (val < 0) {
        perror("[-] Error fcntl F_GETFL error");
        exit(1);
    }

    val = ~flags;

    if (fcntl(fd, F_SETFL, val) < 0) {
        perror("[-] Error FCNTL_SETFL error ");
        exit(1);
    }
}

void set_fl(int fd, int flags) {
    int val = fcntl(fd, F_GETFL, 0);
    if (val < 0) {
        perror("[-] Error fcntl F_GETFL error");
        exit(1);
    }

    val |= flags;

    if (fcntl(fd, F_SETFL, val) < 0) {
        perror("[-] Error FCNTL_SETFL error ");
        exit(1);
    }
}

int main(void) {
    int n_towrite, n_write;

    char *ptr;

    n_towrite = read(STDIN_FILENO, buf, sizeof(buf));

    fprintf(stderr, "read %d bytes \n", n_towrite);
    set_fl(STDOUT_FILENO, O_NONBLOCK);

    ptr = buf;

    while (n_towrite > 0) {
        errno = 0;
        n_write = write(STDOUT_FILENO, ptr, n_towrite);
        fprintf(stderr, "nwrite = %d, errno = %d \n", n_write, errno);

        if (n_write > 0) {
            ptr += n_write;
            n_towrite -= n_write;
        }
    }

    clr_fl(STDOUT_FILENO, O_NONBLOCK);
    return 0;
}
