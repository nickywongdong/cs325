#include <iostream>
#include <cstdlib>
#include <math.h>
#include <fstream>
#include <sstream>
#include <limits>
#include <string.h>

using namespace std;


//int smallestRec(unsigned int, int, int, int, int, ifstream *, int *);

int main(){

   int m, n, k;      //m: # of files, k: kth smallest num, n: # of elements in each file
   char temp;

   /*string path = "CS325_GA1_TESTS/"; 
   string testDirectory = "1/";           //change this based on which test case to try
   string input = "input.txt";*/          //doesnt work

   //retrieve input from bin files
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
   ifstream *myTests;
   myTests = new ifstream[m];
   for(int i=0; i<m; i++){
      myTests[i].open("CS325_GA1_TESTS/1/1.dat", ios::binary | ios::in);     //figure out how to change input file later
      if(!myTests[i].is_open()){
         cout << "FAIL: in opening " << i << "st file...";
      }
   }

   //create offset arrays for each m, and initialize vlues to 0;
   int *offset;
   offset = new int[m];
   for(int i=0; i<m; i++){
      offset[i] = 0;
   }
   //smallestRec(smallest, c, m, n, k, myTests, offset);

   return 0;

}


/*int smallestRec(int m, int n, int k, int *offset){   our algorithm in pseudocode
   //if n of all .dat files == 1
      //combine into 1 array, sort, and return kth element

   ///else
      find largest .dat length (can use offset array) assuming .dat is myFile[][]
      myFile[i][n/2] is the # to compare  (pretending .dat files are arrays)
      find position of all other arrays that come close to # (not over) can use binary search
      count the numbers within that index

      if # of numbers within that index > k
         remove all #'s to the right
         recursive call: kthRec()
      else
         remove all numbers to the left
         k = k-   #s removed
         recursive call kthRec()
   }
}*/

