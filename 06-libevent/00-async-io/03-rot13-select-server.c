/**
 * Here's a reimplementation of our ROT13 server, using select() this time.
 */
#include <netinet/in.h>  // for sockaddr_in
#include <sys/socket.h>  // for socket functions
#include <fcntl.h>       // for fcntl
#include <sys/select.h>  // for select


#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define MAX_LINE 16384
#define PORT 8082

char rot13_char(char c) {
    /* We don't want to use isalpha here; setting the locale would change
     * which characters are considered alphabetical. */
    if ((c >= 'a' && c <= 'm') || (c >= 'A' && c <= 'M'))
        return c + 13;
    else if ((c >= 'n' && c <= 'z') || (c >= 'N' && c <= 'Z'))
        return c - 13;
    else
        return c;
}

typedef struct fd_state {
    char buffer[MAX_LINE];
    size_t buffer_used;

    int writing;
    size_t n_written;
    size_t write_upto;
} fd_state;

// alloc a fd_state
fd_state *alloc_fd_state(void) {
    fd_state *state = (fd_state *)malloc(sizeof(fd_state));
    if (!state) return NULL;

    state->buffer_used = 0;
    state->writing = 0;
    state->n_written = 0;
    state->write_upto = 0;
    return state;
}


// free a fd_state
void free_fd_state(fd_state *state) {
    free(state);
}

// nonblocking socket
void make_nonblocking(int fd) {
    fcntl(fd, F_SETFL, O_NONBLOCK);
}

int do_read(int fd, fd_state *state) {
    printf("do_read %d\n", fd);
    char buf[1024];
    int i;
    ssize_t result;

    while (1) {
        result = recv(fd, buf, sizeof(buf), 0);

        if (result <= 0) {
            break;
        }

        for (i = 0; i < result; ++i) {
            if (state->buffer_used < sizeof(state->buffer)) {
                state->buffer[state->buffer_used++] = rot13_char(buf[i]);
            }

            if (buf[i] == '\n') {
                state->writing = 1;
                state->write_upto = state->buffer_used;
            }
        }
    }

    if (result == 0) {
        return 1;
    } else if (result < 0) {
        if (errno == EAGAIN) {
            return 0;
        }
        return -1;
    }
    return 0;
}

int do_write(int fd, fd_state *state) {
    printf("do_write %d\n", fd);
    while (state->n_written < state->write_upto) {
        ssize_t result = send(fd, state->buffer + state->n_written, state->write_upto - state->n_written, 0);

        if (result < 0) {
            if (errno == EAGAIN) {
                return 0;
            }
            return -1;
        }
        assert(result != 0);
        state->n_written += result;
    }

    if (state->n_written == state->buffer_used) {
        state->n_written = state->write_upto = state->buffer_used = 0;
    }
    state->writing = 0;
    return 0;
}

void run(void) {
    int listener;

    // FD_SETSIZE defines the Number of descriptors that can fit in an `fd_set'. 1024
    fd_state *state[FD_SETSIZE];

    struct sockaddr_in sin;
    int i, maxfd;

    // fd_set 是根据 FD_SETSIZE 定义一个 bit 位类型。
    fd_set readset, writeset, exset;

    sin.sin_family = AF_INET;
    // INADDR_ANY don't bind socket to a specific IP.
    // The socket accepts connections to all the IPs of the machine.
    // 多宿主机，multi-hosted , 因为有无线、有线、wifi, 4G 等，IP 是不同的。
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(PORT);

    for (i = 0; i < FD_SETSIZE; ++i)
        state[i] = NULL;

    listener = socket(AF_INET, SOCK_STREAM, 0);
    make_nonblocking(listener);

    if (bind(listener, (struct sockaddr*)&sin, sizeof(sin)) < 0) {
        perror("bind");
        return;
    }

    if (listen(listener, 16)<0) {
        perror("listen");
        return;
    }

    FD_ZERO(&readset);
    FD_ZERO(&writeset);
    FD_ZERO(&exset);

    while (1) {
        maxfd = listener;

        FD_ZERO(&readset);
        FD_ZERO(&writeset);
        FD_ZERO(&exset);

        FD_SET(listener, &readset);

        for (i=0; i < FD_SETSIZE; ++i) {
            if (state[i]) {
                if (i > maxfd)
                    maxfd = i;
                FD_SET(i, &readset);
                if (state[i]->writing) {
                    FD_SET(i, &writeset);
                }
            }
        }

        if (select(maxfd+1, &readset, &writeset, &exset, NULL) < 0) {
            perror("select");
            return;
        }

        if (FD_ISSET(listener, &readset)) {
            struct sockaddr_storage ss;
            socklen_t slen = sizeof(ss);
            int fd = accept(listener, (struct sockaddr*)&ss, &slen);
            if (fd < 0) {
                perror("accept");
            } else if (fd > FD_SETSIZE) {
                close(fd);
            } else {
                make_nonblocking(fd);
                state[fd] = alloc_fd_state();
                assert(state[fd]);/*XXX*/
            }
        }

        for (i=0; i < maxfd+1; ++i) {
            int r = 0;
            if (i == listener)
                continue;

            if (FD_ISSET(i, &readset)) {
                r = do_read(i, state[i]);
            }
            if (r == 0 && FD_ISSET(i, &writeset)) {
                r = do_write(i, state[i]);
            }
            if (r) {
                free_fd_state(state[i]);
                state[i] = NULL;
                close(i);
            }
        }
    }
}

int main() {
    // man setvbuf, 设置 buffer 类型。
    setvbuf(stdout, NULL, _IONBF, 0);

    run();
    return 0;
}
