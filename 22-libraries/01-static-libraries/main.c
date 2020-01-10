#include <stdio.h>
#include "mymath.h"

int main(void)
{
    double d = 100;
    printf("sqrt (%3.0f) = %2.0f\n", d, calcSqrt(d));
    return 0;
}
