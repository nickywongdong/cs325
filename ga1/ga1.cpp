#include <iostream>
#include <cstdlib>
#include <math.h>
#include <fstream>
#include <sstream>
#include <limits>
#include <string.h>

using namespace std;

int kthSmallest(int , int , int , int *, int *, ifstream *);
int findLongest(ifstream *, int *, int *, int );
int countNums(ifstream *, long , int *, int *, int );
long getFromFile(ifstream &, int );
int binSearch(ifstream&, int, int, long);
void merge(int [], int , int , int );
void mergeSort(int [], int , int );

string directory = "1/";    //this tells which directory to test

int main(){

   int m, n, k;      //m: # of files, k: kth smallest num, n: # of elements in each file
   char temp;

   //open the input.txt file
   ifstream initialFile;
   string path = "CS325_GA1_TESTS/" + directory;
   initialFile.open(path + "input.txt");   //opens input.txt

   //retrieve .dat information
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
      myTests[i].open(path + to_string(i+1) + ".dat", ios::binary | ios::in);     //figure out how to change input file later
      if(!myTests[i].is_open()){
         cout << "FAIL: in opening " << i+1 << ".dat file...";
      }
   }

   //create offset arrays for each m, and initialize values to 0;
   int *beginning, *end;
   beginning = new int[m];
   end = new int[m];
   for(int i=0; i<m; i++){
      beginning[i] = 0;
      end[i] = n;
   }

   //begin recursion call
   int result = kthSmallest(m, n, k, beginning, end, myTests);


   //create and dump output result
   ofstream output;
   output.open("output.txt");
   output << result << endl;

   //clean up
   //close open files
   output.close();
   for(int i=0; i<m; i++){
      myTests[i].close();
   }

   //free memory nevermind not worth
   //delete [] beginning;
   //delete [] end;
   //delete myTests;

   return 0;

}


/*
    Function counts the numbers that come close to given mid index
    Inputs: m: # of .dat files
            n: length of each .dat files
            k: kth least to search 
            int *beginning: array of begining offsets
            int *end: array of end arrays
            ifstream *myFiles: array of file associations
    Outputs: total number of values that come close to mid value
*/

int kthSmallest(int m, int n, int k, int *beginning, int *end, ifstream *myFiles){
   int longest, midIndex, nums;
   long mid;

   int tmp_array[m]; //array that will hold all first values from m arrays
   if( n <= 1) //if the array size is only 1 or zero, combine into 1 array and sort. 
   {
      for( int i = 0; i < m; i ++)
      {
         tmp_array[i] = getFromFile(myFiles[i], 0);
      }
      
   //tmp_array now holds all first values 
   //merge sort:
     //int p = m/sizeof(tmp_array[0]);
     mergeSort(tmp_array, 0, m - 1);

  }
  else{
      //find longest "working" .dat length
      longest = findLongest(myFiles, beginning, end, m);    //store index of which .dat file into longest
      //retrieve the median index
      midIndex = (abs(beginning[longest] - end[longest]))/2;//store median index into midIndex

      mid = getFromFile(myFiles[longest], midIndex);          //store median

      //have function to count # of numbers that come close to mid
      nums = countNums(myFiles, midIndex, beginning, end, m);

      //testing
      cout << "out of countNums \n";

      if (nums >= k){
         //remove all #'s to the right
         for(int i=0; i<m; i++){
            end[i] = binSearch(myFiles[i], beginning[i], end[i], mid);   //set the index of the end for all .dat files for #'s close to mid
         }

         kthSmallest(m, n, k, beginning, end, myFiles);
      }
      else{
         //remove all numbers to the left including that index.
         for(int i=0; i<m; i++){
            beginning[i] = binSearch(myFiles[i], beginning[i], end[i], mid);   //set the index of the beginning for all .dat files for the #'s close to mid
         }

         kthSmallest(m, n, k-nums, beginning, end, myFiles);   //recursive call with k = k - num of nums
      }
   }
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
int countNums(ifstream *myFiles, long mid, int *beginning, int *end, int m){
   int total=0;
   int index;
   int n;
   //use binary search to find all elements up to mid value
   for(int i=0; i<m; i++){
      index = binSearch(myFiles[i], beginning[i], end[i], mid);
      n = abs(beginning[i] - index);
      total += n;
   }

   return total;
}
/*
    Function "getFromFile" finds the xth number in the .dat file
    Inputs:  fileName - ifstream file pointer
                    x - entry number to retrieve
    Outputs: number at xth entry
*/

long getFromFile(ifstream &myFile, int x){
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
int binSearch(ifstream &myFile, int start, int end, long x){
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
//Regular MergeSort algorithm
void merge(int arr[], int l, int m, int r)
{
   int i, j, k;
   int n1 = m - l + 1;
   int n2 = r - m;


   int L[n1], R[n2];

   for(i = 0; i <n1; i++)
    L[i] = arr[l + i];
 for(j = 0; j < n2; j++)
    R[j] = arr[m + 1 + j];
 i = 0;
 j = 0;
 k = l;

 while( i < n1 && j < n2)
 {
   if (L[i] <= R[j])
    {
      arr[k] = L[i];
      i++;
   }
   else
   {
      arr[k] = R[j];
      j++;
   }
   k++;
}
while( j < n2)
{
 arr[k] = R[j];
 j++;
 k++;
}
}
//l = left index and r = right index of sub-array
void mergeSort(int arr[], int l, int r)
{
	if(l < r)
	{
		int m = l+(r-l)/2;

     mergeSort(arr, l, m);
     mergeSort(arr, m+1, r);

     merge(arr, l, m, r);
  }

}

