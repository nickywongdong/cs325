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

   //Now create file pointers to .dat files
   ifstream *myTests;
   myTests = new ifstream[m];
   for(int i=0; i<m; i++){
      myTests[i].open("CS325_GA1_TESTS/1/1.dat", ios::binary | ios::in);     //figure out how to change input file later
      if(!myTests[i].is_open()){
         cout << "FAIL: in opening " << i << "st file...";
      }
   }

   //create offset arrays for each m, and initialize values to 0;
   int *beginning, *end;
   beginning = new int[m];
   end = new int[m];
   for(int i=0; i<m; i++){
      beginning[i] = 0;
      end[i] = 0;
   }
   //smallestRec(smallest, c, m, n, k, myTests, offset);

   return 0;

}

/*
   Function:   will find the working .dat file with the largest offset
   Input:      int *beginning - array that keeps index .dat should start
               int *end       - array that keepy index of where .dat should end
               int m          - number of .dat files 
   Output:     it will return the index of the longest "array" within the file pointers
*/

int findMax(int *beginning, int *end, int m){
   int max = abs(beginning[0] - end[0]);     //initial max
   int temp;
   int n = 0;
   for(int i=0; i<m; i++){
      temp = abs(beginning[i] - end[i]);
      if (temp > max){
         max = temp;
         n=i;
      }
   }
   return n;
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

/*int kthSmallest(int m, int n, int k, int *beginning, int *end, ifstream *myFiles){   our algorithm in pseudocode
   //if n of all .dat files == 1
      //combine into 1 array, sort, and return kth element

   ///else
   
      //find longest "working" .dat length
      longest = findLongest(myFiles, beginning, end, m);    //store index of which .dat file into longest
      midIndex = getMid(myFiles, beginning, end);   //retrieve the median index
      //or abs(beginning[longest] - end[longest]);


      mid = getFromFile(myFile[longest], midIndex);          //store median
   
      //have function to count # of numbers that come close to mid
      nums = countNums(myFiles, midIndex, beginning, end, m);

      if (nums >= k)"{
         //remove all #'s to the right
         //find position of all other arrays that come close to # (not over) can use binary search
         //removeLeft();

         kthSmallest(m, n, k, beginning, end, myFiles);
      }
      else{
         //remove all numbers to the left including that index.
         //find position of all other arrays that come close to # (over) can use binary search
         removeRight();
         kthSmallest(m, n, k-nums, beginning, end, myFiles);   //recursive call with k = k - num of nums
      }
   }
}*/

