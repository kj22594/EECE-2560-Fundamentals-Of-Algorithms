#include "tree.h"

// output operator for vertex properties
ostream& operator<<(ostream &ostr, const VertexProperties &vertProp)
{
	ostr << "Pred: " << vertProp.pred << endl;
	ostr << "Weight: " << vertProp.weight << endl;

	return ostr;
}

// output operator for edge properties
ostream& operator<<(ostream &ostr, const EdgeProperties &edgeProp)
{
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
		if (g[*vert.first].weight != LargeValue)
		{
			ostr << "Vertex Property:" << endl;
			ostr << g[*vert.first] << endl;
		}
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

		Graph sf;
		int treeIndex;

		findSpanningForest(g, sf, treeIndex);
		cout << sf << endl; // prints graph description
		system("pause");

		cout << "Total number of trees: " << treeIndex << endl; // prints number of trees
		cout << endl;
		system("pause");

		int totalWeightOfSpanningForest = totalWeight(sf);
		cout << "Total weight of the spanning forest: " << totalWeightOfSpanningForest << endl; // prints total weight of the forest
		cout << endl;
		system("pause");


		if (!isCyclic(sf, 0)) //  Check to make sure isCyclic works
		{
			cout << "This is a spanning forest" << endl;
			cout << endl;
		}

		system("pause");
		return 0;
	}
	catch (indexRangeError ex)
	{
		cout << ex.what() << endl;
		exit(1);
	}
}

