#include <iostream>

using namespace std;

struct Edge {
	int src;
	int dest;
};

class Graph {
public:
	int numV;
	int numE;
	Edge * edges;
	Graph (int v, int e): numE(e), numV(v), edges(new Edge[e]) {};
	~Graph() {
		cout << "destruct edgeds " << endl;
		delete [] edges;
	}
	bool hasCycle ();
};

int findRepresentive(int * &parent, int v) 
{
	if (parent[v] == -1) {
		return v;
	} else {
		return findRepresentive(parent, parent[v]);
	}
}

void unionSubset(int * &parent, int v1, int v2)
{
	int subSet1 = findRepresentive(parent, v1);
	int subSet2 = findRepresentive(parent, v2);
	parent[subSet1] = subSet2;
}

bool Graph::hasCycle() 
{
	int * parent = new int[numV];
	memset(parent, -1, sizeof(int) * numV);
	for (int i = 0; i < numE; ++i)
	{
		int x = findRepresentive(parent, edges[i].src);
		int y = findRepresentive(parent, edges[i].dest);
		if (x == y) {
			return true;
		}
		unionSubset(parent, x, y);
	}
	delete [] parent;
	return false;
}

int main(int argc, char const *argv[])
{
	/**
	 * let's create the following undirected graph
	 0
	 |  \
   |   \
	 1 - - 2 
	 */
	
	Graph g = Graph(3, 3);
	g.edges[0].src = 0;
	g.edges[0].dest = 1;
	g.edges[1].src = 0;
	g.edges[1].dest = 2;
	g.edges[2].src = 1;
	g.edges[2].dest = 2;
	if (g.hasCycle()) {
		cout << "The graph has a cycle!" << endl;
	} else {
		cout << "The graph doesn't have a cycle!" << endl;
	}
	return 0;
}

