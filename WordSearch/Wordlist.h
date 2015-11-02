#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <cstring>
#include <ctime>
#include <time.h>
#include "Heap.cpp"
using namespace std;


class wordlist
{
public:
	wordlist();
	wordlist(string listInput);
	~wordlist();
	void readWordsFromList(string listInput);  // reads the words into a vector
	friend ostream& operator<< (ostream &ostr, wordlist list); // overloaded operator to print word list
	void sortList(int typeOfSort); // 0 for insertion, 1, for quick, 2 for merge
	string binSearch(string searchedWord);


	// all sorting declarations
	void mergeSort(vector<string>& unsortedList);
	void merge(vector<string>& unsortedList, vector<string> &vect1, vector<string> &vect2);
	void quickSort(vector<string>& unsortedList, int left, int right);
	int partition(vector<string>& unsortedList, int left, int right);
	void insertionSort();

	vector<string> words;

	int findLongestWord();
};
