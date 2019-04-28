#ifndef MY_SOLUTION__
#define MY_SOLUTION__

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define CHAR_COUNT 256

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

void initBadCharMap(int *badCharMap, const char *needle, size_t len) {
    for (size_t i = 0; i < CHAR_COUNT; ++i) {
        badCharMap[i] = -1;
    }

    for (size_t i = 0; i < len; ++i) {
        badCharMap[(int)needle[i]] = i;
    }
}

/**
 * Boyer-Moore string search algorithm using the first heuristic method:
 * bad character heuristic.
 */
int BMStrSearchBadChar(const char *hayStack, const char *needle, size_t start) {
    assert(hayStack != NULL);
    assert(needle != NULL);

    size_t hLen = strlen(hayStack);
    size_t nLen = strlen(needle);
    assert(start < hLen);

    if (nLen == 0) return start;

    int badCharMap[CHAR_COUNT];
    initBadCharMap(badCharMap, needle, nLen);

    size_t i = start + nLen - 1;
    size_t j = 0;
    while (i < hLen) {
        for (j = 0; j < nLen; ++j) {
            if (hayStack[i - j] != needle[nLen - j - 1]) {
                break;
            }
        }
        if (j >= nLen) return i - nLen + 1;
        i = i + (nLen - 1 - badCharMap[(int)hayStack[i]]);
    }
    return -1;
}

#endif /* ifndef MY_SOLUTION__ */
