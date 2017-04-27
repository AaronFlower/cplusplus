#include <iostream>

using namespace std;
/**
 * Union Find Algorithm
 */
struct Edge
{
	int src;
	int dest;
};

struct Subset
{
	int parent;
	int rank;
};

class Graph
{
public:
	Graph(int v, int e):numV(v), numE(e), edges(new Edge[numE]){};
	~Graph() {
		cout << "The graph is destroyed!\n";
		delete [] edges;
	};
	int find(int * &parents, int v);
	void unionSubset(int * & parents, int v1, int v2);
	bool checkIsCycle();
	int findWithRank(Subset * & subsets, int v);
	void unionSubsetWithRank(Subset * & subsets, int v1, int v2);
	bool checkIsCycleWithRank();
public:
	int numV;
	int numE;
	Edge * edges;
};

/**
 * 查找 subset 中的 representive .
 */
int Graph::find(int * &parents, int v)
{
	if (parents[v] == -1) {
		return v;
	} 
	return find(parents, parents[v]);
}

/**
 * 合并两个子集。
 */
void Graph::unionSubset(int * &parents, int v1, int v2)
{
	int repV1 = find(parents, v1);
	int repV2 = find(parents, v2);
	parents[repV1] = repV2;
}

bool Graph::checkIsCycle() 
{
	int *parents = new int[numV];
	memset(parents, -1, sizeof(int) * numV);
	for (int i = 0; i < numE; ++ i) 
	{
		int repX = find(parents, edges[i].src);
		int repY = find(parents, edges[i].dest);
		if (repX == repY) {
			return true;
		} else {
			unionSubset(parents, repX, repY);
		}
	}
	return false;
}

int Graph::findWithRank(Subset * & subsets, int v)
{
	if (subsets[v].parent != v) {
		return findWithRank(subsets, subsets[v].parent);
	}
	return subsets[v].parent;
}

void Graph::unionSubsetWithRank(Subset * & subsets, int v1, int v2)
{
	int repV1 = findWithRank(subsets, v1);
	int repV2 = findWithRank(subsets, v2);
	if (subsets[repV1].rank < subsets[repV2].rank) {
		subsets[repV1].parent = repV2;
	} else if (subsets[repV1].rank > subsets[repV2].rank) {
		subsets[repV2].parent = repV1;
	} else {
		subsets[repV1].parent = repV2;
		subsets[repV2].rank++;
	}
}

/**
 * Union-find by rank with path compression.
 */
bool Graph::checkIsCycleWithRank()
{
	// subsets initialization
	Subset * subsets = new Subset[numV];
	for (int v = 0; v < numV; ++v) {
		subsets[v].parent = v;
		subsets[v].rank = 0;
	}

	int repX, repY;
	for (int e = 0; e < numE; ++e){
		repX = findWithRank(subsets, edges[e].src);
		repY = findWithRank(subsets, edges[e].dest);
		if (repX == repY) {
			return true;
		} else {
			unionSubsetWithRank(subsets, repX, repY);
		}
	}
	return false;
}

int main(int argc, char const *argv[])
{
	Graph g = Graph(3, 2);
	g.edges[0].src = 0;
	g.edges[0].dest = 1;	
	g.edges[1].src = 0;
	g.edges[1].dest = 2;	
	g.edges[2].src = 1;
	g.edges[2].dest = 2;
	if (g.checkIsCycle()) {
		cout << "The graph has a cycle. \n";
	} else {
		cout << "The graph dose not have a cycle. \n";
	}
	if (g.checkIsCycleWithRank()) {
		cout << "The graph has a cycle (check with rank). \n";
	} else {
		cout << "The graph dose not have a cycle (check with rank). \n";
	}
	return 0;
}