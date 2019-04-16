#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int rv;

    switch (pid = fork()) {
    case -1:
        perror("fork");
        exit(1);
    case 0:
        printf(" Child: This is the child process\n");
        printf(" Child: My PID is %d\n", getpid());
        printf(" Child: My parent's PID is %d\n", getppid());
        printf(" Child: Enter my exit status (make it small): ");
        scanf(" %d", &rv);
        printf(" Child: I'm outta here! \n");
        exit(rv);
    default:
        printf(" Parent: This is the parent process\n");
        printf(" Parent: My PID is %d\n", getpid());
        printf(" Parent: My child's PID is %d\n", pid);
        printf(" Parent: I'm now waiting for my child to exit()...  \n");
        wait(&rv);
        printf(" Parent: My child's exit status is : %d\n", WEXITSTATUS(rv));
        printf(" Parent: I'm outta here!\n");
    }

    return 0;
}
