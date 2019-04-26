#include "test.h"

/* extern int main_ret; */

int main()
{
    EXPECT_EQ_INT(1, 1);
    printf("%d\n", main_ret);
    printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return 0;
}
