#include <iostream>
#include <limits.h>
#include <list>
#include <fstream>
#include <queue>
#include <vector>
#include <stack>

#include "d_except.h"
#include "d_matrix.h"
#include "boost\graph\adjacency_list.hpp"
#include "heapV.h"

using namespace std;
using namespace boost;


struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

struct VertexProperties
{
	pair<int, int> cell; // maze cell (x,y) value
	Graph::vertex_descriptor pred = NULL; // predecessor node
	int weight = 0;
	bool visited = false;
	bool marked = false;
	bool startVert = false; // added to make a print flag for the start vertex
};

// Create a struct to hold properties for each edge
struct EdgeProperties
{
	int weight = LargeValue;
	bool visited = false;
	bool marked = false;
};

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;
typedef property<edge_weight_t, int> EdgeProperty;

// needed for checking if connected
bool dijkstra(Graph &g, Graph::vertex_descriptor s);
void relax(Graph &g, Graph::vertex_descriptor u, Graph::vertex_descriptor v);

// needed for checking if cyclic
void clearVisited(Graph &g);
void clearMarked(Graph &g);
void dfs(Graph g, Graph::vertex_descriptor v);

// initialize graph
void initializeGraph(Graph &g, Graph::vertex_descriptor &start, Graph::vertex_descriptor &end, ifstream &fin);

// functions for Project 6a
void findSpanningTree(Graph::vertex_descriptor s, Graph &g1, Graph &st);
void findSpanningForest(Graph &g1, Graph &sf, int &treeIndex);
bool isConnected(Graph &g);
bool isCyclic(Graph &g, Graph::vertex_descriptor);
int totalWeight(Graph &sf);