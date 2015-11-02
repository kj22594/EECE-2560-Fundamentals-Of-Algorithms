#include <iostream>
#include <vector>
using namespace std;


template<typename T>
class heap
{
public:
	heap();
	~heap();

	const T & getItem(int n);

	void initializeMaxHeap(vector<T> notHeap);
	void maxHeapify(int index, int end);
	void buildMaxHeap();

	void initializeMinHeap(vector<T> notHeap);
	void minHeapify(int index, int end);
	void buildMinHeap();

	void heapSort(vector<T> &wordlist);

private:
	
	// object that stores the heap
	vector<T> heapData;

	// gets the key of the parent & their respective children
	int left(int parent);
	int right(int parent);
	int parent(int child);

};