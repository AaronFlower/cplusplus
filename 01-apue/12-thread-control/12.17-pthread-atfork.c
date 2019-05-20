#include <stdio.h>
#include <unistd.h>     // for pid_t
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void *thr_fn(void *arg) {
    (void)arg;
    printf("\t[+] thread starting...\n");
    return 0;
}

void prepare(void) {
    printf("[+] Prepare locks...\n");

    if (pthread_mutex_lock(&mutex1) != 0) {
        perror("[-] Error can't lock mutex1 in prepare handler");
        exit(1);
    }

    if (pthread_mutex_lock(&mutex2) != 0) {
        perror("[-] Error can't lock mutex2 in prepare handler");
        exit(1);
    }
}

void parent(void)
{
    printf("[+] Parent unlocking ...\n");

    if (pthread_mutex_unlock(&mutex1)) {
        perror("[-] Error can't unlock mutex1 in parent handler");
        exit(1);
    }

    if (pthread_mutex_unlock(&mutex2)) {
        perror("[-] Error can't unlock mutex2 in parent handler");
        exit(1);
    }
}

void child(void)
{
    printf("[+] Child unlocking ...\n");

    if (pthread_mutex_unlock(&mutex1)) {
        perror("[-] Error can't unlock mutex1 in child handler");
        exit(1);
    }

    if (pthread_mutex_unlock(&mutex2)) {
        perror("[-] Error can't unlock mutex2 in child handler");
        exit(1);
    }
}

int main(void)
{
    int         err;
    pid_t       pid;
    pthread_t   tid;

    if ((err = pthread_atfork(prepare, parent, child)) != 0) {
        perror("[-] Error pthread_at ");
        exit(1);
    }

    if ((err = pthread_create(&tid, NULL, thr_fn, 0)) != 0) {
        perror("[-] Error pthread_create");
        exit(1);
    }

    if ((pid = fork()) < 0) {
        perror("[-] Error fork");
        exit(1);
    } else if (pid == 0) {
        printf("\t[+] child returned from fork\n");
    } else {
        printf("[+] Parent returned from fork\n");
    }
    return 0;
}
