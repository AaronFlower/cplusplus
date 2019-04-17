#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(void)
{
    int fds[2];
    pid_t pid;

    if (pipe(fds) == -1) {
        perror("[-] Error pipe");
        exit(1);
    }

    if ((pid = fork()) == -1) {
        perror("[-] Error fork");
        exit(1);
    } else if(pid == 0) {
        close(fds[0]);  // 我们的子进程只需要写 fds[1] 就行了，不需要 fds[0]
        close(1);       // 关闭 stdout
        // dup(fds[1]) makes a copy of the write-end of the pipe in the first available file descriptor,
        // whic is "1", since we just close it.
        dup(fds[1]);    // clone 一个 fd
        execlp("ls", "ls", NULL);
    } else {
        close(fds[1]);  // 我们的父进程只需要读 fds[0] 就行了，不需要 fds[1]
        close(0);       // 关闭 stdin
        dup(fds[0]);
        execlp("wc", "wc", "-l", NULL);
    }

    return 0;
}
