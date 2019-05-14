#include <stdio.h>      // for fprintf
#include <stdlib.h>     // for exit()
#include <unistd.h>     // for close(), read()
#include <sys/epoll.h>  // for epoll_create1(), epoll_ctl(), struct epoll_event
#include <string.h>     // for strncmp

#define MAX_EVENTS 5
#define READ_SIZE  10

int main(void)
{
    int running = 1, event_count, i;
    size_t bytes_read;
    char read_buffer[READ_SIZE + 1];

    // create epoll instance
    struct epoll_event event, events[MAX_EVENTS];
    int epoll_fd = epoll_create1(0);

    if (epoll_fd == -1) {
        perror("[-] Error epoll_fd");
        exit(1);
    }

    // Register fd
    event.events = EPOLLIN;
    event.data.fd = STDIN_FILENO;

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &event)) {
        perror("[-] Error epoll_ctl");
        close(epoll_fd);
        exit(1);
    }

    while (running) {
        printf("\n[+] Epoll: polling for input ... \n");
        event_count = epoll_wait(epoll_fd, events, MAX_EVENTS, 10000);
        printf("[+] Epoll: %d ready events \n", event_count);

        for (i = 0; i < event_count; ++i) {
            printf("[+] Epoll: Reading file descriptor '%d' -- ", events[i].data.fd);
            bytes_read = read(events[i].data.fd, read_buffer, READ_SIZE);
            printf("%zd bytes read.\n", bytes_read);
            read_buffer[bytes_read] = '\0';
            printf("Read '%s'\n", read_buffer);

            if (!strncmp(read_buffer, "quit\n", 5)) {
                running = 0;
            }
        }
    }


    if (close(epoll_fd)) {
        perror("[-] Error close");
        exit(1);
    }

    return 0;
}
