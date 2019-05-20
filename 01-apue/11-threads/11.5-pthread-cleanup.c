#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // for pause();
#include <pthread.h>

void cleanup(void *arg) {
    printf("[+] cleanup: %s\n", (char *)arg);
}


void * thr_fn1(void *arg)
{
    printf("[+] thread 1: start\n");
    pthread_cleanup_push(cleanup, (void *)"thread 1 first handler");
    pthread_cleanup_push(cleanup, (void *)"thread 1 second handler");
    printf("[+] thread 1: push complete\n");
    pause();
    if (arg) {
        return (void *)1;
    }
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    return (void *)1;
}


void * thr_fn2(void *arg)
{
    printf("[+] thread 2: start\n");
    pthread_cleanup_push(cleanup, (void *)"thread 2 first handler");
    pthread_cleanup_push(cleanup, (void *)"thread 2 second handler");
    printf("[+] thread 2: push complete\n");
    pause();
    if (arg) {
        return (void *)2;
    }
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    return (void *)2;
}

int main(void) {
    int err;
    pthread_t tid1, tid2;
    void *tret;

    if ((err = pthread_create(&tid1, NULL, thr_fn1, (void *)1)) != 0) {
        perror("[-] Error pthread_create 1");
        exit(1);
    }

    if ((err = pthread_create(&tid2, NULL, thr_fn2, (void *)1)) != 0) {
        perror("[-] Error pthread_create 2");
        exit(1);
    }


    if ((err = pthread_join(tid1, &tret)) != 0) {
        perror("[-] Error pthread_join 1");
        exit(1);
    }

    printf("[+] thread 1 exit code %ld\n", (long)tret);

    if ((err = pthread_join(tid2, &tret)) != 0) {
        perror("[-] Error pthread_join 2");
        exit(1);
    }
    printf("[+] thread 2 exit code %ld\n", (long)tret);

    pause();

    return 0;
}
