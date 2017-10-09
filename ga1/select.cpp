#include <iostream>
#include <cstdlib>
#include <math.h>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int FindSmallest(string, int, int*);

int main(){
  int m, n, k;      //m: # of files, k: kth smallest num, n: # of elements in each file
  //retrieve input from bin files
  char temp;
  ifstream initialFile;
  initialFile.open("CS325_GA1_TESTS/1/input.txt");   //opens input.txt

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

string filePath = "CS325_GA1_TESTS/1/";
int offset[m];
for (int i = 0; i < m; i++){
  offset[i] = 0;
}
int result = FindSmallest(filePath, m, offset);
  //cout << m << endl << n << endl << k << endl;

  return 0;
}

int FindSmallest(string filePath, int m, int *offset){
  unsigned int smallest = -1;
  for (int i = 1; i <= m; i++){
    //open file i
    string fileName = filePath + to_string(i) + ".dat";
    cout << fileName << endl;
    int bufLen = 20;
    char buffer[bufLen];
    ifstream myFile (fileName, ios::in | ios::binary);
    myFile.read(buffer, bufLen);
    for (int j = 0; j < bufLen; j++){
      cout << (unsigned int)buffer[j] << ", ";
    }
    cout << endl;
    //close file i
    myFile.close();
  }
  return 0;
}

//int toInt (char[2], )
