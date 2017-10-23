/*
*	CS325 Fall 2017
*	Group Assignment 2
*	
*/

#include "mergeSort.cpp"
#include <iostream>
#include <fstream>
#include <cmath>
//#include <cstdint>

using namespace std;

double **initDynArr( int );
double findMax(double **, int );
double findLargestSum(int , int , double** , double** , int )


int main(){
	int n;
	double **A, **Q;

	//read in data from input.txt
	ifstream inputFile;
	inputFile.open("testCases/1/input.txt");

	if(inputFile.is_open()){
		inputFile >> n;

		//Create and initialize matrix
		A = initDynArr(n);		//matrix with numbers
		Q = initDynArr(n);		//matrix with path sums

		//retrieve matrix information
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				inputFile >> A[i][j];		//store that index
				inputFile.ignore(1, ',');	//disregard comma
      		}
    	}
	}
	else{
      cout << "Error in opening file...\n";
  	}

  	/*//This will print out matrix, can be used for debugging
  	//test the matrix
  	for(int i=0; i<n; i++){
  		for(int j=0; j<n; j++){
  			cout << A[i][j] << '\t';
  		}
  		cout << endl; 
  	}

  	//testing findMax:
  	cout << findMax( A, n ) << endl;
  	*/

	return 0;
}

/*
Function "findLargestSum" is a recursive algorithm that finds the maximum sum
  from a given row and column of input array. To run for the first time, run with
  row = 0, col = 0, dynArr as an nxn array with values initialized to NULL.
  Returns: Largest sum starting on at location [row][col]
  Input parameters:
    integer "row":    the row of the starting square we're finding the largest sum for
    integer "col":    the col of the starting square we're finding the largest sum for
    int* inputArray:  pointer to nxn array with the input values in it. Does not change.
    int* dynArr:      dynamic array that contains maximum sum to each square. Must
                        be initialized to NULL in each square to start out
    int n:            size of the board (inputArray and dynArr must be this size)
*/

double findLargestSum(int row, int col, double** inputArray, double** dynArr, int n){
  if ((row >= n) || (col >= n)){
    return 0;
  }
  else if ( !isnan(dynArr[row][col]) ){
    return dynArr[row][col];
  }
  else {
    int x = findLargestSum(row+1, col, inputArray, dynArr, n);
    int y = findLargestSum(row, col+1, inputArray, dynArr, n);
    int max;
    if (x>=y){
      max = x + inputArray[row][col];
    } else {
      max = y + inputArray[row][col];
    }
    dynArr[row][col] = max;
    return max;
  }
}


/*
*	Function:	initDynArr
*	Input:		n: integer specifying dimensions of 2D array
*	Output:		2D dynamically allocated double array with values initialized to NaN
*/
double ** initDynArr( int n ){
	double **myArray = new double*[n];
	for(int i=0; i<n; i++){
		myArray[i] = new double[n];
	}

	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			myArray[i][j] = nan("");
		}
	}

	return myArray;
}

/*
*	Function:	findMax
*	Input:		A: pointer to dynamic 2D array
				n: integer specifying dimensions of 2D array
*	Output:		Maximum value in 2D array
*/
double findMax( double **Q, int n ){
	double *temp = new double[n];

	//first sort each row:
	for(int i=0; i<n; i++){
		mergeSort(Q[i], 0, n - 1);
	}

	//now store last column into a temp array:
	for(int i=0; i<n; i++){
		temp[i] = Q[i][n-1];
	}

	//now call sort on temp array:
	mergeSort(temp, 0, n-1);

	//Last value in temp should be maximum value in matrix
	return temp[n-1];
}