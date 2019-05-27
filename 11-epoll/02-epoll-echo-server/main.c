#include <stdio.h>
#include <stdlib.h>         // for exit, calloc
#include <unistd.h>         // for close
#include <sys/socket.h>     // for socket, bind, listen, accept
#include <arpa/inet.h>      // for socklen_t, inet_ntop
#include <netinet/in.h>     // (in)ternet for sockadd_in
#include <string.h>         // for bzero
#include <errno.h>          // for errno
#include <fcntl.h>          // fcntl
#include <sys/epoll.h>      // epoll_create1, epoll_ctl, epoll_wait



#define PORT        8083
#define BUF_SIZE    32
#define MAX_EVENTS  64
#define MILLISECOND 1000
#define MAX_FD      128     // Only for test

// create socket and bind
int create_bind_sock () {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        perror("[-] Error socket");
        exit(1);
    }

    struct sockaddr_in sa;                          //sockaddr_in 后缀 in 是 internet 的意思
    bzero(&sa, sizeof sa);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(PORT);
    sa.sin_addr.s_addr =  htonl(INADDR_ANY);         // s_addr 成员是一个大端 32 整数

    if (bind(s, (struct sockaddr*)&sa, sizeof sa) != 0) {
        perror("[-] Error bind");
        exit(1);
    }
    return s;
}


// make a nonblocking fd
void make_fd_nonblocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) {
        perror("[-] Error fcntl F_GETFL ");
        exit(1);
    }

    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("[-] Error fcntl F_GETFL ");
        exit(1);
    }
}

int main()
{
    int sock_fd, in_fd, fd;
    struct sockaddr_in sa;
    socklen_t len;
    int ep_fd;
    struct epoll_event event, *events;
    int ecount, i;
    char host_buf[INET_ADDRSTRLEN], buf[BUF_SIZE];
    int n_bytes;
    char map[MAX_FD];
    char *greeting = "[+] Server: Welcome, kid!\n";
    char *msg = "[+] Server: It's echo from server!\n";
    char *send;

    bzero(map, sizeof(map));

    sock_fd = create_bind_sock();

    make_fd_nonblocking(sock_fd);

    if (listen(sock_fd, 10) < 0) {
        perror("[-] Error Listen");
        exit(1);
    }

    if ((ep_fd = epoll_create1(0)) < 0) {
        perror("[-] Error epoll_create1");
        exit(1);
    }


    event.data.fd = sock_fd;
    event.events = EPOLLET | EPOLLIN;
    if (epoll_ctl(ep_fd, EPOLL_CTL_ADD, sock_fd, &event) < 0) {
        perror("[-] Error epoll_ctl");
        exit(1);
    }

    // Allocate and zero-initialize array
    events = (struct epoll_event *)calloc(MAX_EVENTS, sizeof event);
    printf("sock_fd = %d, ep_fd = %d\n", sock_fd, ep_fd);

    while (1) {
        ecount = epoll_wait(ep_fd, events, MAX_EVENTS, 10 * MILLISECOND);

        if (ecount == 0) {
            printf("The server is epoll waiting... \n");
        }

        for (i = 0; i < ecount; ++i) {
            /* printf("count ready %d, %d\n", ecount, events[i].data.fd); */
            // error or hang up
            if (events[i].events & (EPOLLERR | EPOLLHUP)) {
                perror("[-] Error poll_wait ");
                close(events[i].data.fd);
                continue;
            }

            if (events[i].events & EPOLLIN) {
                // EPOLLIN
                if (sock_fd == events[i].data.fd) {
                    // has new connection,有新的客户端连接进来，将新的链接设置成 NON_BLOCKING,
                    // 并且加入到 epoll , 用 while 保证 ET 时会取完，用 break 跳出 while
                    while (1) {
                        len = sizeof(sa);
                        in_fd = accept(sock_fd, (struct sockaddr *)&sa, &len);
                        if (in_fd < 0) {
                            if (errno != EAGAIN && errno == EWOULDBLOCK) {
                                // sock_fd is not ready
                                perror("[-] Error accept (EAGAIN or EWOULDBLOCK)");
                            }
                            break;
                        }

                        inet_ntop(AF_INET, &sa.sin_addr, host_buf, sizeof host_buf);
                        printf("[+] Accept: connection on descriptor %d "
                                "(host = %s, port = %d) \n", in_fd, host_buf, sa.sin_port);

                        make_fd_nonblocking(in_fd);

                        event.data.fd = in_fd;
                        event.events = EPOLLET | EPOLLOUT;   // for a new in_fd that it's read to write
                        if (epoll_ctl(ep_fd, EPOLL_CTL_ADD, in_fd, &event) < 0) {
                            perror("[-] Error epoll_ctl");
                            exit(1);
                        }
                    } // while
                } else {
                    // 连接的 socket 有数据, ET 触发，用 while 保证取完，用 break 跳出 while
                    // 数据读取完成后，将 events 类型设置为 EPOLLOUT
                    int j = 0;
                    while (1) {
                        n_bytes = read(events[i].data.fd, buf, BUF_SIZE - 1);
                        if (n_bytes == -1) {
                            if (errno == EAGAIN) {
                                event.data.fd = events[i].data.fd;
                                event.events = EPOLLOUT | EPOLLET;
                                epoll_ctl(ep_fd, EPOLL_CTL_MOD, events[i].data.fd, &event);
                            } else {
                                perror("[-] Error read fd");
                                exit(1);
                            }
                            break;
                        } else if (n_bytes == 0) {
                            // EOF
                            printf("[-] The client has been closed \n");
                            close(events[i].data.fd);
                            printf("[-] Closed connection on descriptor %d\n", events[i].data.fd);
                            break;
                        }

                        fprintf(stdout, "[-] while read (%d, %d bytes): %s \n", j++, n_bytes, buf);
                    }
                }
            } else if(events[i].data.fd & EPOLLOUT) {
                fd = events[i].data.fd;
                if (fd != sock_fd) {
                    send = map[fd] == 0 ? greeting : msg;
                    map[fd] = 1;

                    if(write(fd, send, strlen(send)) < 0) {
                        perror("[-] Error write to client");
                        exit(1);
                    }

                    // 为什么还要修改那？
                    event.data.fd = fd;
                    event.events = EPOLLET | EPOLLIN;
                    epoll_ctl(ep_fd, EPOLL_CTL_MOD, fd, &event);
                }
            }
        } // for
    } // while

    free(events);
    close(sock_fd);
    close(ep_fd);
    return 0;
}
