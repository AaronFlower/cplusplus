#include <stdio.h>
#include <stdlib.h>
#include <errno.h>          // errno
#include <string.h>         // strerror
#include <sys/socket.h>
#include <netinet/in.h>

// fork, exec
#include <unistd.h>
#include <sys/types.h>

#define MAXLINE 4096

static int PORT = 8082;



void str_echo(int sock_fd) {
    size_t n;
    char buf[MAXLINE];

    again:
        while((n = read(sock_fd, buf, MAXLINE)) > 0) {
            write(sock_fd, buf, n);
        }
        if (n < 0 && errno == EINTR) {
            goto again;
        } else if (n < 0) {
            fprintf(stderr, "[-] socket error %s \n", strerror(errno));
            exit(1);
        }
}

int main(int argc, char *argv[])
{
    int listen_fd, conn_fd;
    pid_t child_pid;
    socklen_t cli_len;
    struct sockaddr_in cli_addr, serv_addr;

    if((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "[-] socket error %s \n", strerror(errno));
        exit(1);
    }

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);

    if(bind(listen_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        fprintf(stderr, "[-] Bind error %s \n", strerror(errno));
        exit(1);
    } 

    if(listen(listen_fd, 10) < 0) {
        fprintf(stderr, "[-] Listen error %s \n", strerror(errno));
        exit(1);
    }

    for (;;) {
        cli_len = sizeof(cli_addr);
        if((conn_fd = accept(listen_fd, (struct sockaddr*)&cli_addr, &cli_len)) < 0) {
            fprintf(stderr, "[-] Listen error %s \n", strerror(errno));
            exit(1);
        }

        if ((child_pid = fork()) == 0) {
            close(listen_fd);  // close listening socket.
            str_echo(conn_fd);
            exit(0);
        }
        close(conn_fd); 
    }
    return 0;
}
