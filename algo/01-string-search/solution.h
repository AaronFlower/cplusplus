#ifndef MY_SOLUTION__
#define MY_SOLUTION__

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define CHAR_COUNT 256

int naiveStrSearch(const char* text, const char* pat, size_t start) {
    assert(text != NULL);
    assert(pat != NULL);

    size_t tLen = strlen(text);
    size_t pLen = strlen(pat);

    assert(start < tLen);

    if (pLen == 0) return start;

    size_t i, j ;

    for (i = start; i < tLen; ++i) {
        for (j = 0; j < pLen; ++j) {
            if (pat[j] != text[i + j]) {
                break;
            }
        }

        if (j >= pLen) return i;
    }
    return -1;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void initBadCharMap(int *badCharMap, const char *pat, size_t len) {
    // Initialize all occurences as -1
    for (size_t i = 0; i < CHAR_COUNT; ++i) {
        badCharMap[i] = -1;
    }

    // Fill the actual value of last occurence of a character
    for (size_t i = 0; i < len; ++i) {
        badCharMap[(int)pat[i]] = i;
    }
}

/**
 * Boyer-Moore string search algorithm using the first heuristic method:
 * bad character heuristic.
 */
int BMStrSearchBadChar(const char *text, const char *pat, size_t start) {
    assert(text != NULL);
    assert(pat != NULL);

    size_t tLen = strlen(text);
    size_t pLen = strlen(pat);
    assert(start < tLen);

    if (pLen == 0) return start;

    int badCharMap[CHAR_COUNT];
    initBadCharMap(badCharMap, pat, pLen);

    int end = tLen - pLen;
    int s = start;
    int j = 0;
    while (s <= end) {
        j = pLen - 1;
        while (j >=0 && text[s + j] == pat[j]) j--;
        if (j < 0) return s;
        s += max(1, j - badCharMap[(int)text[s + j]]);
    }
    return -1;
}

// preprocessing for strong good suffix rule
void preprocess_strong_suffix(int *shift, int *bpos, const char *pat, int m) {
    // m is the length of pattern
    int i = m, j = m + 1;
    bpos[i] = j;

    while (i > 0) {
        /* if character at position i - 1 is not equivalent to character at j - 1
         * then continue searching to right of the pattern for border
         */
        while (j <= m && pat[i - 1] != pat[ j - 1]) {
            /* the character preceding the occurence of t in pattern P is different than
             * mismatching character in P, we stop skipping the occurences and shift the
             * pattern from i to j
             */
           if (shift[j] == 0) {
               shift[j] = j - i;
           }

           // Update the position of next border.
           j = bpos[j];
        }
        --i; --j;
        bpos[i] = j;
    }
}

// Preprocessing for case 2
void preprocess_case_2(int *shift, int *bpos, int m) {
    int i, j;
    j = bpos[0];
    for ( i = 0; i <= m; ++i) {
        /* set the border position of first character of pattern to
         * all indices in array shift having shift[i] = 0
         */
        if (shift[i] == 0) {
            shift[i] = j;
        }

        /* suffix become shorter than bpos[0], use the position of next
         * widest border as value of j
         */
        if (i == j) {
            j = bpos[j];
        }
    }
}

/*
 * Search for a pattern in given text using Boyer Moore algorithm with Good Suffix rule
 */
int BMSearchGoodSuffix(const char *text, const char *pat, size_t start) {
    // s is shift of the pattern with respect to text
    int s = start, j;
    int m = strlen(pat);
    int n = strlen(text);

    int bpos[m + 1], shift[m + 1];

    // initialize all occurences of shift to 0
    for (int i = 0; i < m + 1; ++i) {
        shift[i] = 0;
    }

    // do preprocessing
    preprocess_strong_suffix(shift, bpos, pat, m);
    preprocess_case_2(shift, bpos, m);

    int end = n - m;
    while (s <= end) {
        j = m - 1;
        while(j >= 0 && pat[j] == text[s + j]) --j;

        if (j < 0) {
            return s;
        } else {
            s += shift[j + 1];
        }
    }
    return -1;
}

/*
 * Search for a pattern in given text using Boyer Moore algorithm
 */
int BMSearch(const char *text, const char *pat, size_t start) {
    // s is shift of the pattern with respect to text
    int s = start, j;
    int m = strlen(pat);
    int n = strlen(text);

    int badCharMap[CHAR_COUNT];
    initBadCharMap(badCharMap, pat, m);

    int bpos[m + 1], shift[m + 1];

    // initialize all occurences of shift to 0
    for (int i = 0; i < m + 1; ++i) {
        shift[i] = 0;
    }

    // do preprocessing
    preprocess_strong_suffix(shift, bpos, pat, m);
    preprocess_case_2(shift, bpos, m);

    int end = n - m;
    while (s <= end) {
        j = m - 1;
        while(j >= 0 && pat[j] == text[s + j]) --j;

        if (j < 0) {
            return s;
        } else {
            s += max(shift[j + 1], j - badCharMap[(int)text[s + j]]);
        }
    }
    return -1;
}

#endif /* ifndef MY_SOLUTION__ */
