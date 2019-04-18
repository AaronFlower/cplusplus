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
#define COUNT 10

typedef struct shmseg {
    int counter;
    int write_complete;
    int read_complete;
} my_shmseg;

void shared_memory_increment(int pid, my_shmseg *shmp, int total_count);

int main(void)
{
    int key;
    int shmid;
    my_shmseg* shmp;
    pid_t pid;

    printf("Total count is %d\n", COUNT);


    // 创建 shared memory
    if ((key = ftok(KEY_PATH, KEY_ID)) == -1) {
        perror("[-] Error ftok");
        exit(1);
    }
    if ((shmid = shmget(key, sizeof(my_shmseg), 0644 | IPC_CREAT)) == -1) {
        perror("[-] Error shmget");
        exit(1);
    }

    // Attach to the segment to get pointer to it.
    shmp = shmat(shmid, NULL, 0);
    if (shmp == (void *)-1) {
        perror("[-] Error shmat");
        exit(1);
    }
    shmp->counter = 0;

    if ((pid = fork()) == -1) {
        perror("[-] Error fork");
        exit(1);
    } else if (pid == 0) {
        shared_memory_increment(pid, shmp, COUNT);
        return 0;
    } else {
        shared_memory_increment(pid, shmp, COUNT);
        /* wait(NULL); */
    }

    while(shmp->read_complete != 1) {
        sleep(1);
    }

    // Detach the segment pointer
    if (shmdt(shmp) == -1) {
        perror("[-] Error shmdt");
        exit(1);
    }

    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        perror("[-] Error shmctl");
        exit(1);
    }
    printf("Writing Process: Complete\n");
    return 0;
}

void shared_memory_increment(int pid, my_shmseg *shmp, int total_count) {
    int counter;
    int numtimes;
    int sleep_time;
    counter = shmp->counter;

    shmp->write_complete = 0;
    if (pid == 0) {
        printf("SHM_WRITE: CHILD: now writing \n");
    } else {
        printf("SHM_WRITE: PARENT: now writing \n");
    }

    for (numtimes = 0; numtimes < total_count; ++numtimes) {
        counter += 1;
        shmp->counter = counter;

        sleep_time = counter % 2;
        if (sleep_time) {
            sleep(1);
        }
    }
    sleep(1);

    shmp->write_complete = 1;

    if (pid == 0) {
        printf("SHM_WRITE: CHILD: now done \n");
    } else {
        printf("SHM_WRITE: Parent: now done \n");
    }
    return;
}
