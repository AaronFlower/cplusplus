#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>          // inet_pton
#include <netinet/in.h>         // htons

#include <errno.h>
#include <string.h>


#define PORT 8082
#define MAXLINE 4096

void str_cli(FILE *fp, int sock_fd) {
    char send_line[MAXLINE], recv_line[MAXLINE];

    while(fgets(send_line, MAXLINE, fp) != NULL) {
        send(sock_fd, send_line, strlen(send_line), 0);
        /* writen(sock_fd, send_line, strlen(send_line)); */
        if (recv(sock_fd, recv_line, MAXLINE, 0) < 0) {
            printf("[-] str_cli: server terminated prematurely");
            exit(1);
        }
        fputs(recv_line, stdout);
    }
}

int main(int argc, char *argv[])
{
    int sock_fd;
    struct sockaddr_in serv_addr;

    if (argc != 2) {
        printf("[-] usage: client <ip> \n");
        exit(1);
    }

    if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("[-] socket error: %s\n", strerror(errno));
        exit(1);
    }

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) < 0) {
        printf("[-] inet_pton error: %s\n", strerror(errno));
        exit(1);
    }

    if (connect(sock_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        printf("[-] connect error: %s\n", strerror(errno));
        exit(1);
    }

    str_cli(stdin, sock_fd);
    exit(0);
}
