#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

/**
 * Global constants
 */
#define PORT 80
#define LISTENQ 10          // number of connections

int listen_sock;            // listening socket

/**
 * struct to hold the return code and the filepath to serve to client.
 */
typedef struct {
    int return_code;
    char *filename;
} httpRequest;

/**
 * struct to hold variables that will be placed in shared memory.
 */
typedef struct {
    pthread_mutex_t mutexlock;
    int total_bytes;
} sharedVariables;

/**
 * headers to send to clients
 */
char *header_200 = "HTTP/1.0 200 OK\nServer: CS-Server v0.1\n Content-Type: text/html\n\n";
char *header_400 = "HTTP/1.0 400 Bad Request\nServer: CS-Server v0.1\n Content-Type: text/html\n\n";
char *header_404 = "HTTP/1.0 404 Not Found\nServer: CS-Server v0.1\n Content-Type: text/html\n\n";

/**
 * get a message from the socket until a blank line is received.
 */
char *getMessage(int fd) {
    // A file stream
    FILE *sstream;
    if ((sstream = fdopen(fd, "r")) == NULL) {
        fprintf(stderr, "[-] Error opening file descriptor in getMessage() \n");
        exit(EXIT_FAILURE);
    }

    // Size variable for passing to getline
    size_t size = 1;
    char *block;

    // Allocate some memory for block and check it went ok
    if ((block = malloc(sizeof(char) * size)) == NULL) {
        fprintf(stderr, "[-] Error allocating memory to block in getMessage() \n");
        exit(EXIT_FAILURE);
    }

    // Set block to null
    *block = '\0';

    // Allocate some memory for tmp and check if went ok
    char *tmp;
    if ((tmp = malloc(sizeof(tmp) * size)) == NULL) {
        fprintf(stderr, "[-] Error allocating memory to tmp in getMessage() \n");
        exit(EXIT_FAILURE);
    }
    *tmp = '\0';

    // Int to keep track of what getline returns
    int end;
    // Int to help use resize block
    int oldsize = 1;

    // while getline is still getting data
    while ((end = getline(&tmp, &size, sstream)) > 0) {
        // If the line its read is a carriage return and a new line were at the end of the header so break
        if (strcmp(tmp, "\r\n") == 0) {
            break;
        }

        // Resize block
        block = realloc(block, size + oldsize);

        // set the value of oldsize to the current size of block
        oldsize += size;
        // Append the lasted line we got to block
        strcat(block, tmp);
    }

    // Free tmp we no longer need if
    free(tmp);

    // Return the header
    return block;
}


// Extracts the filename needed from a Get Request and adds public_html to the front of it
char* getFileName(char* msg) {
    char* file;
    if ((file = malloc(sizeof(char) *strlen(msg))) == NULL) {
        fprintf(stderr, "[-] Error allocating memory to file in getFileName \n");
        exit(EXIT_FAILURE);
    }

    // Get the filename from the header
    sscanf(msg, "GET %s HTTP/1.1", file);

    char *base;
    if ((base = malloc(sizeof(char) * (strlen(file) + 18))) == NULL) {
        fprintf(stderr, "[-] Error allocating memory to base in getFileName \n");
        exit(EXIT_FAILURE);
    }

    char* ph = "public_html";

    strcpy(base, ph);
    strcat(base, file);
    free(file);
    return base;
}

// parse a HTTP request and return an object with return code and filename
httpRequest parseRequest(char *msg) {
    httpRequest ret;

    char* filename;

    if ((filename = malloc(sizeof(char) *strlen(msg))) == NULL) {
        fprintf(stderr, "[-] Error allocating memory to filename in parseRequest \n");
        exit(EXIT_FAILURE);
    }

    filename = getFileName(msg);
    fprintf(stdout, "filename = %s\n", filename);

    // Check if its a directory traversal attack
    char* traversalStr = "..";
    char* test = strstr(filename, traversalStr);

    if (test != NULL) {
        ret.return_code = 400;
        ret.filename = "400.html";
        return ret;
    }

    int test2 = strcmp(filename, "public_html/");
    if (test2 == 0) {
        ret.return_code = 200;
        ret.filename = "public_html/index.html";
        return ret;
    }

    FILE *exists = fopen(filename, "r");
    if (exists != NULL) {
        ret.return_code = 200;
        ret.filename = filename;
        return ret;
    }

    ret.return_code = 404;
    ret.filename = "404.html";

    return ret;
}

// clean up listening socket on ctrl-c
void cleanup (int sig) {
    (void)sig;
    printf("[+] Cleaning up connections and exiting.\n");

    // try to close the listening socket.
    if (close(listen_sock)) {
        fprintf(stderr, "[-] Error calling close()\n");
        exit(EXIT_FAILURE);
    }

    // Close the shared memroy we used.
    shm_unlink("/sharedmem");

    // exit with success
    exit(EXIT_SUCCESS);
}


// Send a message to a socket file descriptor.
int sendMessage(int fd, char *msg) {
    return write(fd, msg, strlen(msg));
}

int printHeader(int fd, int return_code) {
    switch (return_code) {
        case 200:
            sendMessage(fd, header_200);
            return strlen(header_200);
            break;

        case 400:
            sendMessage(fd, header_400);
            return strlen(header_400);
            break;
        case 404:
            sendMessage(fd, header_404);
            return strlen(header_404);
            break;
    }
}

int printFile(int fd, char *filename) {
    FILE *read;
    if ((read = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "[-] Error opening file in printFile\n");
        exit(EXIT_FAILURE);
    }

    struct stat st;
    stat(filename, &st);

    fprintf(stdout, "printFile name %s\n", filename);

    // Variable for getline to write the size of the line its currently printing to
    size_t size = 1;

    // Get some space to store each line of the file in temorarily
    char *temp;
    if ((temp = malloc(sizeof(char) *size)) == NULL) {
        fprintf(stderr, "[-] Error allocating memory to temp in printFile\n");
        exit(EXIT_FAILURE);
    }

    int end;
    while ((end = getline(&temp, &size, read)) > 0) {
        sendMessage(fd, temp);
    }
    sendMessage(fd, "\n");
    free(temp);
    return st.st_size;
}

int recordTotalBytes(int bytes_sent, sharedVariables *mempointer) {
    pthread_mutex_lock(&(*mempointer).mutexlock);
    (*mempointer).total_bytes += bytes_sent;
    pthread_mutex_unlock(&(*mempointer).mutexlock);
    return (*mempointer).total_bytes;
}


int main(int argc, char *argv[])
{
    int conn_s;                     // connection socket
    int port = PORT;
    struct sockaddr_in serv_addr;

    // set up handler for ctrl-c
    (void) signal(SIGINT, cleanup);


    // create the listening socket
    if ((listen_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "[-] Error creating listening socket.\n");
        exit(EXIT_FAILURE);
    }

    // set all bytes in socket address structure to zero, and fill in the relevant data members.
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);

    // bind to the socket address
    if (bind(listen_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0 ) {
       fprintf(stderr, "[-] Error calling bind(), errno is : %s\n", strerror(errno));
       exit(EXIT_FAILURE);
    }

    // Listen on socket listen_sock
    if (listen(listen_sock, 10) == -1) {
        fprintf(stderr, "[-] Error listening\n");
        exit(EXIT_FAILURE);
    }

    // Set up some shared memory to store our shared variables in

    // Close the shared memory we use just to be safe
    shm_unlink("/sharedmem");

    int sharedmem;

    // Open the memory
    if ((sharedmem = shm_open("sharedmem", O_RDWR | O_CREAT |O_EXCL, S_IRUSR |S_IWUSR)) == -1) {
        fprintf(stderr, "[-] Error opening sharedmem in main() errno is : %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Set the size of the shared memory to the size of my structure
    ftruncate(sharedmem, sizeof(sharedVariables));

    // Map the shared memory into our address space
    sharedVariables *mempointer;

    // Set mempointer to pointer at the shared memory
    mempointer = mmap(NULL, sizeof(sharedVariables), PROT_READ | PROT_WRITE, MAP_SHARED, sharedmem, 0);

    if (mempointer == MAP_FAILED) {
        fprintf(stderr, "[-] Error setting memory for sharedVariables in recordTotalBytes() error is %d \n", errno);
        exit(EXIT_FAILURE);
    }

    // Initialise the mutex
    pthread_mutex_init(&(*mempointer).mutexlock, NULL);
    // set total bytes sent to 0
    (*mempointer).total_bytes = 0;

    // Size of the address
    int addr_size = sizeof(serv_addr);

    // Size of data were sending out
    int header_size;
    int page_size;
    int total_size;

    // Number of child processed we have spawned
    int children = 0;
    // Variable to store the ID of the process we get when fork spawn
    pid_t pid;


    // Loop infinitly serving request
    while (1) {
        // If we havn't already spawned 10 children fork
        if (children <= 10) {
            pid = fork();
            children++;
        }

        // If the pid is -1 the fork failed so handle that
        if (pid == -1) {
            fprintf(stderr, "[-] Error can't fork, error %d \n", strerror(errno));
            exit(1);
        }

        // Have the child process deal with the connection
        while (pid == 0) {
            // Have the child loop infinetly dealing with a connection then getting the next one in the queue
            while (1) {
                // Accept a connection
                conn_s = accept(listen_sock, (struct sockaddr *)&serv_addr, &addr_size);

                // If something went wrong with accepting the connection deal with it
                if (conn_s == -1) {
                    fprintf(stderr, "[-] Error accepting connection \n");
                    exit(1);
                }

                // Get the message from the file descriptor
                char *header = getMessage(conn_s);

                // Parse the request
                httpRequest details = parseRequest(header);
                free(header);

                header_size = printHeader(conn_s, details.return_code);
                page_size = printFile(conn_s, details.filename);
                total_size = recordTotalBytes(header_size + page_size, mempointer);
                printf("[+] Process %d served a request of %d bytes. Total bytes sent %d \n", header_size + page_size, total_size);
                close(conn_s);
            }
        }
        //
    }

    return 0;
}
