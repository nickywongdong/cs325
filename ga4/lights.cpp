/*
 * CS325 Fall 2017
 * Group Assignment 4
 * Caitlin Berger
 * Peter Dorich
 * Nick Wong
 */



#include "./cnf2sat.hpp"



int ** initDynArr( int  );


using namespace std;


/*
 * Function: initDynArr
 * Input:    n: integer specifying dimensions of 2D array
 * Output:   2D dynamically allocated int array with values initialized to -1
 */
int ** initDynArr( int n ){
	//array of pointers corresponding to the number of lights (we add 1 because we want to start at index 1, not 0)
	int **myArray = new int*[n+1];
	for(int i=0; i<n; i++){
      myArray[i] = new int[2 + 1];	//each pointer (light), has an array of switches (2), we add 1 because we start at index 1, not 0
  }

  for(int i=0; i<n+1; i++){
  	for(int j=0; j<2+1; j++){
  		myArray[i][j] = -1;
  	}
  }

  return myArray;
}


int main(){

	int i, j;
	int **Q, *lightStatus, numSwitches, numLights, temp;

	//create output file:
	ofstream outputFile;
	outputFile.open("output.txt");

   //read in data from input.txt
	ifstream inputFile;
	inputFile.open("input.txt");

	if(inputFile.is_open()){
		inputFile >> numSwitches;
      inputFile.ignore(1, ','); //disregard comma
      inputFile >> numLights;

      //create array to hold light statuses:
      lightStatus = new int[numLights];

      //store the array that holds the initial light status:
      for(i=0; i<numLights; i++){
      	inuptFile >> lightStatus[i];
      	inputFile.ignore(1, ',');
      }

      //Create and initialize matrix
      Q = initDynArr(numLights);    //store as input

      //retrieve matrix information
      for(i=0; i<numLights+1; i++){
      	for(j=0; j<2+1; j++){
      		inputFile >> temp;

	 		Q[i][j] = 
	    	inputFile.ignore(1, ','); //disregard comma
		}
	}
}
else{
	cout << "Error in opening input file...\n";
}


   /*
   //testing adjacency matrix
   for(int i=0; i<V; i++){
   for(int j=0; j<V; j++){
   cout << Q[i][j] << "\t";
   }
   cout << endl;
   }
   */


return 0;
}