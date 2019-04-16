/**
getip.c - Simple command line utility to list ips of a given host.
*/

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

// Gets the IPs for the host
int getIp(char* host)
{
    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // Use IPv4 and IPv6
    hints.ai_socktype = SOCK_STREAM; // Use a TCP stream socket

    if ((status = getaddrinfo(host, NULL, &hints, &res)) != 0)
    {
        // Error
        fprintf(stderr, "Error in getaddrinfo: %s\n", gai_strerror(status));
        return 1;
    }

    printf("\nIP addresses for %s:\n\n", host);

    // Get the IPs
    for (p = res; p != NULL; p = p->ai_next)
    {
        void *addr;
        char *ipver;

        // Handle IPv4 Address
        if (p->ai_family == AF_INET)
        {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        }
        // Handle IPv6 Address
        else
        {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }

        // Convert the IP from binary to string and print
        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        printf("\t%s: %s\n", ipver, ipstr);
    }

    // Trailing newline for legibility
    printf("\n");

    freeaddrinfo(res);
    return 0;
}

// The main run loop
int main(int argc, char *argv[])
{
    // Check the command line arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: getip [hostname]\n");
        return 1;
    }

    getIp(argv[1]);
    return 0;
}
