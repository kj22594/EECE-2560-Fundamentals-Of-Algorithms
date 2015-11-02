#include "HashTable.h"

template<typename T>
hashTable<T>::hashTable()
{
	hashtable.resize(hashTableSize);  // resizes the vector of vectors to allocate the correct amount of memory
}

template<typename T>
hashTable<T>::~hashTable()
{
}

template<typename T>
void hashTable<T>::addItem(T item)
{
	hash<T> hash_function; // hash function from c++  -> usable with the #include <functional>
	int x = hash_function(item) % hashTableSize; // finds the hash index
	hashtable[x].push_back(item); // pushes the item into the hash table
}


template<typename T>
void hashTable<T>::deleteItem()
{
	hash<T> hash_function; // hash function from c++  -> usable with the #include <functional>
	int x = hash_function(item) % hashTableSize; // finds the hash index
	for(int y = 0; y < hashtable[x].size(); y++)
	{
		if (hashtable[x][y] == item)  // if the item is found within the hash table it is deleted
		{
			hashtable[x].erase(hashtable[x].begin() + i);  // deletes the thing at the given hash if it is found
		}
	}
}

template<typename T>
bool hashTable<T>::inlist(T item)
{
	hash<T> hash_function; // hash function from c++  -> usable with the #include <functional>
	int x = hash_function(item) % hashTableSize; // finds the hash index
	for(int y = 0; y < hashtable[x].size(); y++)
	{
		if (hashtable[x][y] == item)
		{
			return true;  // if the item is found then return true
		}
	}
	return false;  // return false if the item is not found
}



