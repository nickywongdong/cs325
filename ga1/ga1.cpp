#include <iostream>
#include <cstdlib>
#include <math.h>
#include <fstream>
#include <sstream>

using namespace std;

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
   }
   else{
      cout << "Error in opening file...\n";
   }

   cout << m << endl << n << endl << k << endl;
   return 0;

}

/*int compLowest(  ){




}


int smallestRec(int c, int k, int n){
   if(c==k){
      return n;
   }
   else{
      for(int i=0; i<m-1; i++){
	 n=compLowest(m[i][0], m[i-1][0]);	//returns lowerst number of all arrays at that iteration
      }
      smallestRec(c+1, k, n);

   }

}
*/

