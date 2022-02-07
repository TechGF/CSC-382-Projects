//Gary Feng
//CSC 382 Project 4
//Professor Louis Petingi
//main.cpp
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;
int B[250000];
int insertion(int[], int);
void Merge(int[], int, int, int);
void Mergesort(int[], int, int);
void Heapsort(int[], int);

template <class T>
class MinHeap {
public:
	MinHeap(int MSize) {
		MaxSize = MSize;
		heap = new T[MaxSize + 1];
		Size = 0;
	}
	~MinHeap() { delete[] heap; }
	MinHeap<T>& Insert(T& x);
	MinHeap<T>& Delete(T& x);
	int Size;
	
private:
	int MaxSize;
	T* heap;
};

template <class T>
MinHeap<T>& MinHeap<T>::Insert(T& x)
{
	if (Size == MaxSize)
		return *this;
	else
	{
		int i = ++Size;
		while (i != 1 && x < heap[i / 2])
		{
			heap[i] = heap[i / 2];
			i /= 2;
		}
		heap[i] = x;
		return *this;
	}
}

template <class T>
MinHeap<T>& MinHeap<T>::Delete(T& x)
{
	if (Size == 0)
		return *this;
	x = heap[1];  //root has the smallest key
	T y = heap[Size--]; //last element
	int vacant = 1;
	int child = 2; //make child = left child
	while (child <= Size)
	{
		if (child < Size && heap[child] > heap[child + 1]) ++child;
		//right child < left child
		if (y <= heap[child]) break;
		heap[vacant] = heap[child]; //move smaller child
		vacant = child; //new vacant
		child = child * 2; // new child of vacant

	}
	heap[vacant] = y;
	return *this;
}

int main() {
	srand(time(NULL));
	clock_t startTimeH, startTimeI, startTimeM;
	double timeHeap, timeInsertion, timeMerge;
	int n[] = { 1000, 10000, 25000, 50000, 150000, 250000 };
	string bestTime;
	int bound = 250000;

	cout << setw(80) << "Execution Times of Heap Sort, Insertion Sort, and Merge Sort" << endl;
	cout << "Input Length" << setw(23) << "Heap Sort (seconds)" << setw(29) << "Insertion Sort (seconds)" << setw(25) << "Merge Sort (seconds)" << setw(15) << "Best Time" << endl;

	for (int i = 0; i < size(n); i++) {
		int inputLength = n[i];
		int* array1 = new int[inputLength];
		int* array2 = new int[inputLength];
		int* array3 = new int[inputLength];

		for (int j = 0; j < n[i]; j++) {
			int num = rand() % bound;
			array1[j] = num;
			array2[j] = num;
			array3[j] = num;
		}

		// Heap Sort Time
		startTimeH = clock();
		Heapsort(array1, inputLength);
		timeHeap = ((clock() - startTimeH) / (double)CLOCKS_PER_SEC);

		// Insertion Sort Time
		startTimeI = clock();
		insertion(array2, inputLength);
		timeInsertion = ((clock() - startTimeI) / (double)CLOCKS_PER_SEC);

		// Merge Sort Time
		startTimeM = clock();
		Mergesort(array3, 0, inputLength - 1);
		timeMerge = ((clock() - startTimeM) / (double)CLOCKS_PER_SEC);

		if (timeHeap <= timeInsertion && timeHeap <= timeMerge) {
			bestTime = "Heap Sort";
		}
		else if (timeMerge < timeHeap && timeMerge <= timeInsertion) {
			bestTime = "Merge Sort";
		}
		else {
			bestTime = "Insertion Sort";
		}

		cout << setprecision(2) << fixed;
		cout << setw(7) << inputLength << setw(20) << (double)timeHeap << setw(25) << (double)timeInsertion << setw(29) << (double)timeMerge << setw(23) << bestTime << endl;
	}

	return 0;
}

// Insertion Sort
int insertion(int A[], int n) { //in reality the elements to be sorted are indexed from
	int i, j, temp;
	int steps = 0;
	A[0] = -32768; //smallest possible integer using 2 bytes integer representation
	for (i = 1; i <= n; i++) {
		j = i;
		while (A[j] < A[j - 1]) { // swap 
			temp = A[j];
			A[j] = A[j - 1];
			A[j - 1] = temp;
			j--;
			steps++;
		}
		steps++;
	}
	return steps;
}

// Merge
void Merge(int A[], int low, int mid, int high) // we assume that B is a global variable
{
	int l = low, i = low, h = mid + 1, k; // i is the index corresponding to array B
	while ((l <= mid) && (h <= high)) { // exactly one of the pointers will reach its limit
		if (A[l] <= A[h]) {
			B[i] = A[l];      // push A[l] to B
			l++;                //increment l
		}
		else {                 // we must A[h] to B
			B[i] = A[h];
			h++;
		}
		i++;
	}  //end while 
	if (l > mid) {  // we pushed the remaining elements starting at A[h]
		for (k = h; k <= high; k++) {
			B[i] = A[k];
			i++;
		} // end for
	}
	else
	{
		for (k = l; k <= mid; k++) // we push remaining elements starting at A[l]
			B[i] = A[k];
		i++;
	}
	// end else

   // Next we move B[low:high] to A[low:high] 
	for (k = low; k <= high; k++) {
		A[k] = B[k];
	} // end for
} // end algorithm

// Merge Sort
void Mergesort(int A[], int low, int high)
{
	if (low < high) { // if the sub-list has more than one element
		int mid = (low + high) / 2;
			Mergesort(A, low, mid); // we call Mergesort for the first half
		Mergesort(A, mid + 1, high); //we call Mergesort for the second half
			// at this point the two halves are sorted
			Merge(A, low, mid, high);
	}
} // end algorithm

// Heap Sort
void Heapsort(int A[], int num) {
	MinHeap<int> Heap(num);
	for (int i = 0; i < num; i++) {
		Heap.Insert(A[i]);
	}

	for (int j = 0; j < num; j++) {
		Heap.Delete(A[j]);
	}
}