#include "maze.h"

// used by shortest path DFS recursive functions
stack<Graph::vertex_descriptor> shortestPath; // holds the shortest path for the find shortest path (using recursive DFS)
int shortestPathLength = 0; // length of the shortest path

maze::maze(ifstream &fin)
// Initializes a maze by reading values from fin.  Assumes that the
// number of rows and columns indicated in the file are correct.
{
	fin >> rows;
	fin >> cols;

	char x;

	value.resize(rows, cols);
	for (int i = 0; i <= rows - 1; i++)
		for (int j = 0; j <= cols - 1; j++)
		{
			fin >> x;
			if (x == 'O')
				value[i][j] = true;
			else
				value[i][j] = false;
		}

}

void maze::print(int goalI, int goalJ, int currI, int currJ)
// Print out a maze, with the goal and current cells marked on the
// board.
{
	cout << endl;

	if (goalI < 0 || goalI > rows || goalJ < 0 || goalJ > cols)
		throw rangeError("Bad value in maze::print");

	if (currI < 0 || currI > rows || currJ < 0 || currJ > cols)
		throw rangeError("Bad value in maze::print");

	for (int i = 0; i <= rows - 1; i++)
	{
		for (int j = 0; j <= cols - 1; j++)
		{
			if (i == goalI && j == goalJ)
				cout << "*";
			else
				if (i == currI && j == currJ)
					cout << "+";
				else
					if (value[i][j])
						cout << " ";
					else
						cout << "X";
		}
		cout << endl;
	}
	cout << endl;
}

bool maze::isLegal(int i, int j)
// Return the value stored at the (i,j) entry in the maze, indicating
// whether it is legal to go to cell (i,j).
{
	if (i < 0 || i > rows || j < 0 || j > cols)
		throw rangeError("Bad value in maze::isLegal");

	return value[i][j];
}

void maze::mapMazeToGraph(Graph &g) // Create a graph g that represents the legal moves in the maze m.
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int vertexNumber = (i * cols) + j;
			g[vertex(vertexNumber, g)].weight = 1; // no weight at the moment
			g[vertex(vertexNumber, g)].marked = false;  // marked starts as false
			g[vertex(vertexNumber, g)].visited = false; // by default no vertex is "visited"
			g[vertex(vertexNumber, g)].cell = pair<int, int>(i, j); // setting vertex to a cell
			if (!isLegal(i, j))
			{
				continue;
			}
			else
			{
				if (i != rows - 1) // create down
				{
					if (isLegal(i + 1, j))
					{
						add_edge(vertexNumber, vertexNumber + cols, g);
					}
				}

				if (i > 0) // create up
				{
					if (isLegal(i - 1, j))
					{
						add_edge(vertexNumber, vertexNumber - cols, g);
					}
				}

				if (j != cols - 1) // creates right
				{
					if (isLegal(i, j + 1))
					{
						add_edge(vertexNumber, vertexNumber + 1, g);
					}
				}

				if (j > 0) // creates left
				{
					if (isLegal(i, j - 1))
					{
						add_edge(vertexNumber, vertexNumber - 1, g);
					}
				}
			}
		}
	}
}

void maze::printPath(Graph::vertex_descriptor end, stack<Graph::vertex_descriptor> &s, Graph g)
{
	while (!s.empty())
	{
		print(rows - 1, cols - 1, g[s.top()].cell.first, g[s.top()].cell.second); // assumes the goal is always bottom righthand corner, gets the values of the starting point on the graph
		s.pop(); // moves through the path
		system("pause");
	}
}

void clearVisited(Graph &g) // Mark all nodes in g as not visited.
{
	int numberOfVertices = num_vertices(g);
	for (int vertexIt = 0; vertexIt < numberOfVertices; vertexIt++) // for all vertices
	{
		g[vertex(vertexIt, g)].visited = false; // set visited to false
	}
}

void setNodeWeights(Graph &g, int w) // Set all node weights to w.
{
	int numberOfVertices = num_vertices(g);
	for (int vertexIt = 0; vertexIt < numberOfVertices; vertexIt++) // for all vertices
	{
		g[vertex(vertexIt, g)].weight = w; // set weight to w
	}


	// Logic for setting weight of edges
	/*
		for (int edgesIt = 0; edgesIt < num_edges(g); edgesIt++)
	{
		g[edge(edgeIt, g)].weight = w; // set weight to w
	}
	*/
}

void clearMarked(Graph &g)
{
	int numberOfVertices = num_vertices(g);
	for (int vertexIt = 0; vertexIt < numberOfVertices; vertexIt++) // for all vertices
	{
		g[vertex(vertexIt, g)].marked = false; // set marked to false
	}
}

void clearPred(Graph &g, Graph::vertex_descriptor v) // clears the pred of one node
{
	g[v].pred = NULL;
}

bool recursivelyFindPathDFS(Graph &g, pair<int, int> endOfMaze, Graph::vertex_descriptor startPoint, stack<Graph::vertex_descriptor> &path)
{
	g[startPoint].visited = true; // visits current node
	pair<int, int> currentCell = g[startPoint].cell;
	if (currentCell == endOfMaze) // check to see if the current vertex is the end of the maze
	{
		path.push(startPoint); // this will push the last node in the graph
		return true; // path exists so returns true
	}

	pair<Graph::adjacency_iterator, Graph::adjacency_iterator> adjRange = adjacent_vertices(startPoint, g);

	for (Graph::adjacency_iterator adjIt = adjRange.first; adjIt != adjRange.second; adjIt++) // this loop will not be accessed when the end of the maze is reached
	{
		Graph::vertex_descriptor newNode = vertex(*adjIt, g);
		if (!g[newNode].visited && recursivelyFindPathDFS(g, endOfMaze, newNode, path)) // if recursive call returns true
		{
				path.push(startPoint);  // this logic eliminates having to pop if the wrong path is chosen
				return true;
		}
	}
	return false; // otherwise return false
}

stack<Graph::vertex_descriptor> findPathDFSRecursively(Graph &g, Graph::vertex_descriptor startPoint, pair<int, int> endOfMaze)
{
	stack<Graph::vertex_descriptor> path;
	Graph::vertex_descriptor first = startPoint; // first vertex descriptor of graph
	bool pathExists = recursivelyFindPathDFS(g, endOfMaze, first, path); // updates path
	if (!pathExists) // if there is not a path
	{
		cout << "No Path Exists" << endl; 
		return path; // returns empty path
	}
	clearVisited(g);  // clears the visited nodes of the graph
	return path;
}

void recursivelyFindShortestPathDFS(Graph &g, pair<int, int> endOfMaze, Graph::vertex_descriptor startPoint, stack<Graph::vertex_descriptor> &path)
{
	// visit current node then push to the path
	g[startPoint].visited = true;
	path.push(startPoint);

	if (g[startPoint].cell == endOfMaze) // check to see if the current vertex is the end of the maze
	{
		int sizeOfPath = path.size();
		// checks to see what the shortest path size is and updates it if necessary along with updating the shortest path
		if (shortestPathLength > sizeOfPath || (shortestPathLength == 0 && shortestPath.empty()) )
		{
			shortestPathLength = path.size();
			shortestPath = path;
		}
	}

	pair<Graph::adjacency_iterator, Graph::adjacency_iterator> adjRange = adjacent_vertices(startPoint, g);

	for (Graph::adjacency_iterator adjIt = adjRange.first; adjIt != adjRange.second; adjIt++)
	{
		Graph::vertex_descriptor newNode = vertex(*adjIt, g);
		if (!g[newNode].visited) // if the new current node isn't visited
		{
			recursivelyFindShortestPathDFS(g, endOfMaze, newNode, path);
		}
	}
	// after recursive call pop the path and unvisit the nodes   -> backtracking to find another path
	path.pop();  
	g[startPoint].visited = false;
}

stack<Graph::vertex_descriptor> findShortestPathDFSRecursively(Graph &g, Graph::vertex_descriptor startPoint, pair<int, int> endOfMaze)
{
	stack<Graph::vertex_descriptor> path;
	Graph::vertex_descriptor first = startPoint; // first vertex descriptor of graph
	recursivelyFindShortestPathDFS(g, endOfMaze, first, path);
	if (shortestPath.size() == 0)
	{
		cout << "No Path Exists" << endl;
		return shortestPath; // returns empty path
	}
	clearVisited(g);  // clears the visited nodes of the graph
	stack<Graph::vertex_descriptor> shortestPathInOrder;
	while (!shortestPath.empty()) // reverses the stack so that the top of the stack is the start of the maze
	{
		shortestPathInOrder.push(shortestPath.top()); 
		shortestPath.pop();
	}
	return shortestPathInOrder; // returns the stack from start to finish 
}

stack<Graph::vertex_descriptor> findPathDFSStack(Graph &g, Graph::vertex_descriptor startOfMaze, pair<int, int> endOfMaze)
{
	clearVisited(g);
	stack<Graph::vertex_descriptor> path, x;
	Graph::vertex_descriptor startNode = startOfMaze;
	clearPred(g, startNode);
	pair<Graph::adjacency_iterator, Graph::adjacency_iterator> adjRange;
	
	path.push(startNode); // push first node to stack
	g[startNode].visited = true; // visit right after pushing
	while (!path.empty())
	{
		startNode = path.top();
		path.pop();

		// just in case something happen where the node doesn't get visited
		if (g[startNode].visited == false)
		{
			g[startNode].visited = true;
		}

		pair<int, int> currentCell = g[startNode].cell;
		if (currentCell == endOfMaze)
		{
			break;  // breaks out of while loop if the current cell is the end of the maze
		}
		adjRange = adjacent_vertices(startNode, g);
		for (Graph::adjacency_iterator adjIt = adjRange.first; adjIt != adjRange.second; adjIt++)
		{
			Graph::vertex_descriptor nextNode = vertex(*adjIt, g);
			if (!g[nextNode].visited)
			{
				path.push(nextNode);
				g[nextNode].visited = true;
				g[nextNode].pred = startNode; // update pred so that it can be used later for creating returnPath
			}
		}
	}
	
	stack<Graph::vertex_descriptor> returnPath; // path that is going to be returned
	if (g[startNode].cell != endOfMaze)
	{
		cout << "No Path Exists" << endl;
		return returnPath; // returns empty path if no path exists
	}

	Graph::vertex_descriptor stackInput = startNode;
	while (stackInput != NULL)
	{
		returnPath.push(stackInput);
		stackInput = g[stackInput].pred; // keep track of the pred of each node, this way there is still the ability to track the end path even though the stack pops
	}

	return returnPath;
}

stack<Graph::vertex_descriptor> findPathBFS(Graph &g, Graph::vertex_descriptor startOfMaze, pair<int, int> endOfMaze)
{
	queue<Graph::vertex_descriptor> path;
	Graph::vertex_descriptor startNode = startOfMaze;
	clearPred(g, startNode);
	pair<Graph::adjacency_iterator, Graph::adjacency_iterator> adjRange;

	path.push(startNode);

	while (!path.empty())
	{
		startNode = path.front();
		g[startNode].visited = true;
		adjRange = adjacent_vertices(startNode, g);
		for (Graph::adjacency_iterator adjIt = adjRange.first; adjIt != adjRange.second; adjIt++)
		{
			Graph::vertex_descriptor nextNode = vertex(*adjIt, g);
			if (!g[nextNode].visited)
			{
				g[nextNode].pred = startNode; // keep track of the pred of each node, this way there is still the ability to track the end path even though the queue pops
				path.push(nextNode);
			}
		}
		path.pop();
	}

	stack<Graph::vertex_descriptor> returnPath; // the path that is going to be returned
	if (g[startNode].cell != endOfMaze)
	{
		cout << "No Path Exists" << endl;
		return returnPath; // returns empty path if no path exists
	}

	Graph::vertex_descriptor stackInput = startNode;
	while (stackInput != NULL)
	{
		returnPath.push(stackInput);
		stackInput = g[stackInput].pred; // uses pred to keep track of the path
	}

	return returnPath;
}
