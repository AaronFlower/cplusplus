#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <netinet/in.h>      // sockaddr_in
#include <sys/socket.h>
#include <signal.h>          // for signal to avoid zombie process

#define MAX_LINE 16384
#define PORT 8082

char rot13(char c)
{
    if ((c >= 'a' && c <= 'm') || ('c' >= 'A' && c <= 'M')) {
        return c + 13;
    } else if  ((c >= 'n' && c <= 'z') || ('c' >= 'N' && c <= 'Z')) {
        return c - 13;
    } else {
        return c;
    }
}

void child(int fd)
{
    char outbuf[MAX_LINE + 1];
    size_t outbuf_used = 0;
    ssize_t result;

    while (1) {
        char ch;
        result = recv(fd, &ch, 1, 0);
        if (result == 0) {
            break;
        } else if (result == -1) {
            perror("[-] Error recv");
            break;
        }

        if (outbuf_used < sizeof(outbuf)) {
            outbuf[outbuf_used++] = rot13(ch);
        }
        if (ch == '\n') {
            send(fd, outbuf, outbuf_used, 0);
            outbuf_used = 0;
            continue;
        }
    }
}

void run()
{
    int l;
    struct sockaddr_in sin;

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(PORT);

    l = socket(AF_INET, SOCK_STREAM, 0);

    if (bind(l, (struct sockaddr *)&sin, sizeof(sin))) {
        perror("[-] Error bind");
        exit(1);
    }

    if (listen(l, 16) < 0) {
        perror("[-] Error listen");
        exit(1);
    }

    signal(SIGCHLD, SIG_IGN);

    while (1) {
        struct sockaddr_storage ss;
        socklen_t slen = sizeof(ss);

        int fd = accept(l, (struct sockaddr*)&ss, &slen);
        if (fd < 0) {
            perror("[-] Error accpet");
            continue;
        }
        int pid;

        if ((pid = fork()) < 0) {
            perror("[-] Error fork");
            exit(1);
        } else if (pid == 0) {
            close(l);
            child(fd);
            exit(0);
        }
        close(fd);
    }
}

int main(void)
{
    run();
    return 0;
}
