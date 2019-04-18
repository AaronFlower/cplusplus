#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>


#define KEY_PATH "shm_write_counter.c"
#define SHM_KEY_ID 'a'
#define SEM_KEY_ID 'b'
#define COUNT 10

typedef struct shmseg {
    int counter;
    int write_complete;
    int read_complete;
} my_shmseg;

void shared_memory_increment(pid_t pid, my_shmseg*, int);
void remove_semaphore();

int main(void)
{
    int shmid;
    key_t key;
    pid_t pid;
    my_shmseg *shmp;

    printf("Total count is %d \n", COUNT);
    if ((key = ftok(KEY_PATH, SHM_KEY_ID)) == -1) {
        perror("[-] Error ftok");
        exit(1);
    }

    if ((shmid = shmget(key, sizeof(my_shmseg), 0644 | IPC_CREAT)) == -1) {
        perror("[-] Error shmget");
        exit(1);
    }

    shmp = shmat(shmid, NULL, 0);
    if (shmp == (void *)-1) {
        perror("[-] Error shmat");
        exit(1);
    }

    shmp->counter = 0;

    if((pid = fork()) > 0) {
        shared_memory_increment(pid, shmp, COUNT);
        wait(NULL);
    } else if (pid == 0) {
        shared_memory_increment(pid, shmp, COUNT);
        return 0;
    } else {
        perror("[-] Error fork");
        exit(1);
    }

    while(shmp->read_complete != 1) {
        sleep(1);
    }

    if (shmdt(shmp) == -1) {
        perror("[-] Error shmdt");
        exit(1);
    }

    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        perror("[-] Error shmctl");
        exit(1);
    }
    printf("Writing Process: Complete \n");
    remove_semaphore();
    return 0;
}

int initsem(key_t key, int numsems) {
    int i;
    union semun arg;
    struct semid_ds buf;
    struct sembuf sb;
    int semid;

    semid = semget(key, numsems, IPC_CREAT|IPC_EXCL|0644);
    if (semid >= 0) {
        sb.sem_op = 1;
        sb.sem_flg = 0;
        arg.val = 1;

        for (sb.sem_num = 0; sb.sem_num < numsems; ++sb.sem_num) {
            if (semop(semid, &sb, 1) == -1) {
                int e = errno;
                semctl(semid, 0, IPC_RMID);
                errno = e;
                exit(1);
            }
        }
    } else if(errno == EEXIST) {
        int retries = 10;
        int ready = 0;
        semid = semget(key, numsems, 0);
        if (semid < 0) {
            return semid;
        }

        arg.buf = &buf;
        for (i = 0; i < retries && !ready; ++i) {
            semctl(semid, numsems - 1, IPC_STAT, arg);
            if (arg.buf->sem_otime != 0) {
                ready = 1;
            } else {
                sleep(1);
            }
        }

        if(!ready) {
            errno = ETIME;
            return -1;
        }
    } else {
        return -1;
    }
    return semid;
}

void shared_memory_increment(pid_t pid, my_shmseg *shmp, int total_count) {
    int counter;
    int numtimes;

    int semid;
    key_t key;
    struct sembuf buf;

    if ((key = ftok(KEY_PATH, SEM_KEY_ID)) == -1) {
        perror("[-] Error fotk");
        exit(1);
    }

    if ((semid = initsem(key, 1)) == -1) {
        perror("[-] Error initsem");
        exit(1);
    }

    buf.sem_num = 0;
    buf.sem_op = -1; // allocating the resources
    buf.sem_flg = SEM_UNDO;
    if (semop(semid, &buf, 1) == -1) {
       perror("[-] Error semop lock");
       exit(1);
    }

    if (pid == 0) {
        printf("SHM_WRITE: CHILD now writing \n");
    } else {
        printf("SHM_WRITE: Parent now writing \n");
    }

    shmp->write_complete = 0;
    counter = shmp->counter;

    for (numtimes = 0; numtimes < total_count; ++numtimes) {
        counter += 1;
        shmp->counter = counter;
        if (counter % 2) {
            sleep(1);
        }
    }
    shmp->write_complete = 1;

    buf.sem_op = 1; // Releasing the resource */
    if (semop(semid, &buf, 1) == -1) {
        perror("[-] Error semop unlock ");
        exit(1);
    }

    if (pid) {
        printf("SHM_WRITE: parent writing done \n");
    } else {
        printf("SHM_WRITE: child  writing done \n");
    }

    return ;
}


void remove_semaphore () {
    int semid;
    key_t key;

    if ((key = ftok(KEY_PATH, SEM_KEY_ID)) == -1) {
        perror("[-] Error fotk");
        exit(1);
    }

    if ((semid = semget(key, 1, 0)) == -1) {
        perror("[-] Error ssemget");
        exit(1);
    }

    if (semctl(semid, 0, IPC_RMID)) {
        perror("[-] Error semctl remove");
        exit(1);
    }
    return;
}
