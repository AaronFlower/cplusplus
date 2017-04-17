/**
 * Find the one non-repeating elements in an array of repeating elements
 */
#include <iostream>
using namespace std;

int findOnceNumber(int * a, int len)
{
	int axor = 0;
	for (int i = 0; i < len; ++i) {
		axor ^= a[i];
	}
	return axor;
}

int main (void) 
{
	int a [] = {1, 2, 1, 4, 2, 3, 4};
	int len = 7;
	cout << "The array is: \t" ;
	for (auto ele: a) {
		cout << ele << "\t";
	}
	cout << "\nThe singel number is :" << findOnceNumber(a, len) << endl;
	return 0;
}
