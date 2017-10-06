#include <iostream>
#include <cstdlib>
#include <math.h>
#include <fstream>
#include <sstream>
#include <limits>

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

   //cout << m << endl << n << endl << k << endl;

   //Now create file pointers to .dat files

   for(int i=0; i<m; i++){
      
   }



   return 0;

}


/*int smallestRec(int m, int n, int k, int *offset){   our algorithm in pseudocode
   unsigned int smallest = -1; //just set our smallest to a huge number initially
   int x;                           //this will select which file to offset
   if(k==1){
      return smallest;
   }
   else{
      for(int i=0; i<m; i++){
         if fread(      ) < smallest;
            smallest = fread(    );
            x = i;                     //i think 'i' wil select the file
      }
      smallestRec(m, n, k-1, offset[x]);     //recursive call
   }

}*/

