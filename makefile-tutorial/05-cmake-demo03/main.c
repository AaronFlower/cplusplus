#include <stdio.h>
#include <stdlib.h>
#include "math/myPower.h"

int main (int argc, char *argv[])
{
	if (argc < 3) {
		printf("Please input base and power value to raise base ^ power!\n");
		return 0;
	}

	int base = atoi(argv[1]);
	int exponent = atoi(argv[2]);

	printf(" %d ^ %d = %ld \n", base, exponent, power(base, exponent));

	return 0;
}
