#include <stdio.h>
#include <stdlib.h>        // for exit()
#include <signal.h>        // for signal()
#include <unistd.h>


typedef void (*sig_action)(int);
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
    sig_action pre_action;

    if ((pre_action = signal(SIGUSR1, sig_usr)) == SIG_ERR) {
        perror("[-] Error catch SIGUSR1");
        exit(1);
    } else {
        printf("Success called SIGUSR1 , and previous singal action is %d\n", pre_action);
    }

    if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
        perror("[-] Error catch SIGUSR2");
        exit(1);
    } else {
        printf("Success called SIGUSR2 \n");
    }

    for (;;) {
        pause();
    }

    return 0;
}
