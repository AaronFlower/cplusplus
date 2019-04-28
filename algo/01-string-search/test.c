#include <stdio.h>

#include "test.h"
#include "solution.h"

static void test_naive_string_search() {
    /* char *h1 = NULL; */
    /* char *n1 = NULL; */
    /* EXPECT_EQ_INT(0, naiveStrSearch(h1, n1, 0)); */

    char *hayStack = "Hello";
    char *needle = "";
    EXPECT_EQ_INT(0, naiveStrSearch(hayStack, needle, 0));
    EXPECT_EQ_INT(1, naiveStrSearch(hayStack, needle, 1));

    char *n2 = "e";
    EXPECT_EQ_INT(1, naiveStrSearch(hayStack, n2, 1));

    char *n3 = "r";
    EXPECT_EQ_INT(-1, naiveStrSearch(hayStack, n3, 1));

    int pos[3] = {2, 3, -1};
    int start = -1;
    for (size_t i = 0; i < 3; ++i) {
        start = naiveStrSearch(hayStack, "l", start + 1);
        EXPECT_EQ_INT(pos[i], start);
    }

    char *h4 = "this is a simple example";
    char *n4 = "ple";
    int pos4[3] = {13, 21, -1};
    start = -1;
    for (size_t i = 0; i < 3; ++i) {
        start = naiveStrSearch(h4, n4, start + 1);
        EXPECT_EQ_INT(pos4[i], start);
    }

}

static void test_BM_bad_char_heuristic() {
    /* char *h1 = NULL; */
    /* char *n1 = NULL; */
    /* EXPECT_EQ_INT(0, naiveStrSearch(h1, n1, 0)); */

    char *hayStack = "Hello";
    char *needle = "";
    EXPECT_EQ_INT(0, BMStrSearchBadChar(hayStack, needle, 0));
    EXPECT_EQ_INT(1, BMStrSearchBadChar(hayStack, needle, 1));

    char *n2 = "e";
    EXPECT_EQ_INT(1, BMStrSearchBadChar(hayStack, n2, 1));

    char *n3 = "r";
    EXPECT_EQ_INT(-1, BMStrSearchBadChar(hayStack, n3, 1));

    int pos[3] = {2, 3, -1};
    int start = -1;
    for (size_t i = 0; i < 3; ++i) {
        start = BMStrSearchBadChar(hayStack, "l", start + 1);
        EXPECT_EQ_INT(pos[i], start);
    }

    char *h4 = "this is a simple example";
    char *n4 = "ple";
    int pos4[3] = {13, 21, -1};
    start = -1;
    for (size_t i = 0; i < 3; ++i) {
        start = BMStrSearchBadChar(h4, n4, start + 1);
        EXPECT_EQ_INT(pos4[i], start);
    }

}

static void test_BM_good_suffix_heuristic() {
    /* char *h1 = NULL; */
    /* char *n1 = NULL; */
    /* EXPECT_EQ_INT(0, naiveStrSearch(h1, n1, 0)); */

    char *hayStack = "Hello";
    char *needle = "";
    EXPECT_EQ_INT(0, BMSearchGoodSuffix(hayStack, needle, 0));
    EXPECT_EQ_INT(1, BMSearchGoodSuffix(hayStack, needle, 1));

    char *n2 = "e";
    EXPECT_EQ_INT(1, BMSearchGoodSuffix(hayStack, n2, 1));

    char *n3 = "r";
    EXPECT_EQ_INT(-1, BMSearchGoodSuffix(hayStack, n3, 1));

    int pos[3] = {2, 3, -1};
    int start = -1;
    for (size_t i = 0; i < 3; ++i) {
        start = BMSearchGoodSuffix(hayStack, "l", start + 1);
        EXPECT_EQ_INT(pos[i], start);
    }

    char *h4 = "this is a simple example";
    char *n4 = "ple";
    int pos4[3] = {13, 21, -1};
    start = -1;
    for (size_t i = 0; i < 3; ++i) {
        start = BMSearchGoodSuffix(h4, n4, start + 1);
        EXPECT_EQ_INT(pos4[i], start);
    }
}

static void test_BM() {
    /* char *h1 = NULL; */
    /* char *n1 = NULL; */
    /* EXPECT_EQ_INT(0, naiveStrSearch(h1, n1, 0)); */

    char *hayStack = "Hello";
    char *needle = "";
    EXPECT_EQ_INT(0, BMSearch(hayStack, needle, 0));
    EXPECT_EQ_INT(1, BMSearch(hayStack, needle, 1));

    char *n2 = "e";
    EXPECT_EQ_INT(1, BMSearch(hayStack, n2, 1));

    char *n3 = "r";
    EXPECT_EQ_INT(-1, BMSearch(hayStack, n3, 1));

    int pos[3] = {2, 3, -1};
    int start = -1;
    for (size_t i = 0; i < 3; ++i) {
        start = BMSearch(hayStack, "l", start + 1);
        EXPECT_EQ_INT(pos[i], start);
    }

    char *h4 = "this is a simple example";
    char *n4 = "ple";
    int pos4[3] = {13, 21, -1};
    start = -1;
    for (size_t i = 0; i < 3; ++i) {
        start = BMSearch(h4, n4, start + 1);
        EXPECT_EQ_INT(pos4[i], start);
    }
}

int main()
{
    test_naive_string_search();
    test_BM_bad_char_heuristic();
    test_BM_good_suffix_heuristic();
    test_BM();
    OUTPUT_TEST();
}
