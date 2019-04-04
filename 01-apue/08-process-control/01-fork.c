#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int globvar = 6; /* external variable in initialized data */
char buf[] = "a write to stdout \n";

int main()
{
    int var; /* automatic variable on the stack */
    pid_t pid;
    var = 88;

    if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1) {
        printf("Write Error!\n");
        exit(1);
    }

    printf("before fork \n");

    if ((pid = fork()) < 0) {
        printf("fork error");
        exit(1);
    } else if (pid == 0) {
        // child
        globvar ++;
        var ++;
    } else {
        sleep(2);
    }

    printf("pid = %ld, glob = %d, var = %d \n", (long)getpid(), globvar, var);
    return 0;
}
