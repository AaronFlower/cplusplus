#include "myPower.h"

/**
 * Raise to power: Raise a number to power (base ^ power)
 * @param base: Base value
 * @param exponent: Exponent value
 */
long int power (int base, int exponent)
{
	long int result = base;
	int i;

	if (exponent == 0) {
		return 1;
	}

	for (i = 1; i < exponent; ++i) {
		result *= base;
	}

	return result;
}
