#include "Wordlist.h"

wordlist::wordlist()
{
}

wordlist::wordlist(string listInput) 
{
	readWordsFromList(listInput);
}
wordlist::~wordlist()
{
}


void wordlist::readWordsFromList(string listInput)
{
	ifstream file(listInput.c_str());
	for (string word; getline(file, word);)
	{
		words.push_back(word);
	}
	file.close();
}


void wordlist::sortList(int typeOfSort)
{
	clock_t start;
	clock_t end;
	string name;

	start = clock(); // starts the clock
	switch (typeOfSort)
	{
	case 0:
		// insertionsort then break
		insertionSort();
		name = "insertionSort";
		break;
	case 1:
		// quicksort then break
		quickSort(words,0,words.size()-1);
		name = "quickSort";
		break; 
	case 2:
		// mergesort then break
		mergeSort(words);
		name = "mergeSort";
		break;
	case 3:
		// heapsort
		heap<string> heapOfWords;
		heapOfWords.initializeMaxHeap(words);
		heapOfWords.heapSort(words);
		name = "heapSort";
		break;
	}
	end = clock();  // stop the clock
	clock_t timeDiff = (end - start);
	float timeDuration = ((float)timeDiff) / CLOCKS_PER_SEC; // finds how long each sort takes

	cout << "Time it took to run this program: " << timeDuration << " seconds" << endl;
}

// overloaded output operator to print word list
ostream& operator<< (ostream &ostr, wordlist list)
{
	string tempList;
	int count = list.words.size();
	for (int x = 0; x < count; x++)
	{
		tempList.append(list.words[x]); // adds word
		tempList.append("\n"); // makes a new line
	}
	return ostr << tempList;
}


void wordlist::insertionSort()
{
	string temp;
	int count = words.size();
	for (int j = 0; j < count; j++)
	{
		int i = j;
		while (i > 0 && words[i] < words[i-1])
		{
			temp = words[i];
			words[i]= words[i - 1];
			words[i - 1] = temp;
			i = i - 1;
		}
	}
}

// partition function used in quick sort
int wordlist::partition(vector<string>& unsortedList, int left, int right)
{
	string pivot = unsortedList[right];
	int x = left;
	for (int y = left; y < right; y++)
	{
		if (unsortedList[y] < pivot)
		{
			swap(unsortedList[x], unsortedList[y]);
			x++;
		}
	}
	swap(unsortedList[x], unsortedList[right]);
	return x;
}

void wordlist::quickSort(vector<string>& unsortedList, int left, int right)
{
	if (left < right)
	{
		int middle = partition(unsortedList, left, right); // established the middle pivot point
		quickSort(unsortedList, left, middle - 1);  // sorts first part
		quickSort(unsortedList, middle + 1, right); // sorts second part
	}
}

// merge function used in merge sort
void wordlist::merge(vector<string>& unsortedList, vector<string> &vect1, vector<string> &vect2)
{
	int i(0), j(0), k(0);
	unsortedList.clear(); // in preparation for merging vect1 & vect2 into this
	for (i, j, k; i < vect1.size() && j < vect2.size(); k++)
	{
		if (vect1[i] <= vect2[j])
		{
			unsortedList.push_back(vect1[i]);
			i++;
		}
		else if (vect1[i] > vect2[j])
		{
			unsortedList.push_back(vect2[j]);
			j++;
		}
		k++;
	}

	while (i < vect1.size())
	{
		unsortedList.push_back(vect1[i]);
		i++;
	}
	while (j < vect2.size())
	{
		unsortedList.push_back(vect2[j]);
		j++;
	}
}

void wordlist::mergeSort(vector<string>& unsortedList)
{
	if (1 < unsortedList.size())
	{
		vector<string> vect1(unsortedList.begin(), unsortedList.begin() + unsortedList.size() / 2);  // sorts and merges first half of list
		mergeSort(vect1);
		vector<string> vect2(unsortedList.begin() + unsortedList.size() / 2, unsortedList.end());   // sorts and merges second half of list
		mergeSort(vect2);
		merge(unsortedList, vect1, vect2);
	}
}

// binary search over a certain word
string wordlist::binSearch(string searchedWord)
{
	vector<string> sortedList = words;
	int start = 0;
	int end = sortedList.size();
	int middle = start + (end - start) / 2; // avoids overflow 
	

	while ((end - start) > 1) {
		middle = start + (end - start) / 2;
		if (searchedWord.compare(sortedList[middle]) < 0) { // if the word is less than the middle then the middle becomes the new end of the list
			end = middle;
		}
		else if (searchedWord.compare(sortedList[middle]) > 0) { // if the word is greated than the middle then the middle becomes the start of the list
			start = middle;
		}
		else if (sortedList[middle] == searchedWord) { // if the word and middle are equal then return that middle word
			return searchedWord;
		}
	}
	if (sortedList[start] == searchedWord) {  // if the beginning of the list is the word then return the word
		return searchedWord;
	}
	else 
	{
		if (sortedList[middle].length() < 5) {
			return sortedList[start];
		}
		size_t found = sortedList[middle].find(searchedWord);
		if (found != string::npos) { // word found is containted in another word so return that word 
			return sortedList[middle];
		}
		return sortedList[start]; // otherwise return the first thing in the list
	}
}


int wordlist::findLongestWord()
{
	int longest = words[0].size();
	for (int i = 0; i < words.size(); i++)
	{
		if (longest < words[i].size())
		{
			longest = words[i].size();
		}
	}
	return longest;
}


