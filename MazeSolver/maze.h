// Sample solution for project #5

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

#define LargeValue 99999999

using namespace std;
using namespace boost;


struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

struct VertexProperties
{
	pair<int, int> cell; // maze cell (x,y) value
	Graph::vertex_descriptor pred; // predecessor node
	int weight=0;
	bool visited=false;
	bool marked=false;
};

// Create a struct to hold properties for each edge
struct EdgeProperties
{
	int weight=0;
	bool visited=false;
	bool marked=false;
};

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;
// typedef property<edge_weight_t, int> EdgeProperty;

void setNodeWeights(Graph &g, int w);
void clearMarked(Graph &g);
void clearVisited(Graph &g);
void clearPred(Graph &g, Graph::vertex_descriptor v); // clears pred of only 1 node

// findPathDFSRecursive
stack<Graph::vertex_descriptor> findPathDFSRecursively(Graph &g, Graph::vertex_descriptor startPoint, pair<int, int> endOfMaze);
bool recursivelyFindPathDFS(Graph &g, pair<int, int> endOfMaze, Graph::vertex_descriptor startPoint, stack<Graph::vertex_descriptor> &path);

// findShortestPathDFSRecursively
void recursivelyFindShortestPathDFS(Graph &g, pair<int, int> endOfMaze, Graph::vertex_descriptor startPoint, stack<Graph::vertex_descriptor> &path);
stack<Graph::vertex_descriptor> findShortestPathDFSRecursively(Graph &g, Graph::vertex_descriptor startPoint, pair<int, int> endOfMaze);

// findPathDFSStack
stack<Graph::vertex_descriptor> findPathDFSStack(Graph &g, Graph::vertex_descriptor startOfMaze, pair<int, int> endOfMaze);

// findPathBFS
stack<Graph::vertex_descriptor> findPathBFS(Graph &g, Graph::vertex_descriptor startOfMaze, pair<int, int> endOfMaze); // returns a stack because the print maze function uses a stack not a queue


class maze
{
public:
   maze(ifstream &fin);
   void print(int,int,int,int);
   bool isLegal(int i, int j);
   void mapMazeToGraph(Graph &g);
   void printPath(Graph::vertex_descriptor end, stack<Graph::vertex_descriptor> &s, Graph g);
   int numRows(){return rows;};
   int numCols(){return cols;};

private:
   int rows; // number of rows in the maze
   int cols; // number of columns in the maze
   
   matrix<bool> value;
};


