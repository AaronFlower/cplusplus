#include <iostream>

#define leftChild(node) ((((node) + 1) << 1) - 1) 
#define rightChild(node) (((node) + 1) << 1) 
#define parent(node) ((node) >> 1)
#define max(a, b) ((a) > (b) ? (a) : (b))

using namespace std;

void swap(int * heap, int i, int j)
{
	int tmp = heap[i];
	heap[i] = heap[j];
	heap[j] = tmp;
}


void heapify(int * heap, int node, int len)
{
	int lChild = leftChild(node);
	int rChild = rightChild(node);
	int maxIndex = node;
	if (heap[maxIndex] < heap[lChild] && lChild < len) {
		maxIndex = lChild;
	}
	if (heap[maxIndex] < heap[rChild] && rChild < len) {
		maxIndex = rChild;
	}
	if (maxIndex == node) {
		return;
	}
	swap(heap, maxIndex, node);
	heapify(heap, maxIndex, len);
}

void createHeap(int * heap, int len)
{
	int startNode = (len >> 1) - 1;
	for(int i = startNode; i >=0; --i) {
		heapify(heap, i, len);
	}
}

void heapSort(int * heap, int len)
{
	for (int i = len -1; i > 0; --i)
	{
		swap(heap, 0, i);
		heapify(heap, 0, i);
	}
}

int main(int argc, char const *argv[])
{
	int arr[] = {1, 2, 7, 4, 9, 8, 0, 3, 5, 6};
	int len = 10;
	cout << "Create heap for a array." <<endl;
	for (auto ele : arr) {
		cout << ele << "\t";
	}
	cout << endl;
	createHeap(arr, len);
	for (auto ele : arr) {
		cout << ele << "\t";
	}
	cout << "Create heap for b array." <<endl;
	int brr[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
	for (auto ele : brr) {
		cout << ele << "\t";
	}
	cout << endl;
	createHeap(brr, len);
	for (auto ele : brr) {
		cout << ele << "\t";
	}
	heapSort(brr, len);
	cout << "\nafter heap sort \n";
	for (auto ele: brr) {
		cout << ele << "\t";
	}
	return 0;
}