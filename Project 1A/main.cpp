//Gary Feng
//CSC 382 Project 1A - Extra Credit
//Professor Louis Petingi
//main.cpp
#include <iostream>
#include <ctime>
#include <cmath>
#include <iomanip>
using namespace std;
int MODFibR(int);

int main() {
	clock_t startTimeMR;
	double timeMR;
	int fiboValue;

	cout << "\tFibonacci Time Analysis (Modified Recursive)" << endl;
	cout << "Integer" << setw(20) << "MODFibR (seconds)" << setw(20) << "MOD-Value" << endl;
	for (int i = 0; i <= 45; i += 5) {

		cout << setw(4) << i;

		startTimeMR = clock();
		fiboValue = MODFibR(i); //Calling Modified Recursive Function
		timeMR = (clock() - startTimeMR) / (double)CLOCKS_PER_SEC;
		cout << setw(18) << setprecision(3) << fixed << ((double)timeMR) << setw(25) << fiboValue << endl; //Display Modified Recursive Algorithm time and Fibonacci Value
	}

	return 0;
}

//Modified Recursive Algorithm
int MODFibR(int n) {
	int F0 = 0;
	int F1 = 1;
	int F2 = 1;
	if (n < 2)
		return n;
	for (int i = 2; i < n; i++) {
		F0 = F1;
		F1 = F2;
		F2 = F0 + F1;
	}
	return F2;
}
