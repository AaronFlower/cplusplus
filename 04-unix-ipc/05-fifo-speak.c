#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "test.fifo"

int main(void)
{
    char s[300];
    int num, fd;

    mknod(FIFO_NAME, S_IFIFO | 0666, 0);
    printf("Waiting for reader ... \n");
    fd = open(FIFO_NAME, O_WRONLY);
    printf("got a reader -- type some stuff \n");
    while(gets(s), !feof(stdin)) {
        if ((num = write(fd, s, strlen(s))) == -1) {
            perror("[-] Error, write");
        } else {
            printf("speak: wrote %d bytes \n", num);
        }
    }
    return 0;
}