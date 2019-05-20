#include <stdio.h>
#include <stdlib.h>     // for exit()
#include <unistd.h>     // for sysconf
#include <errno.h>

int main(void)
{
    int i, len = 4;
    long val;

    char *limit_names[] = {
        "THREAD_DESTRUCTOR_ITERATIONS",
        "THREAD_KEYS_MAX",
        "THREAD_STACK_MIN",
        "THREAD_THREADS_MAX",
    };


    int limit_keys[] = {
        _SC_THREAD_DESTRUCTOR_ITERATIONS,
        _SC_THREAD_KEYS_MAX,
        _SC_THREAD_STACK_MIN,
        _SC_THREAD_THREADS_MAX,
    };

    for (i = 0; i < len; ++i) {
        val = sysconf(limit_keys[i]);
        if (val == -1 && errno != 0) {
            perror("[-] Error sysconf");
            exit(1);
        }

        printf("%s : %ld\n", limit_names[i], val);
    }

    return 0;
}
