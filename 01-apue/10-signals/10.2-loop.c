#include <stdio.h>
#include <unistd.h>

int main(void)
{

    printf("   [exec] I was executed by exec funciton!\n");
    printf("   [exec] My pid is %d, ppid is %d\n", getpid(), getppid());
    for(;;) {
        pause();
    }
    return 0;
}
