#include <stdio.h>      // for fprintf
#include <stdlib.h>     // for exit()
#include <unistd.h>     // for close()
#include <sys/epoll.h>
#include <string.h>     // for strncmp


#define BUF_SIZE 10
#define MAX_EVENTS 5


int main(void)
{
    int running = 1, ecount, i;
    size_t nbytes, j;
    char buf[BUF_SIZE + 1];
    struct epoll_event event, events[MAX_EVENTS];
    int epfd, fd;
    if ((epfd = epoll_create1(0)) < 0) {
        perror("[-] Error epoll_create1");
        exit(1);
    }

    event.events = EPOLLIN | EPOLLET;
    event.data.fd = STDIN_FILENO;

    if (epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event) < 0) {
        perror("[-] Error epoll_ctl");
        exit(1);
    }

    while (running) {
        printf("\n[+] Epoll: polling for input... \n");
        ecount = epoll_wait(epfd, events, MAX_EVENTS, 10000);

        if (ecount < 0) {
            perror("[-] Error epoll_wait");
            exit(1);
        } else if (ecount > 0) {
           printf("[+] Epoll: %d is ready -- ", ecount);
           for (i = 0; i < ecount; ++i) {
                fd = events[i].data.fd;
                nbytes = read(fd, buf, BUF_SIZE);
                printf("%zd bytes read.\n", nbytes);
                /* for (j = 0; j < nbytes; ++j) { */
                /*     printf(" %zd : %d\n", j, buf[j]); */
                /* } */
                /* printf("\n"); */
                buf[nbytes] = '\0';
                printf("[+] Read: '%s' \n", buf);
                if (!strncmp(buf, "quit\n", 5)) {
                    running = 0;
                }
           }
        } else {
            printf("waiting you input...\n");
        }
    }

    if (close(epfd)) {
        perror("[-] Error close");
        exit(1);
    }
    return 0;
}
