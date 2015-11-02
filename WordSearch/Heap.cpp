#include "Heap.h"

template<typename T>
heap<T>::heap()
{
}

template<typename T>
heap<T>::~heap()
{
}

template<class T>
int heap<T>::parent(int child) // takes the key of the child and returns the key of the parent
{
	return (child / 2);
}

template<typename T>
int heap<T>::left(int parent) // takes the key of the parent and returns the key of the left child
{
	return (2 * (parent + 1) - 1);
}

template<typename T>
int heap<T>::right(int parent) // takes the key of the parent and returns the key of the right child
{
	return (2 * (parent + 1));
}

template<typename T>
const T & heap<T>::getItem(int n)  // returns the item in the nth element of the heap
{
	return heapData[n];
}

template<typename T>
void heap<T>::initializeMaxHeap(vector<T> notHeap)
{
	for (int i = 0; i < notHeap.size(); i++)
	{
		heapData.push_back(notHeap[i]);
	}
	buildMaxHeap(); // makes sure the conditions of a max heap are correctly implemented
}

template<typename T>
void heap<T>::initializeMinHeap(vector<T> notHeap)
{
	for (int i = 0; i < notHeap.size(); i++)
	{
		heapData.push_back(notHeap[i]);
	}
	buildMinHeap(); // makes sure the conditions of a min heap are correctly implemented
}

template<typename T>
void heap<T>::maxHeapify(int index, int end)  // where index = root index and end = index of the last node 
{
	int l = left(index);
	int r = right(index);
	int largest;
	if (l <= end)
	{
		if (l == end)
		{
			largest = l;
		}
		else
		{
			if (heapData[l] > heapData[r]) // finds which child is larger
			{
				largest = l;
			}
			else
			{
				largest = r;
			}
			if (heapData[largest] > heapData[index])  // swaps the child with the root if the child is larger
			{
				swap(heapData[index], heapData[largest]);
				maxHeapify(largest, end);
			}
		}
	}
}

template<typename T>
void heap<T>::minHeapify(int index, int end)  // where index = root index and end = index of the last node 
{
	int l = left(index);
	int r = right(index);
	int smallest;
	if (l <= end)
	{
		if (l == end)
			smallest = l;
		else
		{
			if (heapData[l] < heapData[r]) // finds the smaller child
			{
				smallest = l;
			}
			else
			{
				smallest = r;
			}
			if (heapData[smallest] < heapData[index])
			{
				swap(heapData[index], heapData[smallest]);  // swaps if the child is smaller than the root
				minHeapify(smallest, end);
			}
		}
	}
}

template<typename T>
void heap<T>::buildMaxHeap()
{
	int end = heapData.size() - 1;
	for (int i = (heapData.size() + 1) / 2; i >= 0; i--)
	{
		maxHeapify(i,end);
	}
}

template<typename T>
void heap<T>::buildMinHeap()
{
	int end = heapData.size() - 1;
	for (int i = (heapData.size() + 1) / 2; i >= 0; i--)
	{
		minHeapify(i, end);
	}
}

template<typename T>
void heap<T>::heapSort(vector<T> &wordlist)
{
	buildMaxHeap();
	int heapSize = heapData.size(); // size of heap after the heap becomes equal to the size of the wordlist
	int length = heapSize - 1;
	
	for (length; length > 0; length--)
	{
		swap(heapData[0], heapData[length]);
		heapSize = heapSize - 1;
		maxHeapify(0, heapSize);
	}

	wordlist.clear(); // clear the previously passed word list
	for (int x = 0; x < heapData.size(); x++)
	{
		wordlist.push_back(heapData[x]); // pushes the sorted heap back into the original passed in wordlist
	}
}

