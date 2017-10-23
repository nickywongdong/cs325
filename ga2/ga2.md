## Functions and specifications:

* Arrays will be indexed from 0 to (n-1)
* Arrays are indexed [row][col]

### integer function "findLargestSum(integer row, integer col, int* inputArray, int* dynArr, int n)"

  * Returns: Largest sum starting on at location [row, col]

  * Input parameters:

    ```
    integer "row":    the row of the starting square we're finding the largest sum for

    integer "col":    the col of the starting square we're finding the largest sum for

    int* inputArray:  pointer to nxn array with the input values in it

    int* dynArr:      dynamic array that contains maximum sum to each square

    int n:            size of the board
    ```

  * Recursive function that calculates the maximum sum of the inputArray, starting at [row,col] storing the sum of each square in dynArr  


### int function "readInput(int* inputArray)" <-- removed this function

  * Returns: integer "n", the size of the array. Input array is populated with values from "input.txt" file

  * Input parameters:

    ```
    int* inputArray:  pointer to a 2D array that will be populated from the values in the "input.txt" file
    ```

  * This function reads the values from "input.txt" to the array pointed to by inputArray

### Integer pointer funciton "initializeDynArr(int n)"  <-- finished

 * Returns: a pointer to the dynamic array that is nxn, with NULL as the value in each entry

  * Input Parameters:

    ```
    int n:  the size of the dynamic array to create
    ```

  * This function creates an nxn dynamic array with each entry initialized to NULL, and returns a pointer to it.

### Integer funciton "findMax(int* dynArr, int n)"  <-- finished, still testing (works with just input matrix)

  * Returns: maximum integer in the dynamic array

  * Input Parameters:

      ```
      int n:   size of the board
      ```

  * This function finds the maximum value in the nxn array and returns it
