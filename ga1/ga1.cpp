#include <iostream>
#include <cstdlib>
#include <math.h>


int main(){

   //retrieve input from bin files

   int k = 5, c = 1, n;
   static int m[2][3] = { { 1, 6, 7 }, { 2, 2, 2 } };

   cout << smallestRec(c, k, n) << endl;


   return 0;

}

int compLowest(  ){




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


