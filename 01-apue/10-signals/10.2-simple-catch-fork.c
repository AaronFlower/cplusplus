#include <stdio.h>
#include <stdlib.h>        // for exit()
#include <signal.h>        // for signal()
#include <unistd.h>         // fork fork()


typedef void (*sig_func)(void);
static void sig_usr(int signo) {
    if (signo == SIGUSR1) {
        printf("received SIGUSR1 \n");
    } else if (signo == SIGUSR2) {
        printf("received SIGUSR2 \n");
    } else {
        perror("[-] Error unhandled signal ");
        exit(1);
    }
}

int main(void)
{

    if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
        perror("[-] Error catch SIGUSR1");
        exit(1);
    } else {
        printf("Success called SIGUSR1 \n");
    }

    if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
        perror("[-] Error catch SIGUSR2");
        exit(1);
    } else {
        printf("Success called SIGUSR2 \n");
    }

    pid_t pid;


    if ((pid = fork()) < 0) {
        perror("[-] Error fork");
        exit(1);
    } else if (pid == 0) {
        printf("the parent pid is %d  \n", getppid());
        for(;;) {
            pause();
        }
    } else {
        printf("the child pid is %d, you can send signal to it \n", pid);

        // fork another and exec
        pid_t pid2;

        if ((pid2 = fork()) < 0) {
            perror("[-] Error fork 2");
            exit(1);
        } else if (pid2 == 0) {
            if (execlp("./10.2-loop", "10.2-loop", (char *)0) < 0) {
                perror("[-] Error execlp");
                exit(1);
            }
        } else {
            printf("The second child pid is %d \n", pid2);
        }

        for (;;) {
            pause();
        }
    }

    return 0;
}
