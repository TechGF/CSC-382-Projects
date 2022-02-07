//Gary Feng
//CSC 382 Project 1
//Professor Louis Petingi
//main.cpp
#include <iostream>
#include <ctime>
#include <iomanip>
#define max 60
using namespace std;
int FiboR(int);
long long int FiboNR(int);
long long int MODFibR(int);

int main() {
	clock_t startTimeR, startTimeMR, startTimeNR;
	double timeR, timeMR, timeNR;
	long long int fiboValue;
	long long int fiboValue2;
	
	cout << "\tFibonacci Time Analysis (Recursive vs. Modified Recursive vs. Non-Recursive)" << endl;
	//cout << "Integer" << setw(20) << "FiboR (seconds)" << setw(20) << "MODFibR (seconds)" << setw(20) << "FibNR (seconds)" << setw(20) << "Fibo-value" << endl;
	cout << "Integer" << setw(20) << "MODFibR (seconds)" << setw(20) << "MOD-Value" << setw(20) << "FibNR (seconds)" << setw(20) << "Fibo-value" << endl;
	for (int i = 0; i <= 50; i += 5) {

		cout << setw(4) << i;
		/*
		startTimeR = clock();
		FiboR(i); //Calling Recursive Function
		timeR = (clock() - startTimeR) / (double)CLOCKS_PER_SEC;
		cout << setw(18) << setprecision(3) << fixed << ((double)timeR); //Display Recursive Algorithm time
		*/
		startTimeMR = clock();
		fiboValue2 = MODFibR(i); //Calling Modified Recursive Function
		timeMR = (clock() - startTimeMR) / (double)CLOCKS_PER_SEC;
		cout << setw(18) << setprecision(3) << fixed << ((double)timeMR) << setw(25) << fiboValue2; //Display Modified Recursive Algorithm time

		startTimeNR = clock();
		fiboValue = FiboNR(i); //Calling Non-Recursive Function
		timeNR = (clock() - startTimeNR) / (double)CLOCKS_PER_SEC;
		cout << setw(20) << setprecision(3) << fixed << ((double)timeNR) << setw(25) << fiboValue << endl;; //Display Non-Recursive Algorithm time and Fibonacci Value

	}

	return 0;
}

//Recursive Algorithm
int FiboR(int n) {
	if (n == 0 || n == 1)
		return (n);
	else
		return (FiboR(n - 1) + FiboR(n - 2));
}

//Non-Recursive Algorithm
long long int FiboNR(int n) {
	long long int F[max];
	F[0] = 0; F[1] = 1;
	for (int i = 2; i <= n; i++) {
		F[i] = F[i - 1] + F[i - 2];
	}
	return (F[n]);
}

//Modified Recursive Algorithm
long long int MODFibR(int n) {
	long long int F[max];
	if (n == 0 || n == 1) {
		return(n);
	}
	else if (F[n - 1] > -1) {
		if (F[n - 2] > -1) {
			F[n] = F[n - 1] + F[n - 2];
			return F[n];
		}
	}
	else
		return (MODFibR(n - 1) + MODFibR(n - 2));

}
