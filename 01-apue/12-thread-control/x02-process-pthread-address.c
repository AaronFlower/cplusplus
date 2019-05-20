#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int main(void)
{
    printf("[+] Parent Process ID: %d\n", getpid());
    unsigned long id = (unsigned long)pthread_self();
    printf("[+] Parent Thread ID: %ld (0x%lx)\n", id, id);

    if (fork() == 0) {
        printf("\t[+] Child Process ID: %d\n", getpid());
        unsigned long ctid = (unsigned long)pthread_self();
        printf("\t[+] Child Thread ID: %ld (0x%lx)\n", ctid, ctid);
    }

    pause();
    return 0;
}
