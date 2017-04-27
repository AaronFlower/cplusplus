#include <iostream>
#include <algorithm>

using namespace std;

struct Edge
{
	int src;
	int dest;
	int weight;
};

class Graph
{
public:
	int numV;
	int numE;
	Edge * edges;
public:
	Graph(int v, int e): numV(v), numE(e), edges(new Edge[e]){};
	~Graph(){
		delete [] edges;
	};
	Graph createMST();
	void printGraph();
private: 
	int find(int * & parents, int v);
	void unionSet(int * & parents, int v1, int v2);
};

void Graph::printGraph()
{
	for (int i = 0; i < numE; ++i)
	{
		cout << edges[i].src << " ---- " << edges[i].dest << "(" << edges[i].weight << ")" << endl;
	}
}

int Graph::find(int * & parents, int v )
{
	if (parents[v] == -1) {
		return v;
	}
	return find(parents, parents[v]);
}

void Graph::unionSet(int * & parents, int v1, int v2)
{
	int repX, repY;
	repX = find(parents, v1);
	repY = find(parents, v2);
	parents[repX] = repY;
}

/**
 * 创建 Minmum Spanning Tree
 */
Graph Graph::createMST()
{
	Graph mst = Graph(numV, numV - 1);
	sort(edges, edges + numE, [](Edge a, Edge b) {
		return a.weight < b.weight;
	});
	int * parents = new int[numV];
	memset(parents, -1, sizeof(int) * numV);
	int v = 0;
	int i = 0;
	int repSrc, repDest;
	while( v < numV - 1) {
		Edge edge = edges[i++];
		repSrc = find(parents, edge.src);
		repDest = find(parents, edge.dest);
		if (repSrc != repDest) {
			mst.edges[v++] = edge;
			unionSet(parents, repSrc, repDest);
		}
	}
	return mst;
}

int main(int argc, char const *argv[])
{
	/* Let us create following weighted graph
	         10
	    0--------1
	    |  \     |
	   6|   5\   |15
	    |      \ |
	    2--------3
	        4       */
	int V = 4;  // Number of vertices in graph
	int E = 5;  // Number of edges in graph
	Graph g = Graph(V, E);
	// add edge 0-1
	g.edges[0].src = 0;
	g.edges[0].dest = 1;
	g.edges[0].weight = 10;
	
	// add edge 0-2
	g.edges[1].src = 0;
	g.edges[1].dest = 2;
	g.edges[1].weight = 6;
	
	// add edge 0-3
	g.edges[2].src = 0;
	g.edges[2].dest = 3;
	g.edges[2].weight = 5;
	
	// add edge 1-3
	g.edges[3].src = 1;
	g.edges[3].dest = 3;
	g.edges[3].weight = 15;
	
	// add edge 2-3
	g.edges[4].src = 2;
	g.edges[4].dest = 3;
	g.edges[4].weight = 4;
	
	Graph mst = g.createMST();
	mst.printGraph();
	return 0;
}


