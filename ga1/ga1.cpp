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
   Function:   will find the working .dat file with the longest working indexes
   Input:      int *beginning - array that keeps index .dat should start
               int *end       - array that keepy index of where .dat should end
               int m          - number of .dat files 
   Output:     it will return the index of the longest working .dat file within the file pointers
*/

int findLongest(ifstream *myFiles, int *beginning, int *end, int m){
   //"working" length can be calculated with abs(beginning[i] - end[i])
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
    Function counts the numbers that come close to given mid index
    Inputs: ifstream *myFiles - ifstream file pointers to all files
            int mid           - the value of the number we are searching for in other .dat files
            int *begginning   - array of offsets that tells us where .dat files should begin
            int *end          - array of offsets that tells us where .dat files should end
            int m             - number of total .dat files
    Outputs: total number of values that come close to mid value
*/
int countNums(ifstream *myFiles, long mid, int *begginning, int *end, int m){
   int total=0;
   int index;
   //use binary search to find all elements up to mid value
   for(int i=0; i<m; i++){
      index = binarySearch(myFile[i], beginning[i], end[i], mid);
   }

   return total;
}
/*
    Function "getFromFile" finds the xth number in the .dat file
    Inputs:  fileName - ifstream file pointer
                    x - entry number to retrieve
    Outputs: number at xth entry
*/

long getFromFile(ifstream myFile, int x){
  long result = 0;
  int bufLen = 4;
  unsigned int readIn;
  char buffer[bufLen];
  //ifstream myFile (fileName, ios::in | ios::binary);
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

/*
    Function "binSearch" finds the index of the element in the .dat file closest
    (less than or equal to) the number "x" to be searched for
    Inputs:  fileName - file path and file name of .dat file to be searched
                    x - number to be searched for
                start - starting index of the array to be searched
                  end - ending index of the array to be searched
    Outputs: index of the closeset (<=) element
*/
int binSearch(ifstream myFile, int start, int end, long x){
  cout << "start: " << start << "   end: " << end << endl;
  if (start == end){
    return start;
  }
  else {
    int a = (end - start)/2;
    long entry = getFromFile(myFile, start+a);
    cout << "a: " << a << "   start+a: " << start+a << "   entry: " << entry << endl;

    if (entry > x){
      // binary search the left side
      return binSearch(myFile, start, start+a, x);
    }
    else { // then entry < x
      // binary search the right side
      return binSearch(myFile, start+a+1, end, x);
    }
  }

}


int kthSmallest(int m, int n, int k, int *beginning, int *end, ifstream *myFiles){
   //if n of all .dat files == 1
      //combine into 1 array, sort, and return kth element

   ///else

      //find longest "working" .dat length
      longest = findLongest(myFiles, beginning, end, m);    //store index of which .dat file into longest
      //retrieve the median index
      midIndex = (abs(beginning[longest] - end[longest]))/2;//store median index into midIndex

      mid = getFromFile(myFile[longest], midIndex);          //store median
   
      //have function to count # of numbers that come close to mid
      nums = countNums(myFiles, midIndex, beginning, end, m);

      if (nums >= k){
         //remove all #'s to the right
         //find position of all other arrays that come close to # (not over)

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

