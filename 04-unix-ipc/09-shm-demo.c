#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024 // 1K

int main(int argc, char *argv[])
{
    key_t key;
    int shmid;
    char *data;

    if (argc > 2) {
        fprintf(stderr, "usage: 09-shm-demo [data_to_write] \n");
        exit(1);
    }

    // make the key
    if ((key = ftok("09-shm-demo.c", 'A')) == -1) {
        perror("[-] Error ftok");
        exit(1);
    }

    // connect to (and possibly create) the segment.
    if ((shmid = shmget(key, SHM_SIZE, 0644 |IPC_CREAT)) == -1) {
        perror("[-] Error shmget");
        exit(1);
    }

    // attach to the segment to get a pointer to it
    data = shmat(shmid, (void *)0, 0);
    if (data == (char *)-1) {
        perror("[-] Error shmat");
        exit(1);
    }

    // read of modify the segment, based on the commnad line.
    if (argc == 2) {
        printf("writing to segment: \"%s\" \n", argv[1]);
        strncpy(data, argv[1], SHM_SIZE);
    } else {
        printf("segment contains: \"%s\" \n", data);
    }

    // detach from the segment
    if (shmdt(data) == -1) {
        perror("[-] Error shmdt");
        exit(1);
    }

    return 0;
}
