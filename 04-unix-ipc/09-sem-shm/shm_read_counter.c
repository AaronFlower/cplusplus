#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>


#define KEY_PATH "shm_write_counter.c"
#define KEY_ID 'a'

typedef struct shmseg {
    int counter;
    int write_complete;
    int read_complete;
} my_shmseg;


int main(void)
{
    int shmid;
    int key;
    my_shmseg* shmp;

    if ((key = ftok(KEY_PATH, KEY_ID)) == -1) {
        perror("[-] Error fotk");
        exit(1);
    }

    if ((shmid = shmget(key, sizeof(my_shmseg), 0644|IPC_CREAT)) == -1) {
        perror("[-] Error shmget");
        exit(1);
    }

    // Attach to the segment to get a pointer to it.
    shmp = shmat(shmid, NULL, 0);
    if (shmp == (void *)-1) {
        perror("[-] Error shmat");
        exit(1);
    }

    // Read the shared memory counter and print it on standard oupt.
    while (shmp->write_complete != 1) {
        if (shmp->counter == -1) {
            perror("[-] Error read");
            exit(1);
        }
        sleep(3);
    }

    printf("Reading Process: Shared memory : counter is %d \n", shmp->counter);
    printf("Reading Process: Reading Done, Detaching shared memory \n");
    shmp->read_complete = 1;

    if (shmdt(shmp) == -1) {
        perror("[-] Error shmdt");
        exit(1);
    }
    printf("Reading process: Complete \n");

    return 0;
}
