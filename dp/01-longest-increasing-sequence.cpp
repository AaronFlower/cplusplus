#include <iostream>

using namespace std;

int getLongestIncreasingSequence(int * a, int len)
{
	int * lis = new int[len];
	int i , j, maxLen = 1;
	for (i = 0; i < len; ++i) {
		lis[i] = 1;
	}
	for (i = 1; i < len; ++i) {
		for (j = 0; j < i; ++j) {
			if (a[i] > a[j] && lis[i] < lis[j] + 1) {
				lis[i] = lis[j] + 1;
			}
		}
	}
	for (i = 0; i < len; ++i) {
		if (maxLen < lis[i]) {
			maxLen = lis[i];
		}
	}
	delete [] lis;
	return maxLen;
}

int main(int argc, char const *argv[])
{
	int a[] = {10, 22, 9, 33, 21, 50, 41, 60, 80};
	int len = sizeof(a) / sizeof(a[0]);
	cout << getLongestIncreasingSequence(a, len) <<endl;
	return 0;
}