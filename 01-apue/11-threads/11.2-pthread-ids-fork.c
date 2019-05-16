#include <stdio.h>
#include <stdlib.h>         // for exit()
#include <unistd.h>         // for getpid(), for getppid()
#include <pthread.h>        // for pthread

#define NUM 2

pthread_t ntid, ntid2;
pthread_t tids[NUM];

void printids(const char *s) {
    pid_t pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();
    printf("%s pid %lu tid %lu (0x%lx)\n", s, (unsigned long)pid, (unsigned long)tid, (unsigned long)tid);
}


void * thr_fn(void *arg) {
    (void)arg;
    printids("new thread: ");
    return ((void *)0);
}

int main(void) {

    int err, i;
    pid_t pid;

    for (i = 0; i < NUM; ++i) {
        err = pthread_create(tids + i, NULL, thr_fn, NULL);
        if (err) {
            perror("[-] Error pthread_create");
            exit(1);
        }
    }

    if ((pid = fork()) < 0) {
        perror("[-] Error fork");
        exit(1);
    } else if (pid == 0) {
        for (i = 0; i < NUM; ++i) {
            err = pthread_create(tids + i, NULL, thr_fn, NULL);
            if (err) {
                perror("[-] Error pthread_create");
                exit(1);
            }
        }
    }

    printids("main thread:");
    sleep(1);
    return 0;
}
