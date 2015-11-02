#include "grid.h"

grid::grid() 
{
}

grid::~grid()
{
}

void grid::createGrid(string givenFile)
{
	ifstream wordSearch = ifstream(givenFile);

	wordSearch >> columns >> rows; // reads row and column number

	for (int i = 0; i < rows; i++)
	{
		vector<char> nextRow(columns); 
		gridMatrix.push_back(nextRow);
		for (int j = 0; j < columns; j++)
		{
			wordSearch >> gridMatrix.at(i).at(j);
		}
	}
}





