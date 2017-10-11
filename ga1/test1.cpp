#include <iostream>
#include <cstdlib>
#include <math.h>
#include <fstream>
#include <sstream>
#include <limits>
#include <string.h>

using namespace std;


int smallestRec(unsigned int, int, int, int, int, ifstream *, int *);

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

   unsigned int smallest = -1;      //just set our smallest to a huge number initially
   int c=1;
   smallestRec(smallest, c, m, n, k, myTests, offset);

   return 0;

}

//simply testing the input for .dat files

int smallestRec(unsigned int smallest, int c, int m, int n, int k, ifstream *dataFiles, int *offset){
   int x;                           //this will select which file to offset
   char buffer[512];
   unsigned long temp;

   memset(buffer, '\0', 512);


   for(int x=0; x<n; x++){
      for(int i=0; i<m; i++){
         dataFiles[i].read(buffer, 4);       //store HEX input as cstring

         for(int j=0; j<4; j++){
            cout << (unsigned int)((unsigned char)buffer[j]) << endl;
         }

         //cout << atoi(buffer) << endl;
         offset[i] += 4;                    //allow file "i" to move one # over
         dataFiles[i].seekg(offset[i], dataFiles[i].beg);    //move to next 8 bytes (next number)

      }
      //smallestRec(smallest, c+1, m, n, k, dataFiles, offset);           //recursive call
   }
}

