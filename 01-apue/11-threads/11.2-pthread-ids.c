#include <stdio.h>
#include <stdlib.h>         // for exit()
#include <unistd.h>         // for getpid(), for getppid()
#include <pthread.h>        // for pthread

pthread_t ntid, ntid2;

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

    int err;

    err = pthread_create(&ntid, NULL, thr_fn, NULL);
    if (err != 0) {
        perror("[-] Error pthread_create");
        exit(1);
    }

    err = pthread_create(&ntid2, NULL, thr_fn, NULL);
    if (err != 0) {
        perror("[-] Error pthread_create");
        exit(1);
    }
    printids("main thread:");
    sleep(1);
    return 0;
}
