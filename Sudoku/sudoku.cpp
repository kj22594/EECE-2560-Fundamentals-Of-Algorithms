// Declarations and functions for the Sudoku project

#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>
#include "Cell.h"

using namespace std;

const int Blank = -1;  // Indicates that a cell is blank

const int SquareSize = 3;  //  The number of cells in a small square
						   //  (usually 3).  The board has
						   //  SquareSize^2 rows and SquareSize^2
						   //  columns.

const int BoardSize = SquareSize * SquareSize;

const int MinValue = 1;
const int MaxValue = 9;

int numSolutions = 0;
int counter = 0; // global variable counter, will get incremented every time solveBoard is called 
class board
	// Stores the entire Sudoku board
{
public:
	board(int);
	void clear();
	void initialize(ifstream &fin);
	void print();
	bool isBlank(int, int);
	Cell getCell(int, int);
	void setCell(int i, int j, const Cell& val);
	void clearCell(int i, int j);
	bool isSolved();
	void setConflicts(int row, int column,Cell &cell);
	void updateConflicts();
	void printConflicts();

	// Implemented for 4b
	void solveBoard();
	void findCellWithLeastPossibilities(int &x, int &y);

private:

	// The following matrices go from 1 to BoardSize in each
	// dimension.  I.e. they are each (BoardSize+1) X (BoardSize+1)
	matrix<Cell> value;

};

board::board(int sqSize)
   : value(BoardSize+1,BoardSize+1)
// Board constructor
{
	clear(); // initializes the board as a cleared board
}

void board::clear()
// Clear the entire board.
{
	counter = 0;
	for (int i = 1; i <= BoardSize; i++)
	{
		for (int j = 1; j <= BoardSize; j++)
		{
			value[i][j].clearCell();
			
		}
	}
}

void  board::setCell(int i,int j, const Cell& val)
// set cell i,j to val and update conflicts
{
	value[i][j] = val;
	updateConflicts();
}

void board::initialize(ifstream &fin)
// Read a Sudoku board from the input file.
{
   char ch;

   clear();
   for (int i = 1; i <= BoardSize; i++)
      for (int j = 1; j <= BoardSize; j++)
      {
		 fin >> ch;

         // If the read char is not Blank
		if (ch != '.')
		{
		    setCell(i,j,Cell(ch-'0'));   // Convert char to int
		}
      }
   updateConflicts();
}

int squareNumber(int i, int j)
// Return the square number of cell i,j (counting from left to right,
// top to bottom.  Note that i and j each go from 1 to BoardSize
{
   // Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
   // coordinates of the square that i,j is in.  

   return SquareSize * ((i-1)/SquareSize) + (j-1)/SquareSize + 1;
}

ostream &operator<<(ostream &ostr, vector<int> &v)
// Overloaded output operator for vector class.
{
   for (int i = 0; i < v.size(); i++)
      ostr << v[i] << " ";
   ostr << endl;
   return ostr;
}



Cell board::getCell(int i, int j)
// Returns the value stored in a cell.  Throws an exception
// if bad values are passed.
{
   if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
      return value[i][j];
   else
      throw rangeError("bad value in getCell");
}

void board::clearCell(int i, int j)
{
	value[i][j].clearCell();
	updateConflicts();
}

bool board::isBlank(int i, int j)
// Returns true if cell i,j is blank, and false otherwise.
{
   if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
      throw rangeError("bad value in setCell");

   int check = getCell(i, j).getValue();
   return (check == Blank); // if the value of the given cell is equal to blank(-1) then isBlank will return true
}

void board::print()
// Prints the current board.
{
   for (int i = 1; i <= BoardSize; i++)
   {
      if ((i-1) % SquareSize == 0)
      {
         cout << " -";
	 for (int j = 1; j <= BoardSize; j++)
	    cout << "---";
         cout << "-";
	 cout << endl;
      }
      for (int j = 1; j <= BoardSize; j++)
      {
	 if ((j-1) % SquareSize == 0)
	    cout << "|";
	 if (!isBlank(i,j))
	    cout << " " << getCell(i,j).getValue() << " ";
	 else
	   cout << "   ";
      }
      cout << "|";
      cout << endl;
   }

   cout << " -";
   for (int j = 1; j <= BoardSize; j++)
      cout << "---";
   cout << "-";
   cout << endl;
}

bool board::isSolved()
{
	bool isSolved = true;
	updateConflicts();
	for (int i = 1; i <= BoardSize; i++)
	{
		for (int j = 1; j <= BoardSize; j++)
		{
			if (isBlank(i, j))  // if this returns true for any single cell then it isn't solved
			{
				isSolved = false;
			}
		}
	}
	return isSolved;
}

void board::setConflicts(int row, int column, Cell &cell) // i and j are the indices for the cell in the matrix
{
	cell.getConflicts().clear();  // clears possible conflicts for the cell passed in
	
	int rows = value.rows();
	int cols = value.cols();


		// sets column conflicts
		for (int i = 1; i < cols; i++) // column is changing
		{
			if (cell.assignedByBoard == true)
			{
				break;
			}
			if (i != column)
			{
				cell.addConflict(value[row][i].getValue()); // adds that cell value into the possibleConflicts
			}
		}

		// sets row conflicts

		for (int i = 1; i < rows; i++) // row is changing
		{
			if (cell.assignedByBoard == true)
			{
				break;
			}
			if (i != row)
			{
				cell.addConflict(value[i][column].getValue());
			}
		}

		// sets square conflicts
		int x = column - ((column-1) % SquareSize);       // y coordinate for square
		int y = row - ((row - 1) % SquareSize);           // x coordinate for square
		for (int i = x; i < x + SquareSize; i++)          // these two loops check everything in a square that is of size SquareSize x SquareSize (3x3 in our case)
		{
			for (int j = y; j < y + SquareSize; j++)
			{
				if (cell.assignedByBoard == true)
				{
					break;
				}
				if (i != column || j != row)
				{
					cell.addConflict(value[j][i].getValue());
				}
			}
		}
}

void board::updateConflicts()
{
	int row = value.rows(); // 10 rows but 0th row is omitted
	int col = value.cols(); // 10 columns but 0th column is omitted
	for (int i = 1; i < row; i++)
	{
		for (int j = 1; j < col; j++)
		{

			setConflicts(i, j, value[i][j]); // sets the conflicts 

		}
		
	}
}


void board::printConflicts()
{
	for (int i = 1; i <= BoardSize; i++)
	{
		for (int j = 1; j <= BoardSize; j++)
		{
			cout << "Conflicts for [" << i << "][" << j << "] are: ";
			for (int x = 0; x < value[i][j].getConflicts().size(); x++)
			{
				cout << value[i][j].getConflicts()[x] << " ";
			}
			cout << endl;
		}
	}

}

void board::findCellWithLeastPossibilities(int &x, int &y)
{
	int minimum = 9; // minimum number of possibilities
	for (int i = 1; i <= BoardSize; i++)
	{
		for (int j = 1; j <= BoardSize; j++)
		{
			if (isBlank(i, j)) // if the cell is blank
			{
				int numberOfPossibilities = getCell(i, j).possibilities.size();
				if (numberOfPossibilities < minimum)
				{
					minimum = numberOfPossibilities; // updates minimum number of possibilities to be equal to number of possibilities
					x = i; // updates x 
					y = j; // updates y
				}
			}
		}
	}
}


void board::solveBoard()
{
	updateConflicts();
	if (isSolved()) // if the board is solved then return
	{
		return;
	}
	counter++; // counts number of recursions
	matrix<Cell> newBoard(value); // created new board that is a copy of the other board, this is for resetting purposes after a recursion if the board isn't solved

	// gets possibilities for each cell
	vector<int> allPossibilities = { 1,2,3,4,5,6,7,8,9 };
	vector<int> possibilities;
	//vector<int>::iterator it;
	for (int i = 1; i <= BoardSize; i++)
	{
		for (int j = 1; j <= BoardSize; j++)
		{
			
			vector<int> conf(value[i][j].getConflicts());
			if (conf.size() > 0)
			{
				sort(conf.begin(), conf.end()); // sort the conflicts in preparation for the set_difference
				//it = set_difference(allPossibilities.begin(), allPossibilities.end(), conf.begin(), conf.end(), possibilities.begin());
				set_difference(allPossibilities.begin(), allPossibilities.end(), conf.begin(), conf.end(), std::inserter(possibilities, possibilities.begin())); // takes all conflicts and removes them from the all possibilities and then adds the nonconflicts into a "possibilities" vector
				//possibilities.resize(it - possibilities.begin());
				value[i][j].possibilities = possibilities; // assigns the possibilities found to the cell's possibilities vector
				possibilities.clear();
			}
		}
	}
	
	int x(0), y(0);
	findCellWithLeastPossibilities(x, y);
	possibilities = value[x][y].possibilities; // gets the possibilities of the cell with the least possibilities
	for (int i = 0; i < possibilities.size(); i++)
	{
		value[x][y].setValue(possibilities[i]); // sets a possibility for that respective cell
		solveBoard(); // recursive call after the previous call was created
		if (!isSolved())
		{
			for (int row = 1; row <= BoardSize; row++)
			{
				for (int col = 1; col <= BoardSize; col++)
				{
					value[row][col] = newBoard[row][col]; // refreshes board if the placement of a possibility is incorrect
				}
			}
		}
		else
			return; // solved
	}
}

int main()
{
   ifstream fin;
   
   // Read the sample grid from the file.
   string fileName = "sudoku.txt";

   fin.open(fileName.c_str());
   if (!fin)
   {
      cerr << "Cannot open " << fileName << endl;
      exit(1);
   }

   try
   {
      
	  int sum(0);
	  int numberOfBoards(0);
	  int boardNumber(0);
	  while (fin && fin.peek() != 'Z')
	  {
		  board b1(SquareSize);
		  boardNumber++;
		  b1.initialize(fin);
		  b1.solveBoard(); // solves the board
		  b1.print();
		  
		  //b1.printConflicts();  //<- was for part A of the assignment
		  if (b1.isSolved())
		  {
			  cout << "The sudoku puzzle is solved" << endl;
		  }
		  else if (!b1.isSolved())
		  {
			  cout << "The sudoku puzzle is not solved" << endl;
		  }

		  cout << "Total Calls for puzzle "<< boardNumber <<": " << counter << endl;
		  sum += counter;
		  numberOfBoards++;
	  }
	  cout << "Average number of recursions: " << sum / numberOfBoards << endl;
	  system("pause");
	  
   }
   catch  (indexRangeError &ex)
   {
      cout << ex.what() << endl;
      exit(1);
   }
}

