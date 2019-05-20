/**
 * This version is not reenterant.
 * If two threads call it at the same time, they will see inconsistent results,
 * because the string returned is stored in a single static buffer that is shared
 * by all threads calling getenv.
 */
#include <string.h>

#define MAX_STRING_SZ 4096

static char env_buf[MAX_STRING_SZ];
extern char **environ;

char * getent(const char *name)
{
    int i, len;
    len = strlen(name);
    for (i = 0; environ[i] != NULL; ++i) {
        if ((strncmp(name, environ[i], len) == 0 && environ[i][len] == '=')) {
            strncpy(env_buf, &environ[i][len+1], MAX_STRING_SZ - 1);
            return env_buf;
        }
    }
    return NULL;
}
