#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;


class Cell
{
public:
	Cell();
	Cell(int num);
	~Cell();
	vector<int> possibilities; // possibilities that the cell could be
	void setValue(int setVal); // sets value in the cell
	int getValue(); // gets the value in the cell
	friend ostream &operator<<(ostream &ostr, Cell cell);
	void clearCell();
	void addConflict(int x);
	vector<int> getConflicts();
	bool assignedByBoard = false;  // will be set to true if assigned by board but by default is set to true
private:
	int value; // value of the cell

	vector<int> possibleConflicts;
};