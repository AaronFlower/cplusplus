#include <stdio.h>
#include <stdlib.h> // for exit(), timespec
#include <pthread.h>

#define USEC_TO_NSECS   1000000         // microseconds to nanoseconds
#define SEC_TO_NSECS    1000000000      // seconds to nanoseconds

typedef struct to_info {
    void            (*to_fn)(void *);   // function
    void            *to_arg;            // argument
    struct timespec to_wait;            // time to wait
} to_info;

pthread_mutexattr_t attr;
pthread_mutex_t mutex;

int make_thread(void *(*fn)(void *), void *arg) {
    int             err;
    pthread_t       tid;
    pthread_attr_t  attr;

    err = pthread_attr_init(&attr);
    if (err != 0) {
        perror("[-] Error pthread_attr_init");
        return err;
    }

    err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (err == 0) {
        err = pthread_create(&tid, &attr, fn, arg);
    }

    pthread_attr_destroy(&attr);
    return err;
}

void *timeout_helper(void *arg) {
    to_info *tip = (to_info *)arg;
    clock_nanosleep(CLOCK_REALTIME, 0, &tip->to_wait, NULL);
    (*tip->to_fn)(tip->to_arg);
    free(arg);
    return 0;
}

void timeout(const struct timespec *when, void(*func)(void *), void *arg) {
    struct timespec now;
    struct to_info *tip;
    int err;

    printf("[+] timeout \n");
    if ((err = clock_gettime(CLOCK_REALTIME, &now)) != 0) {
        perror("[-] Error clock_gettime");
        exit(1);
    }

    if ((when->tv_sec > now.tv_sec) || 
        (when->tv_sec == now.tv_sec && when->tv_nsec > now.tv_nsec)) {
        tip = (to_info *)malloc(sizeof(struct to_info));
        
        if (tip != NULL) {
            tip->to_fn = func;
            tip->to_arg = arg;
            tip->to_wait.tv_sec = when->tv_sec - now.tv_sec;
            if (when->tv_nsec >= now.tv_nsec) {
                tip->to_wait.tv_nsec = when->tv_nsec - now.tv_nsec;
            } else {
                tip->to_wait.tv_sec--;
                tip->to_wait.tv_nsec = SEC_TO_NSECS - now.tv_nsec + when->tv_nsec;
            }
            if ((err = make_thread(timeout_helper, (void *)tip)) != 0) {
                perror("[-] Error make_thread");
                exit(1);
                
                free(tip);
            } else {
                return;
            }
        } else {
            perror("[-] Error malloc");
            exit(1);
        }
    } 

    (*func)(arg);
}

void retry(void *arg) {
    (void)arg;
    pthread_mutex_lock(&mutex);
    printf("[+] Retry...\n");
    /* perform retry steps ... */
    pthread_mutex_unlock(&mutex);
}

int main(void) {
    int err, condition = 1, arg = 1;
    struct timespec when;

    if ((err = pthread_mutexattr_init(&attr)) != 0) {
        perror("[-] Error pthread_mutexattr_init ");
        exit(1);
    }

    if ((err = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE)) != 0) {
        perror("[-] Error pthread_mutexattr_settype ");
        exit(1);
    }

    if ((err = pthread_mutex_init(&mutex, &attr)) != 0) {
        perror("[-] Error pthread_mutex_init");
        exit(1);
    }
    
    /* continue processing ... */
    pthread_mutex_lock(&mutex);

    /*
     * Check the condition under the protection of a lock to make the check and the call 
     * to timeout atomic.
     */
    if (condition) {
        // Calculate the absolute time when we want to retry.
        printf("[+] set timeout\n");
        if ((err = clock_gettime(CLOCK_REALTIME, &when)) != 0) {
            perror("[-] Error clock_gettime");
            exit(1);
        }
        when.tv_sec += 10;  // 10 seconds from now.
        timeout(&when, retry, (void *)((unsigned long)arg));
    }
    pthread_mutex_unlock(&mutex);

    /* continue processing ... */
    return 0;
}
