#include "tree.h"

void initializeGraph(Graph &g, Graph::vertex_descriptor &start, Graph::vertex_descriptor &end, ifstream &fin)
// Initialize g using data from fin.  Set start and end equal
// to the start and end nodes.
{
	EdgeProperties e;

	int n, i, j;
	//int startId, endId;
	fin >> n;
	//fin >> startId >> endId;
	Graph::vertex_descriptor v;

	// Add nodes.
	for (int i = 0; i < n; i++)
	{
		v = add_vertex(g);
		//if (i == startId)
		//	start = v;
		//if (i == endId)
			//end = v;
	}

	while (fin.peek() != '.')
	{
		fin >> i >> j >> e.weight;
		add_edge(i, j, e, g);
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

	heap.buildMinHeap(heap.size(), g);
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

bool isConnected(Graph &g, Graph::vertex_descriptor start)
{
	bool isConnected = dijkstra(g, start); // dijkstra's algorithm will return true if every vertex in the graph is reachable
	return isConnected;
}

void clearVisited(Graph &g) // Mark all nodes in g as not visited.
{
	int numberOfVertices = num_vertices(g);
	for (int vertexIt = 0; vertexIt < numberOfVertices; vertexIt++) // for all vertices
	{
		g[vertex(vertexIt, g)].visited = false; // set visited to false

	}
}

void clearMarked(Graph &g) // Mark all nodes in g as not marked.
{
	int numberOfVertices = num_vertices(g);
	for (int vertexIt = 0; vertexIt < numberOfVertices; vertexIt++) // for all vertices
	{
		g[vertex(vertexIt, g)].marked = false; // set marked to false

	}
}

void dfs(Graph g, Graph::vertex_descriptor v, bool &isCyclic)
{
	stack<Graph::vertex_descriptor> s;
	Graph::vertex_descriptor current;
	clearVisited(g);
	s.push(v);
	pair<Graph::adjacency_iterator, Graph::adjacency_iterator> adjRange;
	while (!s.empty())
	{
		current = s.top();
		s.pop();
		if (g[current].visited) // if it makes it back to a node that was already visited then there is a cycle
		{
			isCyclic = true;
			return;
		}

		g[current].visited = true;

		adjRange = adjacent_vertices(current, g);
		for (Graph::adjacency_iterator adjIt = adjRange.first; adjIt != adjRange.second; adjIt++)
		{
			Graph::vertex_descriptor next = vertex(*adjIt, g);
			if (!g[next].visited)
			{
				s.push(next);
			}
		}
	}
}

bool isCyclic(Graph &g, Graph::vertex_descriptor v)
{
	bool isCyclic = false;
	dfs(g, v, isCyclic); 
	return isCyclic;
}

// using Prim's algorithm to find spanning tree (ends up giving minimum spanning tree
// Note: Chris Kenyon helped explain the method findSpanningTree
void findSpanningTree(Graph::vertex_descriptor s, Graph &g1, Graph &st)
{
	dijkstra(g1, s);
	map<size_t, size_t> mapForTree;
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g1);
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++)
	{
		if (g1[*vItr].weight != LargeValue) // if the vertex has a weight
		{
			mapForTree[*vItr] = add_vertex(g1[*vItr], st);
		}
	}

	Graph::vertex_descriptor u = s;

	// mark the start, keep track of the marked vertices in a vector
	vector<Graph::vertex_descriptor> markedVertices;
	g1[s].marked = true;
	g1[s].startVert = true;
	markedVertices.push_back(u);

	size_t target;
	size_t source;

	while (markedVertices.size() < num_vertices(st)) // do this until the number of marked vertices equals the total number of vertices
	{
		// initialize minimum weight and the total size of the marked vertices
		int minimumWeight = LargeValue;
		int vectorSize = markedVertices.size();

		for (int i = 0; i < vectorSize; i++)
		{
			u = markedVertices[i]; // update the current vertex
			pair<Graph::adjacency_iterator, Graph::adjacency_iterator> adjItrRange = adjacent_vertices(u, g1); // get all neighbors of the new vertex
			// goes through all neighbors to check which has the lowest weight and is not marked
			for (Graph::adjacency_iterator adjItr = adjItrRange.first; adjItr != adjItrRange.second; adjItr++)
			{
				Graph::vertex_descriptor v = *adjItr; // retreive adjacent vertex
				bool markedCheck = g1[v].marked; // get the value of adjacent vertex marked status

				if (!markedCheck) // checks to see if the adjacent vertex is not marked
				{
					Graph::edge_descriptor	e = edge(u, v, g1).first;
					if (g1[e].weight < minimumWeight)
					{
						minimumWeight = g1[e].weight;
						source = u;
						target = v;
					}
				}
			}
		}
		// add the new lowest path to the spanning tree and set it as marked so it is only reached once
		if (minimumWeight < LargeValue) // checks to make sure that the minimum weight just found is actually smaller than infinity (LargeValue)
		{
			EdgeProperties newEdge;
			newEdge.weight = minimumWeight;
			add_edge(mapForTree[source], mapForTree[target], newEdge, st); // add the edge to the spanning tree
			markedVertices.push_back(target); // push the target into marked vector then mark it
			g1[target].marked = true;
		}
	}
}

void findSpanningForest(Graph &g1, Graph &sf, int &treeIndex)
{
	// reset the graph to its original state
	clearMarked(g1);
	clearVisited(g1);

	pair<Graph::vertex_iterator, Graph::vertex_iterator> verts = vertices(g1);
	Graph::vertex_descriptor s = *verts.first; // first vertex as starting point
	treeIndex = 1; // updated so that the number of trees can be found
	bool unmarked = true; // bool to keep track if there are vertices that are unmarked

	while (unmarked)
	{
		Graph insertTree;  // this tree will get inserted to the spanning forest
		g1[s].startVert = true; // sets this as the start point
		g1[s].marked = true;
		findSpanningTree(s, g1, insertTree); // find spanning tree, updates insertTree

		// adding tree into spanning forest
		pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(insertTree);
		pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(insertTree);
		
		for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++)
		{
			add_vertex(insertTree[*vItr], sf); // adds vertices into spanning forest
		}

		for (Graph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; eItr++)
		{
			// copy an edge, and then get its vertices
			EdgeProperties newEdge;
			newEdge.weight = insertTree[*eItr].weight;
			newEdge.marked = insertTree[*eItr].marked;
			newEdge.visited = insertTree[*eItr].visited;
			Graph::vertex_descriptor u = source(*eItr, insertTree) + *vertices(sf).second; // add the first vertex_descriptor to make sure new vertex is in the correct location
			Graph::vertex_descriptor v = target(*eItr, insertTree) + *vertices(sf).second;

			add_edge(u, v, newEdge, sf); // add the edge to the spanning forest graph
		}

		/// This block of code checks to see if there is another vertex that is unmarked, if so then there is another tree that exists and needs to be added to the spanning forest
		unmarked = false; // assume that everything is marked because a spanning tree has been added
		pair<Graph::vertex_iterator, Graph::vertex_iterator> allVerts = vertices(g1);
		for (Graph::vertex_iterator vItr = allVerts.first; vItr != allVerts.second; vItr++)
		{
			Graph::vertex_descriptor vertCheck = *vItr;
			bool checkMarked = g1[vertCheck].marked; // checks to make sure all vertices are marked
			if (!checkMarked)
			{
				unmarked = true; // if all vertices are not marked then set this true
				s = vertCheck; // set the start point to the vertex that is being checked
				treeIndex += 1;
				break; // break out if any vertex is not marked
			}
		}
	}
}

int totalWeight(Graph &sf)
{
	int totalWeight = 0;
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(sf); // get all vertices
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++)
	{
		Graph::vertex_descriptor v = *vItr;
		totalWeight += sf[v].weight; // keep a running total of all weights of the spanning forest
	}
	return totalWeight;
}
