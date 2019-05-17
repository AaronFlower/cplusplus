#include <stdio.h>
#include <stdlib.h>     // for exit()
#include <pthread.h>    // for pthreads functions

void *thr_fn1(void *arg) {
    (void)(arg);
    printf("[+] thread 1: returning \n");
    return ((void *)1);
}

void *thr_fn2(void *arg) {
    (void)(arg);
    printf("[+] thread 2: returning \n");
    pthread_exit((void *)2);
}

int main(void) {
    int err;
    pthread_t tid1, tid2;
    void *tret;

    if ((err = pthread_create(&tid1, NULL, thr_fn1, NULL)) != 0) {
        perror("[-] Error pthread_t");
        exit(1);
    }

    if ((err = pthread_create(&tid2, NULL, thr_fn2, NULL)) != 0) {
        perror("[-] Error pthread_t");
        exit(1);
    }

    if ((err = pthread_join(tid1, &tret)) != 0) {
        perror("[-] Error pthread_join 1");
        exit(1);
    }

    printf("[+] thread1: exit code %ld \n", (long)tret);

    if ((err = pthread_join(tid2, &tret)) != 0) {
        perror("[-] Error pthread_join 2");
        exit(1);
    }
    printf("[+] thread2: exit code %ld \n", (long)tret);

    return 0;
}
