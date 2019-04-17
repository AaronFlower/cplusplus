#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

volatile sig_atomic_t got_usr1;
/* int got_usr1; */

void sigusr1_hanlder(int sig) {
    (void)sig;
    got_usr1 = 1;
}

int main()
{
    struct sigaction sa;

    got_usr1 = 0;

    sa.sa_handler = sigusr1_hanlder;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("[-] Error sigaction");
    }

    while(!got_usr1) {
        printf("Pid %d: working hard...\n", getpid());
        sleep(1);
    }
    printf("Done in by SIGUSR1! \n");
    return 0;
}
