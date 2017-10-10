#include <iostream>
#include <cstdlib>
#include <math.h>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
long getFromFile(string, int);
int main () {
  int m, n, k;      //m: # of files, k: kth smallest num, n: # of elements in each file
  //retrieve input from bin files
  char temp;
  ifstream initialFile;
  initialFile.open("CS325_GA1_TESTS/2/input.txt");   //opens input.txt

  if(initialFile.is_open()){
     initialFile >> m;
     initialFile >> temp;
     initialFile >> n;
     initialFile >> temp;
     initialFile >> k;
     initialFile.close();
     cout << "m: " << m << endl;
     cout << "n: " << n << endl;
     cout << "k: " << k << endl;

  }
  else{
     cout << "Error in opening file...\n";
  }
  for (int i = 0; i < n; i++){
    long result = getFromFile("CS325_GA1_TESTS/2/2.dat", i);
    cout << "result: " << result << endl;
  }

  return 0;
}

/*
    Function "getFromFile" finds the xth number in the .dat file
    Inputs:  fileName - file path and file name of input file
                    x - entry number to retrieve
    Outputs: number at xth entry
*/

long getFromFile(string fileName, int x){
  long result = 0;
  int bufLen = 4;
  unsigned int readIn;
  char buffer[bufLen];
  ifstream myFile (fileName, ios::in | ios::binary);
  myFile.seekg(4*x, ios::beg);
  myFile.read(buffer, bufLen);
  for (int j = 0; j < bufLen; j++){
    readIn = (unsigned int)((unsigned char)buffer[j]);
    //cout << readIn << ", ";
    result += readIn * pow(16, 3-j);
  }
  //cout << endl;
  myFile.close();
  return result;
}
