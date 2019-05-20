/*
 * A thread-safe `getenv`, we use thread-specific data to 
 * maintain a per-thread copy of the data used to hold the 
 * return string.
 */
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SZ 4096

extern char **environ;

pthread_once_t init_done = PTHREAD_ONCE_INIT;
pthread_key_t key;
pthread_mutex_t env_mutex;

static void thread_int(void) {
    pthread_key_create(&key, free);
}

char *getenv(const char *name) {
    int     i, len;
    char    *env_buf;

    pthread_once(&init_done, thread_int);
    pthread_mutex_lock(&env_mutex);

    env_buf = (char *)pthread_getspecific(key);
    if (env_buf == NULL) {
        if((env_buf = (char *)malloc(MAX_STRING_SZ)) == NULL) {
            pthread_mutex_unlock(&env_mutex);
            return NULL;
        }
        pthread_setspecific(key, env_buf);
    }

    len = strlen(name);
    for (i = 0; environ[i] != NULL; ++i) {
        if (strncmp(name, environ[i], len) == 0 && (environ[i][len] == '=')) {
            strncpy(env_buf, &environ[i][len + 1], MAX_STRING_SZ - 1);
            pthread_mutex_unlock(&env_mutex);
            return env_buf;
        }
    }

    pthread_mutex_unlock(&env_mutex);
    return NULL;
}
