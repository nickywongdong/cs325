#include <iostream>
#include <cstdlib>
#include <math.h>
#include <fstream>


int main() {
    int m, n, k;
    //read in variables from file
    ifstream myfile;
    myfile.open("/CS325_GA1_TESTS/input.txt");



  return 0;
}

int FindKth(int offsets[], int m, int k){
  if (k==1){ //base case: k = 1
    int x = FindSmallest(offsets, m);
    int smallest; //= [get x.dat at offset[x] ]
    return smallest;
  } else {
    int x = FindSmallest(offsets, m);
    offsets[x] += 1;
    return FindKth(offsets, m, k);
  }
}

int FindSmallest(int offsets[], int m, int k){
  int min; // = open 1.dat and read entry at offset of offsets[1]
  for (int i = 1; i <= m; i++){
    int comp; // = read in i.dat at offset of offsets[i]
    if (comp < min){
        min = comp;
    }
  }
  return min;
}
