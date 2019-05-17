#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>     // for sleep()

struct foo {
    int a, b, c, d;
};

void printFoo(struct foo *f) {
    printf("f->a: %d \n", f->a);
    printf("f->b: %d \n", f->b);
    printf("f->c: %d \n", f->c);
    printf("f->d: %d \n", f->d);
}

void *thr_fn1(void *arg) {
    (void)arg;

    struct foo f  = {1, 2, 3, 4};
    printFoo(&f);
    return (void *)&f; // ALE 直接会提醒的, 厉害。
}

int main(void)
{
    int err;
    pthread_t tid1;
    void *ret;

    if ((err = pthread_create(&tid1, NULL, &thr_fn1, NULL)) != 0) {
        perror("[-] Error pthread_create 1");
        exit(1);
    }


    err = pthread_join(tid1, &ret);
    if (err) {
        perror("[-] Error pthread_join");
        exit(1);
    }

    sleep(1);

    printFoo((struct foo *)ret);

    return 0;
}
