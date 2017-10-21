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

double **initDynArr(int );
double findMax(double **, int );


int main(){
	int n;
	char temp;

	//read in data from input.txt
	ifstream inputFile;
	inputFile.open("input.txt");

	if(inputFile.is_open()){
		inputFile >> n;
		//Create and initialize matrix
		double **A = initDynArr(n);		//matrix with numbers
		double **Q = initDynArr(n);		//matrix with path sums

		//retrieve matrix information
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
      			inputFile >> A[i][j];	//store that index
      			inputFile >> temp;		//disregard comma
      		}
    	}
	}
	else{
      cout << "Error in opening file...\n";
  	}

	return 0;
}

/*
*	Function:	readInput
*	Input:		n: dimensions of matrix that will be stored into variable n in main
*	Output:		2D dynamically allocated double array with values initialized to NaN
*/
/*void readInput(ifstream& inputFile, double **A, int n){

	char temp;
	//retrieve matrix information
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
      		inputFile >> A[i][j];	//store that index
      		inputFile >> temp;		//disregard comma
      	}
    }
}*/

/*
*	Function:	initDynArr
*	Input:		n: integer specifying dimensions of 2D array
*	Output:		2D dynamically allocated double array with values initialized to NaN
*/
double **initDynArr(int n){
	double **myArray;
	*myArray = new double[n];
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
double findMax(double **Q, int n){
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