#include "Wordlist.h"

class grid
{
public:
	grid();
	~grid();
	void createGrid(string givenFile);
	int rows;
	int columns;
	vector<vector<char>> gridMatrix; // declares matrix

};
