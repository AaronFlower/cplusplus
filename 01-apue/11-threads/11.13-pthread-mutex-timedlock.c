#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main(void) {
    int err;
    struct timespec tout;
    struct tm *tmp;
    char buf[64];

    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_lock(&lock);
    printf("[+] mutex is locked \n");

    clock_gettime(CLOCK_REALTIME, &tout);
    tmp = localtime(&tout.tv_sec);
    strftime(buf, sizeof(buf), "%r", tmp);
    printf("[+] current time is %s\n", buf);

    tout.tv_sec += 10;  // 10 seconds from now
    err = pthread_mutex_timedlock(&lock, &tout);

    clock_gettime(CLOCK_REALTIME, &tout);
    tmp = localtime(&tout.tv_sec);
    strftime(buf, sizeof(buf), "%r", tmp);
    printf("[+] the time is now %s \n", buf);

    if (err) {
        perror("[-] Error lock mutex again");
        exit(1);
    } else {
        printf("[+] mutex locked again \n");
    }

    return 0;
}
