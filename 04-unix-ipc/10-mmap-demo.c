#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int fd, offset;
    char *data;
    struct stat sbuf;
    int pagesize;

    if (argc != 2) {
        fprintf(stderr, "usage: 10-mmap-demo <offset> \n");
        exit(1);
    }

    if ((fd = open("10-mmap-demo.c", O_RDONLY)) == -1) {
        perror("[-] Error open");
        exit(1);
    }

    if (stat("10-mmap-demo.c", &sbuf) == -1) {
        perror("[-] Error stat");
        exit(1);
    }

    offset = atoi(argv[1]);
    if (offset < 0 || offset > sbuf.st_size - 1) {
        fprintf(stderr, "[-] Error: offset must be in the range 0-%lld \n", sbuf.st_size - 1);
        exit(1);
    }

    pagesize= getpagesize();
    printf("The Pagesize is %dB \n", getpagesize());
    data = mmap(NULL, sbuf.st_size, PROT_READ, MAP_SHARED, fd, 0 * pagesize);

    if (data == (void *)-1) {
        perror("[-] Error mmap");
        exit(1);
    }

    printf("byte at offset %d is '%c' \n", offset, data[offset]);
    return 0;
}
