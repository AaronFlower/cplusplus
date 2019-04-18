#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define MAX_RETRIES 10

/**
 * initsem() : semaphore has fatal flaw, create and initilaize cann't be atomic. Use this method to tackle
 */
int initsem(key_t key, int numSems) { // key from ftok
    int i;
    union semun arg;   // 传入 semctl 函数的 arg, 用于指定命令操作。
    struct semid_ds buf;  // 当 union semun 的 buf 定义。
    struct sembuf sb;  // semop() 操作的结构体
    int semid;

    semid = semget(key, numSems, IPC_CREAT | IPC_EXCL | 0666);

    if (semid >= 0) {
        // 初始化时 semaphore set 中的每一个 semaphore 的 value 都设置为 1，保证有一个资源可用。
        sb.sem_op = 1;
        sb.sem_flg = 0;

        arg.val = 1;

        for (sb.sem_num = 0; sb.sem_num < numSems; ++sb.sem_num) {
            /* do a semop() to 'free' the semaphores. */
            /* this sets the sem_otime field, as needed below. */
            // int semop(int semid, struct sembuf *sops, size_t nsops);
            if (semop(semid, &sb, 1) == -1) {
                int e = errno;
                semctl(semid, 0, IPC_RMID); // clean up
                errno = e;
                return -1;
            }
        }
    } else if (errno == EEXIST) { // 已经创建了
        int ready = 0;
        // 获取已经创建的 semid
        if ((semid = semget(key, numSems, 0)) < 0){
            return -1;
        }

        /* 等待其它进程来初始化 semaphore */
        arg.buf = &buf;
        for (i = 0; i < MAX_RETRIES && !ready; ++i) {
            if(semctl(semid, numSems - 1, IPC_STAT, arg) == -1) {
                return -1;
            }
            if (arg.buf->sem_otime != 0) {
                ready = 1;
            } else {
                sleep(1);
            }
        }
        if (!ready) {
            errno = ETIME;
            return -1;
        }
    } else {
        return semid;
    }
    return semid;
}

int main(void)
{
    key_t key;
    int semid;
    struct sembuf sb;


    if ((key = ftok("08-sem-demo.c", 'a')) == -1) {
        perror("[-] Error ftok");
        exit(1);
    }

    // grap the semaphore set
    if ((semid = initsem(key, 1)) == -1) {
        perror("[-] Error initsem");
        exit(1);
    }

    printf("Press return to lock: \n");
    getchar();
    printf("Trying to lock... \n");

    sb.sem_num = 0;
    sb.sem_op = -1; /* negative, set to allocate resource */
    sb.sem_flg = SEM_UNDO;
    if (semop(semid, &sb, 1) == -1) {
        perror("[-] Error semop");
        exit(1);
    }

    printf("Locked. \n");
    printf("Press return to unlock \n");
    getchar();

    sb.sem_op = 1; /* positive, free resource */
    if (semop(semid, &sb, 1) == -1) {
        perror("[-] Error semop");
        exit(1);
    }
    printf("Unlocked \n");

    // remove the sem
    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("semctl");
        exit(1);
    }

    return 0;
}
