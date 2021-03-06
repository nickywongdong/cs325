/*
*	CS325 Fall 2017
*	Group Assignment 2
*	Caitlin Berger
*	Peter Dorich
*	Nick Wong
*/

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

double **initDynArr( int );
double findLargestSum(int , int , double** , double** , int, double &);


int main(){
	int n;
	double **A, **Q, result;

	//create output file:
	ofstream outputFile;
	outputFile.open("output.txt");

	//read in data from input.txt
	ifstream inputFile;
	inputFile.open("input.txt");

	if(inputFile.is_open()){
		inputFile >> n;

		//Create and initialize matrix
		A = initDynArr(n);		//matrix with input numbers
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
      cout << "Error in opening input file...\n";
  	}

  	//Recursive solution of populating Q with largest sums
  	findLargestSum(0, 0, A, Q, n, result);

  	//store solution in output.txt
  	if(outputFile.is_open()){
  		outputFile << result;
  	}
  	else{
  		cout << "Error in opening output file...\n";
  	}


  	//clean up
	inputFile.close();
	outputFile.close();
	for(int i=0; i<n; i++){
		delete[] A[i];
		delete[] Q[i];
	}
	delete[] Q;
	delete[] A;

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

double findLargestSum(int row, int col, double** inputArray, double** dynArr, int n, double &result){
  if ((row >= n) || (col >= n)){
    return 0;
  }
  else if ( !isnan(dynArr[row][col]) ){
    return dynArr[row][col];
  }
  else {
    double x = findLargestSum(row+1, col, inputArray, dynArr, n, result);
    double y = findLargestSum(row, col+1, inputArray, dynArr, n, result);
    double max;
    if (x>=y){
      max = x + inputArray[row][col];
    } else {
      max = y + inputArray[row][col];
    }
    if(max > result){
    	result = max;
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