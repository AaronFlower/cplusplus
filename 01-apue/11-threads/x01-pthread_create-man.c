#include <stdio.h>
#include <stdlib.h>         // for exit(), calloc()
#include <pthread.h>        // for threads
#include <string.h>         // for strdup()
#include <ctype.h>          // for toupper
#include <unistd.h>         // for optarg, getopt


typedef struct thread_info {
    pthread_t tid;  // ID returned by pthread_create()
    int num;        // User-defined thread nubmer
    char *argv;     // from command-line argument
} tinfo;

/*
 * Thread start function: display address near top of our stack and
 * return return upper-cased copy of argv
 */
static void *thread_start(void *arg) {
    tinfo *tif = (tinfo *)arg;
    char *p, *str;

    printf("Thread %d: top of stack near %p; arg = %s \n",
           tif->num, &p, tif->argv);

    if ((str = strdup(tif->argv)) == NULL) {
        perror("[-] Error strdup");
        exit(1);
    }

    for (p = str; *p != '\0'; ++p) {
        *p = toupper(*p);
    }
    return str;
}


int main(int argc, char *argv[]) {
    int s, tnum, opt, num_threads;
    tinfo *tif;

    pthread_attr_t attr;
    int stack_size;
    void *res;

    /* The "-s" option specifies a stack size fo our threads */
    stack_size = -1;
    while ((opt = getopt(argc, argv, "s:")) != -1) {
        switch (opt) {
            case 's':
                // optarg is defeind in unistd.h by `extern char *optarg` 
                stack_size = strtoul(optarg, NULL, 0);
                break;
            default:
                printf("\n");
        }
    }

    num_threads = argc - optind;

    // Initialize thread creation attributes
    if ((s = pthread_attr_init(&attr)) != 0) {
        perror("[-] Error pthread_attr_init");
        exit(1);
    }

    if (stack_size > 0) {
        if (( s = pthread_attr_setstacksize(&attr, stack_size)) != 0) {
            perror("[-] Error pthread_attr_setstacksize");
            exit(1);
        }
    }

    tif = (tinfo *)calloc(num_threads, sizeof(tinfo));
    
    if (!tif) {
        perror("[-] Error calloc");
        exit(1);
    }

    // create one thread for each command-line argument.
    for (tnum = 0; tnum < num_threads; ++tnum) {
        tif[tnum].num = tnum + 1;
        tif[tnum].argv = argv[optind + tnum];

        s = pthread_create(&tif[tnum].tid, &attr, &thread_start, tif + tnum);
        if (s) {
            perror("[-] Error pthread_create");
            exit(1);
        }
    }

    s = pthread_attr_destroy(&attr);
    if (s != 0) {
        perror("[-] Error pthread_attr_destroy");
        exit(1);
    }


    /* Now join with each thread, and display its returnd value */

    for (tnum = 0; tnum < num_threads; ++tnum) {
        s = pthread_join(tif[tnum].tid, &res);
        if (s != 0) {
            perror("[-] Error pthread_join");
            exit(1);
        }
        printf("Joined with thread %d; returned value was %s\n", tif[tnum].num, (char *)res);
        free(res);      // Free memory allocated by strdup in thread
    }
    free(tif);
    return 0;
}
