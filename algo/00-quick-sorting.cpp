#include <iostream>
using namespace std;

void swap(int * a, int indexI , int indexJ)
{
	int tmp = a[indexI];
	a[indexI] = a[indexJ];
	a[indexJ] = tmp;
}
int partition(int * a, int start, int end, int (* condFunc) (int, int))
{
	return 0;
}

/**
 * 快速排序最重要的是 if 条件的判断。可以把 if 条件的判断当成一个函数参数传进来。
 */
int partition(int * a, int start, int end)
{
	int lessIndex = start - 1;
	int pivot = a[end];
	for (auto i = start; i < end; ++i) {
		if (a[i] <= pivot) {
			++lessIndex;
			swap(a, lessIndex, i);
		}
	}
	swap(a, lessIndex + 1, end);
	return lessIndex + 1;
}

void quickSort(int * a, int start, int end)
{
	if (start < end) {
		int pivotIndex = partition(a, start, end);
		quickSort(a, start, pivotIndex - 1);
		quickSort(a, pivotIndex + 1, end);
	}
}

int main (void)
{
	int a[] = {4, 1, 2, 4, 7, 9, 0, 3};
	int count = sizeof(a) / sizeof(a[0]);
	cout << "Array length: " << count << endl;
	cout << "Origin array: \t";
	for (auto ele : a) {
		cout << ele << "\t";
	}
	quickSort(a, 0, count - 1);
	cout << "\nSorted array: \t";
	for (auto ele: a) {
		cout << ele << "\t";
	}
}