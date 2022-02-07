//Gary Feng
//CSC 382 Project 3
//Professor Louis Petingi
//main.cpp
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;
int modInsertion(int A[], int);

int main() {
	srand(time(NULL));
	int n[] = { 100, 500 };
	double calculateAverage, realAverage;
	int bound = 10000;
	int repeat = 100000;
	
	cout << "Input Size" << setw(30) << "Calculated Average" << setw(23) << "Real Average" << endl;

	for (int i = 0; i < size(n); i++) {
		int inputSize = n[i];
		int* array = new int[inputSize];
		long long int totalNumSteps = 0;

		//Generate 100,000 random sequences
		for (int j = 0; j < repeat; j++) {
			for (int k = 0; k < inputSize; k++) {
				array[k] = rand() % bound;
			}
			int insertionFunc = modInsertion(array, inputSize); //Calling modInsertion
			totalNumSteps += insertionFunc; //Update total number steps
		}
		calculateAverage = (pow(inputSize, 2) / 4) + (3 * inputSize / 4); //Calculate Average
		realAverage = static_cast<double>(totalNumSteps) / repeat; //Real Average

		cout << setprecision(2) << fixed;
		cout << setw(5) << inputSize << setw(30) << calculateAverage << setw(27) << realAverage << endl;
	}

	return 0;
}

int modInsertion(int A[], int n) { //in reality the elements to be sorted are indexed from
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