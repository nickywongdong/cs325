/*
 * CS325 Fall 2017
 * Group Assignment 4
 * Caitlin Berger
 * Peter Dorich
 * Nick Wong
 */



#include "./cnf2sat.hpp"


using namespace std;


struct light {
  int* s;
} ;


void createSatInput(light*, int*, int, int*, int*);
light * initDynArr( int  );


/*
 * Function: initDynArr
 * Input:    n: integer specifying dimensions of array
 * Output:   dynamically allocated array of light structs with s values initialized to -1
 */
light * initDynArr( int n ){
  //array of pointers corresponding to the number of lights (we add 1 because we want to start at index 1, not 0)
  light *myArray = new light[n+1];
  for(int i=0; i<n+1; i++){
      myArray[i].s = new int[2 + 1];  //each pointer (light), has an array of switches (2), we add 1 because we start at index 1, not 0
  }

  //initialize values
  for(int i=0; i<n+1; i++){
    for(int j=0; j<2+1; j++){
      myArray[i].s[j] = -1;
    }
  }

  return myArray;
}


int main(){

  int i, j;
  int *lightStatus, numSwitches, numLights;
  light *Q;
  string buffer;

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
        inputFile >> lightStatus[i];
        inputFile.ignore(1, ',');
      }

      //Create and initialize matrix
      Q = initDynArr(numLights);    //store as input

      //retrieve matrix information
      //cool snippet inspired from:
      //https://stackoverflow.com/questions/3292107/whats-the-difference-between-istringstream-ostringstream-and-stringstream-w
      j=1;
      while (inputFile){
        if (!getline( inputFile, buffer )) break;
        //cout << buffer << endl;
        istringstream ss(buffer);
        while (ss >> i)
        {
          if(Q[i].s[0] == -1){
            Q[i].s[1] = j;
            Q[i].s[0] = -2;
          }
          //else we already filled in the first light
          else{
            Q[i].s[2] = j;
          }


          //ignore the next comma
           if(ss.peek() == ','){
            ss.ignore();
          }
        }
        //get next line (which is the switch number)
        j++;
      }


}
else{
  cout << "Error in opening input file...\n";
}


   
   /*//testing adjacency matrix
   for(i=1; i<2+1; i++){
    for(j=1; j<numLights+1; j++){
      cout << Q[j].s[i] << "\t";
    }
    cout << endl;
  }
  */
  //create array to store pairs
  int *a = new int[numLights * 2];
  int *b = new int[numLights * 2];
  //memset(a, 0, numLights);
  //memset(b, 0, numLights);


  //format input table
  createSatInput(Q, lightStatus, numLights, a, b);

  //testing output of a, and b
  /*for(i=0; i<numLights*2; i++){
    cout << a[i] << '\t';
  }
  cout << endl;
  for(i=0; i<numLights*2; i++){
    cout << b[i] << '\t';
  }
  cout << endl;
*/
  //format data as input for SAT2 black box
  vector<pair<int, int> > test; 
  for(i = 0; i < numLights*2; i++) {
        test.push_back(make_pair(a[i],b[i]));
  }

    //put data into SAT2 black box
    cout << satisfiable(test) << endl;
    //test.clear();

return 0;
}
/*
  void fuction: createSatInput
    Inputs:
      light* switches: (n+1)x3 array that has the numbers of the two switches connected to each switch
      int* lights: array length n that has the initial status of each light
      int n: number of lights
      int* x and y: arrays of length n*2. These will hold the resulting pairs to pass to cnf2sat
    Result:
      Arrays x and y contain the pairs to use as input to cnf2sat
*/
void createSatInput(light* switches, int* lights, int n, int* x, int* y){
  int a, b;
  for (int i = 0; i <n; i++){
    a = switches[i+1].s[1]; // get number of switches for light i
    b = switches[i+1].s[2];
    if (lights[i]){ // if light i is initially on (1 or TRUE)
      x[2*i] = -1*a; // add pair (-a|-b)
      y[2*i] = -1*b;
      x[2*i+1] = a; // add pair (a|b)
      y[2*i+1] = b;
    }
    else { //otherwise, i is initially off (0 or FALSE)
      x[2*i] = a; // add pair (a|-b)
      y[2*i] = -1*b;
      x[2*i+1] = -1*a; // add pair (-a|b)
      y[2*i+1] = b;
    }
  }
}
