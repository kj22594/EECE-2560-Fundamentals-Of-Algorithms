#include "initializeGraph.h"
#include "heapV.h"
#include <fstream>


// output operator for vertex properties
ostream& operator<<(ostream &ostr, const VertexProperties &vertProp)
{
	ostr << "Cell value: " << "(" << vertProp.cell.first << "," << vertProp.cell.second << ")" << endl;
	ostr << "Visited: " << vertProp.visited << endl;
	ostr << "Pred: " << vertProp.pred << endl;
	ostr << "Weight: " << vertProp.weight << endl;
	ostr << "Marked: " << vertProp.marked << endl;

	return ostr;
}

// output operator for edge properties
ostream& operator<<(ostream &ostr, const EdgeProperties &edgeProp)
{
	ostr << "Visited: " << edgeProp.visited << endl;
	ostr << "Weight: " << edgeProp.weight << endl;
	ostr << "Marked: " << edgeProp.marked << endl;

	return ostr;
}

// output operator for graph properties
ostream& operator<<(ostream &ostr, const Graph &g)
{
	typedef graph_traits<Graph>::vertex_iterator vertex_iter;
	typedef graph_traits<Graph>::edge_iterator edge_iter;

	pair<vertex_iter, vertex_iter> vert;
	pair<edge_iter, edge_iter> edg;
	edge_iter edg_it, edg_it_end;

	for (vert = vertices(g); vert.first != vert.second; vert.first++)
	{
		ostr << "Vertex Property:" << endl;
		ostr << g[*vert.first] << endl;
	}

	ostr << endl; // blank line between vertex & edge output

	for (tie(edg_it, edg_it_end) = edges(g); edg_it != edg_it_end; edg_it++)
	{
		ostr << "Edge Property:" << endl;
		ostr << g[*edg_it] << endl;
	}

	return ostr;
}

// Forward declaration of functions needed for Project 5c
void relax(Graph &g, Graph::vertex_descriptor u, Graph::vertex_descriptor v);
bool dijkstra(Graph &g, Graph::vertex_descriptor s);
bool bellmanFord(Graph &g, Graph::vertex_descriptor s);
void print(Graph &g, Graph::vertex_descriptor startNode, pair<Graph::vertex_iterator, Graph::vertex_iterator> allVerts);


int main()
{
	try {
		ifstream fin;
		string graphFile;
		cout << "Which graph would you like to use?" << endl;
		cin >> graphFile;
		fin.open(graphFile.c_str());


		Graph g;
		pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g); // gets vertices of graph
		Graph::vertex_descriptor start = vertex(*vItrRange.first, g); // gets start vertex
		Graph::vertex_descriptor end = vertex(*vItrRange.second, g); // gets end vertex
		initializeGraph(g, start, end, fin); // initializes the graph
		fin.close();

		// For dijkstra's algorithm
		Graph::vertex_descriptor vert = vertex(0, g); // Note: start node is index 0
		bool dijkstraA = dijkstra(g, vert);
		if (dijkstraA)
		{
			pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g); // gets vertices of graph
			print(g, 0, vItrRange);
		}
		else
			cout << "Path to end node is not reachable" << endl;
		system("pause");

		// For Bellman-Ford's algorithm
		if (bellmanFord(g, vert))
		{
			pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g); // gets vertices of graph
			print(g, 0, vItrRange);
		}
		else
			cout << "Path to end node is not reachable" << endl;
	}
	catch (indexRangeError ex)
	{
		cout << ex.what() <<endl;
		exit(1);
	}
}

void relax(Graph &g, Graph::vertex_descriptor u, Graph::vertex_descriptor v)
{
	pair<Graph::edge_descriptor, bool> checkEdge = edge(u, v, g); // get the edge between the two nodes passed in
	if (checkEdge.second) // checks to see if the edge exists
	{
		int weightOfV = g[v].weight;
		int weightOfU = g[u].weight;
		int weightOfEdge = g[checkEdge.first].weight;
		if (weightOfV > weightOfU + weightOfEdge) // if the shortest path to v is greater than that of the shortest path to u + the edge length then update the shortest path to v
		{
			weightOfV = weightOfU + weightOfEdge;
			g[v].weight = weightOfV; // assigns a new weight to v
			g[v].pred = u; // assigns u as the pred of v
		}
	}
}


bool dijkstra(Graph &g, Graph::vertex_descriptor s)
{
	heapV<Graph::vertex_descriptor, Graph> heap; // create a heap, used for priority queue
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g); // gets all vertices
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++)
	{
		if (*vItr == s)
		{
			g[*vItr].weight = 0; // the start vertex will always have a shortest path of 0 to itself
			g[*vItr].pred = SmallValue;
			heap.minHeapInsert(*vItr, g); // insert into min heap

		}

		if (*vItr != s)
		{
			// Note LargeValue denotes INF, SmallValue denotes Undefined
			g[*vItr].weight = LargeValue;
			g[*vItr].pred = SmallValue; 
			heap.minHeapInsert(*vItr, g); // insert into min heap
		}
	}

	while (heap.size() > 0)
	{
		Graph::vertex_descriptor u = heap.extractMinHeapMinimum(g); // extract minimum from graph g
		pair<Graph::adjacency_iterator, Graph::adjacency_iterator> adjRange = adjacent_vertices(u, g);
		for (Graph::adjacency_iterator adjItr = adjRange.first; adjItr != adjRange.second; adjItr++)
		{
			Graph::vertex_descriptor v = *adjItr; // set v to be a neighbor
			relax(g, u, v); // relax u & v to make sure the minimum path is set 
			
			try 
			{
				int index = heap.getIndex(v);
				heap.minHeapDecreaseKey(index, g); // decreases priority in the priority queue
			}
			catch (rangeError ex)
			{
				continue;
			}
		}
	}

	pair<Graph::vertex_iterator, Graph::vertex_iterator> allVerts = vertices(g);
	for (Graph::vertex_iterator vert = allVerts.first; vert != allVerts.second; vert++)
	{
		if (g[*vert].weight == LargeValue)
		{
			return false; // if any of the nodes isn't reachable then the weight will still be INF/LargeValue
		}
	}
	return true;
}

bool bellmanFord(Graph &g, Graph::vertex_descriptor s)
{
	
	// Initialize the graph
	pair<Graph::vertex_iterator, Graph::vertex_iterator> verts = vertices(g);
	for(Graph::vertex_iterator vItr = verts.first; vItr != verts.second; vItr++)
	{
		g[*vItr].pred = NULL;  // set predecessor to null
		g[*vItr].weight = LargeValue; // set every weight to inf
	}
	g[s].weight = 0; // start point weight is 0
	
	// Relaxation
	pair<Graph::edge_iterator, Graph::edge_iterator> edgeRange = edges(g); // retrieves all edges in the graph
	int totalVerts = num_vertices(g);
	for (int i = 1; i < totalVerts; i++)
	{
		for (Graph::edge_iterator edgeItr = edgeRange.first; edgeItr != edgeRange.second; edgeItr++)
		{
			Graph::vertex_descriptor u = source(*edgeItr, g); // retrieves source vertex 
			Graph::vertex_descriptor v = target(*edgeItr, g); // retrieves target vertex
			relax(g, u, v); // relax edges but the return value here doesn't matter
		}
	}

	// Check for negative weights
	for (Graph::edge_iterator edgeItr = edgeRange.first; edgeItr != edgeRange.second; edgeItr++)
	{
		Graph::vertex_descriptor u = source(*edgeItr, g); // retrieves source vertex 
		Graph::vertex_descriptor v = target(*edgeItr, g); // retrieves target vertex
		int negCheck = g[u].weight + g[*edgeItr].weight;
		if(negCheck < g[v].weight)
		{
			return false; // return false if theres a negative path included
		}
	}
	return true;
}

stack<Graph::vertex_descriptor> createStack(Graph &g, Graph::vertex_descriptor vert)
{
	stack<Graph::vertex_descriptor> printStack;
	Graph::vertex_descriptor updatedVert = vert; // starts out as vert, ends up becoming the predecessor of vert
	while (updatedVert != NULL) // updatedVert will be NULL after the start is added on
	{
		printStack.push(updatedVert);
		updatedVert = g[updatedVert].pred;
	}
	return printStack;
}

// Print takes the start node because that is going to be the last vertex visited
void print(Graph &g, Graph::vertex_descriptor startNode, pair<Graph::vertex_iterator, Graph::vertex_iterator> allVerts)
{
	for (Graph::vertex_iterator vItr = allVerts.first; vItr != allVerts.second; vItr++)
	{
		stack<Graph::vertex_descriptor> printStack = createStack(g,*vItr); 		// initializes the stack
		cout << "Shortest Path (" << startNode << " to " << *vItr << "):" << " ";
		if (printStack.size() == 0)
		{
			cout << startNode;
		}
		else
			cout << startNode << " to ";
		while (!printStack.empty())
		{
			if (printStack.size() == 1)
			{
				cout << printStack.top();
			}
			else
			{
				cout << printStack.top() << " to ";
			}
			printStack.pop();
		}
		cout << endl;
	}
}