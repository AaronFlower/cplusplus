#include <iostream>

using namespace std;

#define MAX_TREE_HEIGHT 100

/**
 * HeapNode 即可以当 Heap 的节点，也可当作 Huffman 树的节点。
 */
struct HeapNode
{
	char value;
	int freq;
	HeapNode * left;
	HeapNode * right;
};

class MinHeap
{
	friend ostream & operator << (ostream & os, const MinHeap & heap);
public:
	MinHeap(){};
	MinHeap(char * chars, int * freq, int len);
	~MinHeap();
	HeapNode * extract();
	void insert(HeapNode node);
	HeapNode * buildHuffmanTree();

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
		return parent(size - 2);
	};
	void swap(int nodeIndex1, int nodeIndex2)
	{
		HeapNode tmpNode = {nodes[nodeIndex1].value, nodes[nodeIndex1].freq};
		nodes[nodeIndex1].value = nodes[nodeIndex2].value;
		nodes[nodeIndex1].freq = nodes[nodeIndex2].freq;
		nodes[nodeIndex2].value = tmpNode.value;
		nodes[nodeIndex2].freq = tmpNode.freq;
	};

	/**
	 * 与 vector 类似，当容量不足时扩充到当前 size 的两倍。
	 */
	void reallocateHeap()
	{
		capicity = size * 2;
		HeapNode * newNodes = new HeapNode[size * 2];
		memcpy(newNodes, nodes, sizeof(HeapNode) * size);
		delete [] nodes; // 释放之前分配的内存。
		nodes = newNodes; // 赋予新的内存。
	}

public:
	int size = 0;
private:
	HeapNode * nodes = nullptr;
	int capicity = 0; // 和 vector 的 capicity 分配方式一样。
};

MinHeap::MinHeap(char * chars, int * freq, int len)
{
	size = len;
	capicity = len * 2;
	nodes = new HeapNode[capicity];
	for (int i = 0; i < len; ++i)
	{
		nodes[i] = HeapNode{chars[i], freq[i], nullptr, nullptr};
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

/**
 * 递归最小堆调整。
 */
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

/**
 * 最小堆插入实现：直接将元素插入到数据最后。然后次调整父结点，直到满足最小堆的性质。
 */
void MinHeap::insert(HeapNode node)
{
	if (size >= capicity) {
		reallocateHeap();
	}
	++size;
	nodes[size - 1] = node;
	int nodeIndex = size -1;
	int parentIndex = parent(size -1);
	while(nodeIndex != 0 && nodes[nodeIndex].freq < nodes[parentIndex].freq) {
		swap(nodeIndex, parentIndex);
		nodeIndex = parentIndex;
		parentIndex = parent(nodeIndex);
	}
}

/**
 * 提取最小堆中的最小元素。
 */
HeapNode * MinHeap::extract()
{
	HeapNode * node = new HeapNode{nodes[0].value, nodes[0].freq, nullptr, nullptr};
	nodes[0] = nodes[--size];
	minHeapify(0);
	return node;
}

HeapNode * MinHeap::buildHuffmanTree()
{
	HeapNode * root, * left, * right;
	while (size > 1) {
		left = extract();
		right = extract();
		root = new HeapNode{'$', left->freq + right->freq, nullptr, nullptr};
		root->left =  left;
		root->right =  right;
		insert(* root);
	}
	return root;
}

/**
 * friend method operator overload.
 */
ostream & operator << (ostream & os, const MinHeap & minHeap)
{
	cout << "Heap info, capicity: " << minHeap.capicity << ", size : " << minHeap.size << endl;
	for (int i = 0; i < minHeap.size; ++i)
	{
		cout << minHeap.nodes[i].value << "(" << minHeap.nodes[i].freq << ")" << "\t";
	}
	return os;
}

void printHuffmanTree(HeapNode * root, int arr[], int top)
{
	if (root->left) {
		arr[top] = 0;
		printHuffmanTree(root->left, arr, top + 1);
	}
	if (root->right) {
		arr[top] = 1;
		printHuffmanTree(root->right, arr, top + 1);
	}
	if (root->left == nullptr && root->right == nullptr) {
		cout << root->value << "(" << root->freq << "):";
		for (int i = 0; i < top; ++i) {
			cout << arr[i];
		}
		cout << endl;
	}
}

void testHeap()
{
	int freq[] = {9, 5, 12, 16, 13, 45};
	char chars[] = {'b', 'a', 'c', 'e', 'c', 'f'};	
	int len = sizeof(freq) / sizeof(int);
	MinHeap minHeap = MinHeap(chars, freq, len);
	cout << minHeap << endl;
	MinHeap heap2 = MinHeap();
	for (int i = len - 1; i >= 0; --i)
	{
		heap2.insert(HeapNode{chars[i], freq[i], nullptr, nullptr});
	}
	cout << heap2 << endl;
	char chars2[] = {'b', 'a', 'c', 'e', 'c', 'f', 'g', 'h', 'i', 'j', 'k', 'l'};
	int brr[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
	MinHeap testH = MinHeap(chars2, brr, 10);
	cout << testH << endl;
}


int main(int argc, char const *argv[])
{
	testHeap();
	cout << "---->>>" << endl;
	int freq[] = {9, 5, 12, 16, 13, 45};
	char chars[] = {'b', 'a', 'c', 'e', 'c', 'f'};	
	int len = sizeof(freq) / sizeof(int);
	MinHeap minHeap = MinHeap(chars, freq, len);
	cout << minHeap << endl;
	HeapNode * huffmanTree = minHeap.buildHuffmanTree();
	int arr[MAX_TREE_HEIGHT], top = 0;
	printHuffmanTree(huffmanTree, arr, top);
	return 0;
}