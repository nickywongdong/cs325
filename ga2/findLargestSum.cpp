#include<stdlib.h>
#include<stdio.h>
#include <iostream>
#include <fstream>
#include <cmath>

int main () {
  return 0;
}

/*
Function "findLargestSum" is a recursive algorithm that finds the maximum sum
  from a given row and column of input array. To run for the first time, run with
  row = 0, col = 0, dynArr as an nxn array with values initialized to NULL.
  Returns: Largest sum starting on at location [row][col]
  Input parameters:
    integer "row":    the row of the starting square we're finding the largest sum for
    integer "col":    the col of the starting square we're finding the largest sum for
    int* inputArray:  pointer to nxn array with the input values in it. Does not change.
    int* dynArr:      dynamic array that contains maximum sum to each square. Must
                        be initialized to NULL in each square to start out
    int n:            size of the board (inputArray and dynArr must be this size)
*/

int findLargestSum(int row, int col, int** inputArray, int** dynArr, int n){
  if ((row >= n) || (col >= n)){
    return 0;
  }
  else if ( !isnan(dynArr[row][col]) ){
    return dynArr[row][col];
  }
  else {
    int x = findLargestSum(row+1, col, inputArray, dynArr, n);
    int y = findLargestSum(row, col+1, inputArray, dynArr, n);
    int max;
    if (x>=y){
      max = x + inputArray[row][col];
    } else {
      max = y + inputArray[row][col];
    }
    dynArr[row][col] = max;
    return max;
  }
}
