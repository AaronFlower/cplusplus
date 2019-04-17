#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCK_PATH "echo.soc"

/**
 * usage:
 *  ./11-unix-sokcet-server
 *  nc -U echo.soc
 */
int main(void)
{
    int listen_s, conn_s;
    int len, t;
    struct sockaddr_un local, remote;
    char str[100];

    if ((listen_s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("[-] Error socket ");
        exit(1);
    }


    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, SOCK_PATH);
    unlink(local.sun_path);
    len = strlen(local.sun_path) + sizeof(local.sun_family);

    if (bind(listen_s, (struct sockaddr *)&local, len) == -1) {
        perror("[-] Error bind ");
        exit(1);
    }

    if (listen(listen_s, 5) == -1) {
        perror("[-] Error listen ");
        exit(1);
    }

    for (;;) {
        int done, n;
        printf("Waiting for a connection ... \n");
        t = sizeof(remote);

        if ((conn_s = accept(listen_s, (struct sockaddr *)&remote, &t)) == -1) {
            perror("[-] Error accept");
            exit(1);
        }

        printf("Connected . \n");
        done = 0;
        do {
            n = recv(conn_s, str, 100, 0);
            if (n <= 0) {
                if (n < 0) {
                    perror("[-] Error recv");
                }
                done = 1;
            }
            if (!done) {
                if (send(conn_s, str, n, 0) < 0) {
                    perror("[-] Error send");
                    done = 1;
                }
            }
        } while(!done);
        close(conn_s);
    }
    close(listen_s);
    return 0;
}
