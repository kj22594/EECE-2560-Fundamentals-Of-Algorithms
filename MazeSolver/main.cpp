#include <iostream>
#include <limits.h>
#include <vector>
#include <list>
#include <fstream>
#include <queue>
#include "maze.h"

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
   
int main()
{
   try
   {
      ifstream fin;
	
      // Read the maze from the file.
      string fileName = "maze0.txt";
      
      fin.open(fileName.c_str());
      if (!fin)
      {
         cerr << "Cannot open " << fileName << endl;
         exit(1);
      }

      maze m(fin);
      fin.close();
      
      m.print(m.numRows()-1,m.numCols()-1,0,0);

      Graph g(m.numRows() * m.numCols()); // initializes the graph as the size of the maze
      m.mapMazeToGraph(g); // graph g is created from the maze
	  
	  Graph::vertex_descriptor startOfMaze = vertex(0, g); // beginning vertex of the maze
	  pair<int, int> endOfMaze(m.numRows() - 1, m.numCols() - 1); // initializes the end of the maze
	  int totalVertices = num_vertices(g); // gets total # of vertices
	  stack<Graph::vertex_descriptor> testPath; // create path that can be used to for print path


	 clearVisited(g); // clears visited vertices
	 testPath = findPathDFSRecursively(g, startOfMaze, endOfMaze); // gets a path to complete the maze
	 m.printPath(totalVertices, testPath, g); // prints path using DFS
	 system("cls");

	 clearVisited(g); 
	 testPath = findShortestPathDFSRecursively(g, startOfMaze, endOfMaze); // gets the shortest path to complete the maze
	 m.printPath(totalVertices, testPath, g); // prints shortest path using DFS
	 system("cls");
	  
	 clearVisited(g);
	 testPath = findPathDFSStack(g,startOfMaze,endOfMaze); // gets path using DFS stack logic
	 m.printPath(totalVertices, testPath, g); // prints path using DFS with a stack
	 system("cls");

	 clearVisited(g);
	 testPath = findPathBFS(g, startOfMaze, endOfMaze); // BFS finds shortest path from start to every node
	 m.printPath(totalVertices, testPath, g); // prints shortest path using BFS
	  

      // cout << g << endl;   may be used in later implementations but unnecessary for this project
   }
   catch (indexRangeError &ex)
   {
	   cout << ex.what() << endl;
	   exit(1);
   }
}