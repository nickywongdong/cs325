/*
*	CS325 Fall 2017
*	Group Assignment 2
*	
*/

#include "mergeSort.cpp"
#include <iostream>


int main(){
	double **A = initDynArr(n);



	return 0;
}


/*
*	Function:	initDynArr
*	Input:		n: integer specifying dimensions of 2D array
*	Output:		2D dynamically allocated double array with values initialized to NaN
*/
double **initDynArr(int n){
	double **A;
	*A = new double[n];
	for(int i=0; i<n; i++){
		A[i] = new double[n];
	}

	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			A[i][j] = nan("");
		}
	}
	return A;
}

/*
*	Function:	findMax
*	Input:		A: pointer to dynamic 2D array
				n: integer specifying dimensions of 2D array
*	Output:		Maximum value in 2D array
*/
double findMax(double **A, int n){
	double *temp = new int[n];

	//first sort each row:
	for(int i=0; i<n; i++){
		mergeSort(A[i], 0, n - 1);
	}

	//now store last column into a temp array:
	for(int i=0; i<n; i++){
		temp[i] = A[i][n-1];
	}

	//now call sort on temp array:
	mergeSort(temp, 0, n-1);

	//Last value in temp should be maximum value in matrix
	return temp[n-1];
}