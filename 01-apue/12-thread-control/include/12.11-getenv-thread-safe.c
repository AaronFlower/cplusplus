/**
 * A reentrant version of getenv.
 * It uses the pthread_once function to ensure that thread_init
 * function is called only once process, regardless of how many 
 * threads might race to call getenv_r at the same time.
 */
#include <string.h>
#include <pthread.h>
#include <errno.h>      // for ENOENT

extern char **environ;

static pthread_once_t init_done = PTHREAD_ONCE_INIT;  // #define PTHREAD_ONCE_INIT  0

pthread_mutex_t env_mutex;

// 每个进程只会执行一次
static void thread_init(void) {
    pthread_mutexattr_t attr;

    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&env_mutex, &attr);
    pthread_mutexattr_destroy(&attr);
}

int getenv_t(const char *name, char *buf, int buflen)
{
    int i, len, olen;
    pthread_once(&init_done, thread_init);
    pthread_mutex_lock(&env_mutex);
    len = strlen(name);
    for (i = 0; environ[i] != NULL; ++i) {
        if ((strncmp(name, environ[i], len) == 0) && (environ[i][len] == '=')) {
            olen = strlen(&environ[i][len + 1]);
            if (olen >= buflen) {
                pthread_mutex_unlock(&env_mutex);
                return ENOSPC;
            }
            strcpy(buf, &environ[i][len + 1]);
            pthread_mutex_unlock(&env_mutex);
            return 0;
        }
    }
    pthread_mutex_unlock(&env_mutex);
    return ENOENT;
}

