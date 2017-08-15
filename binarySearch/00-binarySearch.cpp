#include <iostream>

using namespace std;

int binarySearch(int *arr, int len, int needle)
{
	int bottom = 0, top = len, mid = 0;
	while (bottom <= top) {
		// Please don't miss the bottom base.
		mid = bottom + (int)((top - bottom) / 2);
		if (arr[mid] == needle) {
			return mid;
		} else if (arr[mid] > needle) {
			top = mid - 1;
		} else {
			bottom = mid + 1;
		}
	}
	return -1;
}

int main(int argc, char const *argv[])
{
	int arr[] = {2, 4, 7, 9, 30, 35, 43};
	int len = sizeof(arr)/sizeof(arr[0]);
	cout<<"binarySearch(arr, len, 9)	: " << binarySearch(arr, len, 9) << endl;
	cout<<"binarySearch(arr, len, 2)	: " << binarySearch(arr, len, 2) << endl;
	cout<<"binarySearch(arr, len, 43)	: " << binarySearch(arr, len, 43) << endl;
	cout<<"binarySearch(arr, len, 0)	: " << binarySearch(arr, len, 0) << endl;
	cout<<"binarySearch(arr, len, 100)	: " << binarySearch(arr, len, 100) << endl;
	cout<<"binarySearch(arr, len, 10)	: " << binarySearch(arr, len, 10) << endl;
	return 0;
}