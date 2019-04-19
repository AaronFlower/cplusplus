#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2

/*
 *  create thread argument struct for thr_func()
 */
typedef struct _thread_data_t {
    int tid;
    double stuff;
} thread_data_t;

void *thr_fun(void *arg)
{
    thread_data_t *data = (thread_data_t *)arg;
    printf("Hello form thr_fun, thread id: %d \n", data->tid);
    pthread_exit(NULL);
}


int main()
{
    pthread_t thr[NUM_THREADS];
    thread_data_t thr_data[NUM_THREADS];
    int i, rc;

    // create threads
    for ( i = 0; i < NUM_THREADS; ++i) {
        thr_data[i].tid = i;
        if ((rc = pthread_create(&thr[i], NULL, thr_fun, &thr_data[i]))) {
            fprintf(stderr, "[-] Error : pthread_create , %d \n", rc);
            return EXIT_FAILURE;
        }
    }

    // block until all threads complete
    for (i = 0; i < NUM_THREADS; ++i) {
        pthread_join(thr[i], NULL);
    }
    return EXIT_SUCCESS;
}
