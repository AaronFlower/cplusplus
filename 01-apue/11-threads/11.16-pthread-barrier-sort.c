#include <stdio.h>
#include <stdlib.h>     // for qsort(), srand(), rand()
#include <pthread.h>
#include <limits.h>     // for LONG_MAX
#include <sys/time.h>   // for gettimeofday()

#define NUM_THREADS         1                       // number of threads
#define NUM_NUM             8000000L                // number of numbers to sort
#define NUM_PER_SORT        (NUM_NUM / NUM_THREADS) // number of sort per thread

long nums[NUM_NUM];
long snums[NUM_NUM];

pthread_barrier_t b;

/*
 * Compare two long integers
 */
int complong(const void *arg1, const void *arg2) {
    long l1 = *(long *)arg1;
    long l2 = *(long *)arg2;

    return l1 - l2;
}

/*
 * Worker thread to sort a portion of the set of numbers.
 */
void *thread_entry(void *arg) {
    long idx = (long)arg;
    qsort(nums + idx, NUM_PER_SORT, sizeof(long), complong);
    pthread_barrier_wait(&b);
    // Go off and perform more work...
    return (void *)0;
}

/* 
 * Merge the results of the individual sorted ranges
 */
void merge() {
    long idx[NUM_THREADS];
    long i, min_idx, sort_idx, num; 

    for (i = 0; i < NUM_THREADS; ++i) {
        idx[i] = i * NUM_PER_SORT;
    }

    for (sort_idx = 0; sort_idx < NUM_NUM; ++sort_idx) {
        num = LONG_MAX;
        for (i = 0; i < NUM_THREADS; ++i) {
            if ((idx[i] < (i + 1) * NUM_PER_SORT) && (nums[idx[i]] < num)) {
                num = nums[idx[i]];
                min_idx = i;
            }
        }
        snums[sort_idx] = nums[idx[min_idx]];
        ++idx[min_idx];
    }
}

int main(void) {
    unsigned int i;
    struct timeval start, end;
    long long start_usec, end_usec;
    double elapsed;
    int err;
    pthread_t tid;

    // create the initial set of numbers to sort.
    srand(1);
    for (i = 0; i < NUM_NUM; ++i) {
        nums[i] = random();
    }

    // create NUM_THREADS threads to sort the numbers
    gettimeofday(&start, NULL);

    pthread_barrier_init(&b, NULL, NUM_THREADS + 1);
    for (i = 0; i < NUM_THREADS; ++i) {
        err = pthread_create(&tid, NULL, thread_entry, (void *)(i * NUM_PER_SORT));
        if (err != 0) {
            perror("[-] Error pthread_create");
            exit(1);
        }
    }
    pthread_barrier_wait(&b);
    merge();

    gettimeofday(&end, NULL);

    start_usec = start.tv_sec * 1000000 + start.tv_usec;
    end_usec = end.tv_sec * 1000000 + end.tv_usec;
    elapsed = (double)(end_usec - start_usec) / 1000000.0;

    printf("sort took %.4f seconds \n", elapsed);
    for (i = 0; i < NUM_NUM; ++i) {
        printf("%ld\n", snums[i]);
    }

    return 0;
}
