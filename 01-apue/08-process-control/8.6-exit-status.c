#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


void pr_exit(int status) {
    /**
     * Check Wait IF: exited, signaled, stopped, continued
     */
    if (WIFEXITED(status)) {
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("abnormal termination, signal number = %d%s\n", WTERMSIG(status),
#ifdef WCOREDUMP
                WCOREDUMP(status) ? "(core file generated) " : "");
#else
        "");
#endif
    } else if (WIFSTOPPED(status)) {
        printf("child stopped, signal number = %d \n", WSTOPSIG(status));
    }
}

int main()
{
    pid_t pid;
    int status;

    if ((pid = fork()) < 0) {
        printf("fork error\n");
    } else if (pid == 0) {
        /* exit(7); // what if comment this line? */
    }

    // - Block, if all of its children are still running.
    // - Return immediately with the termination status of a child.
    // - Return immediately with an error, if it doesn't have any child processes.
    if (wait(&status) != pid) {
        printf("wait error\n");
    }
    pr_exit(status);

    /* ------------  separator ----------*/

    if ((pid = fork()) < 0) {
        printf("fork error\n");
    } else if (pid == 0) {
        abort();
    }

    // - Block, if all of its children are still running.
    // - Return immediately with the termination status of a child.
    // - Return immediately with an error, if it doesn't have any child processes.
    if (wait(&status) != pid) {
        printf("wait error\n");
    }
    pr_exit(status);

    /* ------------  separator ----------*/

    if ((pid = fork()) < 0) {
        printf("fork error\n");
    } else if (pid == 0) {
        status /= 0;
    }

    // - Block, if all of its children are still running.
    // - Return immediately with the termination status of a child.
    // - Return immediately with an error, if it doesn't have any child processes.
    if (wait(&status) != pid) {
        printf("wait error\n");
    }
    pr_exit(status);


    return 0;
}
