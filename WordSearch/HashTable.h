#include <vector>
#include <iostream>
#include <functional>
using namespace std;

template<typename T>
class hashTable
{
public:
	hashTable();
	~hashTable();

	// hash table functions
	void addItem(T item);
	void deleteItem();
	bool inlist(T item); // pass in an item to see if it is in the list, if yes return true


private:
	vector<vector<T>> hashtable;
	int hashTableSize = 90787; // size of hash table, really close prime number value to 90000

};