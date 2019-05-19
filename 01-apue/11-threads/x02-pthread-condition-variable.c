/**
 * An exmaple of using pthread's condition variables,
 * showing how to block a main thread while waiting
 * for worker threads to finish joining the threads.
 * This could be useful if you want to loop the threads, for example.
 *
 * https://gist.github.com/rtv/4989304
 */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>         // for exit(1);
#include <unistd.h>         // for sleep()

const size_t num_threads = 5;

/* A global count of the number of threads finished working. It will be
 * protected by mutex and changes to it will be signalled to the
 * main thread via cond
 */

int done;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void * thread_entry(void *arg) {
    int num = *(int *)arg;

    int i, err;
    const int workloops = 2;
    /* unsigned long id = (unsigned long)pthread_self(); */
    // simulate doing some costly work
    for (i = 0; i < workloops; ++i) {
        printf("\t\t[+] Thread %d working (%d/%d) \n", num, i, workloops );
        sleep(1);
    }

    // we're going to manipulate done and use the cond, so we need the mutex.
    if ((err = pthread_mutex_lock(&lock)) != 0) {
        perror("[-] Error lock");
        exit(1);
    }
    ++done;
    printf("\t\t[+] Thread %d done is now %d. Signalling cond. \n", num, done);

    // to singal main thread, main thread will try to re-aquire the lock so we need to unlock.
    if ((err = pthread_mutex_unlock(&lock)) != 0) {
        perror("[-] Error unlock");
        exit(1);
    }

    // wait up the main thread (if it is sleeping) to test the value of done.
    if ((err = pthread_cond_signal(&cond)) != 0) {
        perror("[-] Error signal");
        exit(1);
    }

    // 上面的 signal, unlock 的调用顺序应该是随意的。
    // 1. signal -> unlock, 先通知 main, main 会尝试再次加锁，所以我们要 unlock
    // 2. unlock->signal, 先 unlock , 再 signal 通知 main, main 刚好唤醒时同时获得锁.

    return NULL;
}

int main(void) {
    int err;
    size_t i;
    size_t nums[num_threads];
    puts("[+] thread main starting ");
    pthread_t threads[num_threads];

    for (i = 0; i < num_threads; ++i) {
        nums[i] = i;
        pthread_create(&threads[i], NULL, thread_entry, nums + i);
    }

    // we're going to test "done", so we need the mutex for safety.
    if ((err = pthread_mutex_lock(&lock)) != 0) {
        perror("[-] Error lock");
        exit(1);
    }

    // are the other threads still busy?
    while (done < (int)num_threads) {
        printf("[+] thread main : done is %d which is < %d so waiting on cond \n",
                done, (int)num_threads);
        /* block this thread until another thread signals cond.
         * While blocked, the mutex is released, then re-aquired
         * before this thread is woken up and the call returns.
         */
        if ((err = pthread_cond_wait(&cond, &lock)) != 0) {
            perror("[-] Error cond wait");
            exit(1);
        }
        
        puts("\t[+] thread main: wake - cond was signalled.");
    }

    printf("\n[+] thread main: done == %d so everyone is done \n", (int)num_threads);
    pthread_mutex_unlock(&lock);
    return 0;
}
