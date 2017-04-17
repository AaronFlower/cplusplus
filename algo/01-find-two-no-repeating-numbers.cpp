/**
 * Find the two non-repeating elements in an array of repeating elements
 * http://www.geeksforgeeks.org/find-two-non-repeating-elements-in-an-array-of-repeating-elements/
 */
#include <iostream>
using namespace std;

void findTwoNonRepeatingNumbers(int * a, int count, int * num1, int * num2)
{
	int axor = 0;
	for(auto i = 0; i < count; ++i) {
		axor ^= a[i];
	}
	int bitMask = axor & ~(axor - 1);
	*num1 = 0;
	*num2 = 0;
	for (auto i = 0; i < count; ++i) {
		if (a[i] & bitMask) {
			*num1 ^= a[i];
		} else {
			*num2 ^= a[i];
		}
	}
}

int main (void) 
{
	int arr[] = {2, 3, 7, 9, 11, 2, 3, 11};
	int count = sizeof(arr) / sizeof(*arr);
	int *a = (int *) malloc(sizeof(int));
	int *b = (int *) malloc(sizeof(int));
	findTwoNonRepeatingNumbers(arr, count, a, b);
	cout << "The tow non-repeating numbers are : " << *a << "\t" << *b << endl;
	return 0;
}