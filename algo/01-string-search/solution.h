#ifndef MY_SOLUTION__
#define MY_SOLUTION__

#include <stdlib.h>
#include <string.h>
#include <assert.h>

int naiveStrSearch(const char* hayStack, const char* needle, size_t start) {
    assert(hayStack != NULL);
    assert(needle != NULL);

    size_t hLen = strlen(hayStack);
    size_t nLen = strlen(needle);

    assert(start < hLen);

    if (nLen == 0) return start;

    size_t i, j ;

    for (i = start; i < hLen; ++i) {
        for (j = 0; j < nLen; ++j) {
            if (needle[j] != hayStack[i + j]) {
                break;
            }
        }

        if (j >= nLen) return i;
    }
    return -1;
}

#endif /* ifndef MY_SOLUTION__ */
