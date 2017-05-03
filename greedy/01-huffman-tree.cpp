#include <iostream>

using namespace std;

struct HeapNode
{
	char value;
	int freq;
};

class MinHeap
{
	friend ostream & operator << (ostream & os, const MinHeap & heap);
public:
	MinHeap();
	MinHeap(char * chars, int * freq, int len);
	~MinHeap();
	HeapNode extract();
	void insert(HeapNode node);

private:
	void createMinHeap();
	void minHeapify(int nodeIndex);
	/**
	 * left, right, parent, lastNoneLeaf 为工具函数。
	 */
	// 左子节点。
	int left(int nodeIndex) {
		return ((nodeIndex + 1) << 1) - 1;
	};
	// 右子节点。
	int right(int nodeIndex) {
		return ((nodeIndex + 1) << 1);
	};
	// 父节点。
	int parent(int nodeIndex) {
		return nodeIndex >> 1;
	};
	// 最后一个非叶子节点。
	int lastNoneLeaf() {
		return parent(size - 1);
	};
	void swap(int nodeIndex1, int nodeIndex2)
	{
		HeapNode tmpNode = {nodes[nodeIndex1].value, nodes[nodeIndex1].freq};
		nodes[nodeIndex1].value = nodes[nodeIndex2].value;
		nodes[nodeIndex1].freq = nodes[nodeIndex2].freq;
		nodes[nodeIndex2].value = tmpNode.value;
		nodes[nodeIndex2].freq = tmpNode.freq;
	};

public:
	int size = 0;
private:
	HeapNode * nodes = nullptr;
};

MinHeap::MinHeap(char * chars, int * freq, int len)
{
	size = len;
	nodes = new HeapNode[len];
	for (int i = 0; i < len; ++i)
	{
		nodes[i].value = chars[i];
		nodes[i].freq = freq[i];
	}
	createMinHeap();
}

MinHeap::~MinHeap()
{
	cout << "Destroy MinHeap..." << endl;
	if (nodes) {
		delete [] nodes;
	}
}
/**
 * 构造最小堆。从最后一个非叶子结依次调整到根节点。
 */
void MinHeap::createMinHeap()
{
	int lastIndex = lastNoneLeaf();
	for (int i = lastIndex; i >= 0; --i) {
		minHeapify(i);
	}
}

void MinHeap::minHeapify(int nodeIndex)
{
	int leftIndex = left(nodeIndex);
	int rightIndex = right(nodeIndex);
	int minIndex = nodeIndex;
	if (leftIndex < size && nodes[leftIndex].freq < nodes[minIndex].freq) {
		minIndex = leftIndex;
	}
	if (rightIndex < size && nodes[rightIndex].freq < nodes[minIndex].freq) {
		minIndex = rightIndex;
	}
	if (nodeIndex != minIndex) {
		swap(nodeIndex, minIndex);
		if (minIndex == leftIndex) {
			minHeapify(leftIndex);
		}
		if (minIndex == rightIndex) {
			minHeapify(rightIndex);
		}
	}
}

ostream & operator << (ostream & os, const MinHeap & minHeap)
{
	for (int i = 0; i < minHeap.size; ++i)
	{
		cout << minHeap.nodes[i].value << "(" << minHeap.nodes[i].freq << ")" << "\t";
	}
	return os;
}


int main(int argc, char const *argv[])
{
	int freq[] = {9, 5, 12, 16, 13, 45};
	char chars[] = {'b', 'a', 'c', 'e', 'c', 'f'};
	int len = sizeof(freq) / sizeof(int);
	MinHeap minHeap = MinHeap(chars, freq, len);
	cout << minHeap << endl;
	char chars2[] = {'b', 'a', 'c', 'e', 'c', 'f', 'g', 'h', 'i', 'j', 'k', 'l'};
	int brr[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
	MinHeap testH = MinHeap(chars2, brr, 10);
	cout << testH << endl;
	return 0;
}