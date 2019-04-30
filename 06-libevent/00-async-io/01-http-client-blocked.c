#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <netinet/in.h>  // sockaddr_in
#include <sys/socket.h>  // for sockets func
#include <netdb.h>       // gethostbyname

int main(void)
{
    const char query[] =
        "GET / HTTP/1.0\r\n"
        "HOST: localhost\r\n"
        "\r\n";

    const char hostname[] = "localhost";

    struct sockaddr_in sin;
    struct hostent *h;
    const char *cp;
    int fd;

    ssize_t n_written, remaining;
    char buf[1024];

    /* Look up the IP address for the hostname. Watch out; this isn't threadsafe on most platforms. */
    h = gethostbyname(hostname);
    if (!h) {
        fprintf(stderr, "[-] Error: couldn't lookup %s: %s\n", hostname, hstrerror(h_errno));
        return 1;
    }

    if (h->h_addrtype != AF_INET) {
        fprintf(stderr, "No ipv6 support, sorry.\n");
        return 1;
    }

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("[-] Error socket: ");
        exit(1);
    }


    /* Connet to the remote host. */
    sin.sin_family = AF_INET;
    sin.sin_port = htons(8080);
    sin.sin_addr = *(struct in_addr *)h->h_addr;
    if (connect(fd, (struct sockaddr*) &sin, sizeof(sin))) {
        perror("[-] Error connect");
        close(fd);
        exit(1);
    }

    /* Write the query. */
    cp = query;
    remaining = strlen(query);

    while(remaining) {
        n_written = send(fd, cp, remaining, 0);
        if (n_written <= 0) {
            perror("[-] Error send");
            exit(1);
        }
        remaining -= n_written;
        cp += n_written;
    }

    /* Get an answer back. */
    while (1) {
        ssize_t result = recv(fd, buf, sizeof(buf), 0);
        if (result == 0) {
            break;
        } else if (result < 0) {
            perror("[-] Error recv");
            close(fd);
            exit(1);
        }
        fwrite(buf, 1, result, stdout);
    }
    close(fd);
    return 0;
}
