#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <string.h>

void sigint_handler(int sig) {
    (void)sig;
    char *msg =  "Aha! SIGINT! \n";
    write(0,msg, strlen(msg));
}

int main()
{
    void sigint_handler(int sig);
    char s[200];
    struct sigaction sa;

    sa.sa_handler = sigint_handler;
    /* sa.sa_flags = 0; */
    sa.sa_flags = SA_RESTART; // some system calls can be restart
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("[-] error sigaction");
        exit(1);
    }

    printf("Enter a string:\n");
    if (fgets(s, sizeof s, stdin) == NULL) {
        perror("[-] Error fgets ");
    } else {
        printf("You entered: %s \n", s);
    }
    return 0;
}
