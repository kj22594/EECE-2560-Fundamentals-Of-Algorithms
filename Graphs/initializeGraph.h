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

using namespace std;
using namespace boost;


struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

struct VertexProperties
{
	pair<int, int> cell; // maze cell (x,y) value
	Graph::vertex_descriptor pred; // predecessor node
	int weight = 0;
	bool visited = false;
	bool marked = false;
};

// Create a struct to hold properties for each edge
struct EdgeProperties
{
	int weight = 0;
	bool visited = false;
	bool marked = false;
};

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;
typedef property<edge_weight_t, int> EdgeProperty;

void initializeGraph(Graph &g, Graph::vertex_descriptor &start, Graph::vertex_descriptor &end, ifstream &fin);