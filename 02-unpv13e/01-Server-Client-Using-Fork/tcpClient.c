#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 9091

int main()
{
    int clientSocket, ret;
    struct sockaddr_in serverAddr;
    char buffer[1024];

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientSocket < 0) {
        printf("[-] Error in connection.\n");
    }
    printf("[+] Client Socket is created.\n");

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    if (ret < 0) {
        printf("[-] Error in connection.\n");
        exit(1);
    }
    printf("[+] Connection to Server.\n");

    while (1) {
        printf("Client: \n");
        scanf("%s", &buffer[0]);
        send(clientSocket, buffer, strlen(buffer), 0);

        if (strcmp(buffer, ":exit") == 0) {
            close(clientSocket);
            printf("[-] Disconnected from server.\n");
            exit(0);
        }

        if (recv(clientSocket, buffer, 1024, 0) < 0) {
            printf("[-] Error in receiving data.\n");
        } else {
            printf("\t%s\n", buffer);
        }
    }

    return 0;
}
