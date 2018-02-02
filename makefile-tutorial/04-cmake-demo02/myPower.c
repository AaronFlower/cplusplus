#include "myPower.h"

/**
 * Raise to power - Return base raised to the power exponent: base ^ power
 * 
 * @param base: Base value
 * @param exponent: Exponent value
 */
long int power(int base, int exponent)
{
	long int result = base;
	int i = 1;

	if (exponent == 0) {
		return 1;
	}

	for (; i < exponent; ++i) {
		result *= base;
	}

	return result;
}

