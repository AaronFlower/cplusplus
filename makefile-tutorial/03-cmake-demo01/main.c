#include <stdio.h>
#include <stdlib.h>


/**
 * Raise to power - Return base raised to the power exponent: base ^ power.
 * @param base: Base value
 * @param exponent: Exponent value
 */
long int power (int base, int power) 
{
	int result = base;
	int i;

	if (power == 0) {
		return 1;
	}

	for (i = 1; i < power; ++i) {
		result *= base;
	}
	
	return result;
}


int main (int argc, char *argv[]) 
{
	if (argc < 3) {
		printf("Please input base and exponent to cacluate base ^ power!\n ");
		return 0;
	}

	int base = atoi(argv[1]);
	int exponent = atoi(argv[2]);

	long int result = power(base, exponent);
	printf("%d ^ %d = %ld \n", base, exponent, result);

	return 0;
}
