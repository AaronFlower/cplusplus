#include <stdio.h>
#include <stdlib.h>
#include "config.h"

#ifdef USE_MYMATH
	#include "math/myPower.h"
#else
	#include <math.h>
#endif


int main (int argc, char *argv[])
{
	if (argc < 3) {
		printf("Usage: %s base exponent\n", argv[0]);
		return 0;
	}

	int base = atoi(argv[1]);
	int exponent = atoi(argv[2]);

	#ifdef USE_MYMATH
		printf("Now we use our own Math library. \n");
		long int result = power(base, exponent);
	#else
		printf("Now we use standard library. \n");
		long int result = pow(base, exponent);
	#endif
	
	printf(" %d ^ %d = %ld \n", base, exponent, result);
	return 0;
}
