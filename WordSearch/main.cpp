#include "Grid.h"
#include "HashTable.cpp"



// Brandon Ngyuen helped talk me through this search for matches algorithm
void findWords(vector<char> characters, vector<string> &matches, wordlist dictionary)
{
	for (int c = 0; c < characters.size(); c++)
	{
		string tempF;  // temp for going forwards
		tempF = tempF + characters[c];
		int index = c;
		for (int a = 0; a < characters.size(); a++)
		{
			
			if (index == characters.size() - 1) // end of vector check condition
			{
				index = 0;
			}
			else
			{
				index++; // increments due to going forward
			}

			tempF = tempF + characters[index]; // adds the next character

			if (tempF.length() < 5)
			{
				continue;
			}
			
			string word = dictionary.binSearch(tempF); // does a binary search with the temp value to return a word in the list
			if (word == tempF)
			{
				matches.push_back(word);
				continue;
			}
			else if (word.find(tempF) == 0)
			{
				continue;
			}
			else
			{
				break;
			}

		}
	}
	
	for (int c = 0; c < characters.size(); c++)
	{
		string tempB;  // temp for going backwards
		tempB = tempB + characters[c];
		int index = c;
		for (int a = 0; a < characters.size(); a++)
		{	
			if (index == 0) // end of vector check condition
			{
				index = characters.size() - 1;
			}
			else
			{
				index--; // increments due to going forward
			}

			tempB = tempB + characters[index]; // adds the next character

			if (tempB.length() < 5)
			{
				continue;
			}

			string word = dictionary.binSearch(tempB); // does a binary search with the temp value to return a word in the list
			if (word == tempB)
			{
				matches.push_back(word);
				continue;
			}
			else
			{
				break;
			}

		}
	}
}

vector<string> findMatches(wordlist dictionary, grid wordsearchBoard)
{
	vector<string> matches; // what is being returned

	// goes through all columns of the matrix
	for (int x = 0; x < wordsearchBoard.gridMatrix.size(); x++)
	{
		vector<char> charactersCol;  // stores all characters in the column
		for (int y = 0; y < wordsearchBoard.gridMatrix[x].size(); y++)
		{
			charactersCol.push_back(wordsearchBoard.gridMatrix[y][x]); // pushes in the characters of each column to the vector
		}
		findWords(charactersCol, matches, dictionary);
	}

	// goes through all rows of the matrix
	for (int x = 0; x < wordsearchBoard.gridMatrix.size(); x++)
	{
		vector<char> charactersRow;  // stores all characters in the row
		for (int y = 0; y < wordsearchBoard.gridMatrix[x].size(); y++)
		{
			charactersRow.push_back(wordsearchBoard.gridMatrix[x][y]); // pushes in the characters of each row to the vector
		}
		findWords(charactersRow, matches, dictionary);
	}

	// goes through the up to down diagonals of the matrix
	for (int x = 0; x < wordsearchBoard.gridMatrix.size(); x++)
	{
		vector<char> charactersUpToDownDiagonal;
		for (int y = 0; y < wordsearchBoard.gridMatrix.size(); y++)
		{
			int wrapAround = (x + y) % wordsearchBoard.gridMatrix.size(); // takes into account the wrapping
			charactersUpToDownDiagonal.push_back(wordsearchBoard.gridMatrix[y][wrapAround]);
		}
		findWords(charactersUpToDownDiagonal, matches, dictionary);
	}

	// goes through the down to up diagonals of the matrix
	for (int x = 0; x < wordsearchBoard.gridMatrix.size(); x++)
	{
		vector<char> charactersDownToUpDiagonal;
		for (int y = 0; y < wordsearchBoard.gridMatrix.size(); y++)
		{
			int wrapAround;
			int diff = x - y;
			if (diff >= 0)
			{
				wrapAround = diff;
			}
			else
			{
				wrapAround = wordsearchBoard.gridMatrix.size() + x - y;
			}
			charactersDownToUpDiagonal.push_back(wordsearchBoard.gridMatrix[y][wrapAround]);
		}
		findWords(charactersDownToUpDiagonal, matches, dictionary);
	}

	return matches;
}


void hashFindWords(vector<char> characters, vector<string> &matches, hashTable<string> hashT)
{
	for (int c = 0; c < characters.size(); c++)
	{
		string tempF;  // temp for going forwards
		tempF = tempF + characters[c];
		int index = c;
		for (int a = 0; a < characters.size(); a++)
		{

			if (index == characters.size() - 1) // end of vector check condition
			{
				index = 0;
			}
			else
			{
				index++; // increments due to going forward
			}

			tempF = tempF + characters[index]; // adds the next character

			//if (tempF == "feature")
			//	cout << "";

			if (tempF.length() < 5)
			{
				continue;
			}

			if (tempF.length() > 22) // longest word
			{
				break;
			}

			if (hashT.inlist(tempF))  // if the string is in the hash table then push it into matches
			{
				matches.push_back(tempF);
				continue;
			}

		}
	}

	for (int c = 0; c < characters.size(); c++)
	{
		string tempB;  // temp for going backwards
		tempB = tempB + characters[c];
		int index = c;
		for (int a = 0; a < characters.size(); a++)
		{
			if (index == 0) // end of vector check condition
			{
				index = characters.size() - 1;
			}
			else
			{
				index--; // increments due to going forward
			}

			tempB = tempB + characters[index]; // adds the next character

			if (tempB.length() < 5)
			{
				continue;
			}
			if (tempB.length() > 22)
			{
				break;
			}

			if (hashT.inlist(tempB))
			{
				matches.push_back(tempB); // adds tempB if the string is in the hash table
				continue;
			}

		}
	}
}

vector<string> hashFindMatches(hashTable<string> hashT, grid wordsearchBoard)
{
	vector<string> matches; // what is being returned

	// goes through all columns of the matrix
	for (int x = 0; x < wordsearchBoard.gridMatrix.size(); x++)
	{
		vector<char> charactersCol;  // stores all characters in the column
		for (int y = 0; y < wordsearchBoard.gridMatrix[x].size(); y++)
		{
			charactersCol.push_back(wordsearchBoard.gridMatrix[y][x]); // pushes in the characters of each column to the vector
		}
		hashFindWords(charactersCol, matches, hashT);
	}

	// goes through all rows of the matrix
	for (int x = 0; x < wordsearchBoard.gridMatrix.size(); x++)
	{
		vector<char> charactersRow;  // stores all characters in the row
		for (int y = 0; y < wordsearchBoard.gridMatrix[x].size(); y++)
		{
			charactersRow.push_back(wordsearchBoard.gridMatrix[x][y]); // pushes in the characters of each row to the vector
		}
		hashFindWords(charactersRow, matches, hashT);
	}

	// goes through the up to down diagonals of the matrix
	for (int x = 0; x < wordsearchBoard.gridMatrix.size(); x++)
	{
		vector<char> charactersUpToDownDiagonal;
		for (int y = 0; y < wordsearchBoard.gridMatrix.size(); y++)
		{
			int wrapAround = (x + y) % wordsearchBoard.gridMatrix.size(); // takes into account the wrapping
			charactersUpToDownDiagonal.push_back(wordsearchBoard.gridMatrix[y][wrapAround]);
		}
		hashFindWords(charactersUpToDownDiagonal, matches, hashT);
	}

	// goes through the down to up diagonals of the matrix
	for (int x = 0; x < wordsearchBoard.gridMatrix.size(); x++)
	{
		vector<char> charactersDownToUpDiagonal;
		for (int y = 0; y < wordsearchBoard.gridMatrix.size(); y++)
		{
			int wrapAround;
			int diff = x - y;
			if (diff >= 0)
			{
				wrapAround = diff;
			}
			else
			{
				wrapAround = wordsearchBoard.gridMatrix.size() + x - y;
			}
			charactersDownToUpDiagonal.push_back(wordsearchBoard.gridMatrix[y][wrapAround]);
		}
		hashFindWords(charactersDownToUpDiagonal, matches, hashT);
	}

	return matches;
}

void search(int typeOfSort)
{
	try
	{
		string file;
		cout << "What is the name of the file you plan to use for the grid" << endl;
		cin >> file;
		grid game; // creates the grid based on the file input
		game.createGrid(file);
		wordlist dictionary;  // inputs the wordlist file
		string userInput;
		int searchType;
		cout << "What is the dictionary you'll be using" << endl;
		cin >> userInput;
		dictionary.readWordsFromList(userInput);
		if (typeOfSort != 4)  // if  typeOfSort is 0,1,2, or 3 then sort, otherwise it is just going to be doing hash table lookups
		{
			dictionary.sortList(typeOfSort); // 0 for insertionsort, 1 for quicksort, 2 for mergesort, 3 for heapsort
		}
		cout << "What type of search will you be using (Enter 0 for Binary Search, 1 for Hash Search)" << endl;
		cin >> searchType;
		if (searchType != 0 && searchType != 1)
		{
			throw("Invalid Character");
		}
		
		


		if (searchType == 1) // new logic for the hash table search
		{
			hashTable<string> hashT; // initializes hash table
			for (int x = 0; x < dictionary.words.size(); x++)
			{
				hashT.addItem(dictionary.words[x]); // adds sorted word list
			}

			// should return a vector of matches that are obtained based on lookups in the hash table
			vector<string> matches = hashFindMatches(hashT, game);
			cout << "The matches for this grid are:" << endl;
			for (int i = 0; i < matches.size(); i++)
			{
				cout << matches[i] << endl;
			}
			system("pause");
		}
		
		else   // sorts and finds matches if searchType comes back as binary search
		{
			vector<string> matches = findMatches(dictionary, game);  // gets all of the matches of the wordsearch and then prints them 

			cout << "The matches for this grid are:" << endl;
			for (int i = 0; i < matches.size(); i++)
			{
				cout << matches[i] << endl;
			}
			system("pause");
		}
	}
	catch (exception ex)
	{
		cout << ex.what();
		return;
	}
}
 


int main()
{
	try 
	{
		int typeOfSort;
		cout << "What type of sort would you like to use for this wordsearch? 0 for Insertionsort, 1 for Quicksort, 2 for Mergesort, 3 for Heapsort. If you are not sorting, please enter 4" << endl;
		cin >> typeOfSort;
		if (typeOfSort < 0 || typeOfSort >= 5)
		{
			throw("You entered a character in that is outside the parameters given");
		}

		search(typeOfSort);
			
	}
	catch (exception ex)
	{
		cout << ex.what();
		return -1;
	}
}