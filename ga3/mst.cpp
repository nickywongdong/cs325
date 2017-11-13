/*
* CS325 Fall 2017
* Group Assignment 3
* Caitlin Berger
* Peter Dorich
* Nick Wong
*/


/*
Implementation of Prim's algorithm sourced from:
http://www.geeksforgeeks.org/greedy-algorithms-set-5-prims-minimum-spanning-tree-mst-2/
with slight modifications
*/
// A C / C++ program for Prim's Minimum Spanning Tree (MST) algorithm. 
// The program is for adjacency matrix representation of the graph
 
#include <stdio.h>
#include <limits.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include "sort.cpp"

using namespace std;

int findLowestTwo(int *, int &, int &);
void iterMST(int ** , int, int **, int &, int &);
int minKey(int [], bool []);
int printMST(int [], int , int **);
int primMST(int **, int*);
int ** initDynArr( int  );

// Number of vertices in the graph
int V = 0;

// A utility function to print the constructed MST stored in parent[]
int printMST(int parent[], int n, int **graph)
{
  int sum = 0;
   for (int i = 1; i < V; i++){
      sum+=graph[i][parent[i]];
   }
   return sum;
}

//function that will take in an array, and find the lowest two elements
int findLowestTwo(int *result, int &result2, int &result3){
  quickSort(result, 0, V-2);
  result2 = result[0];
  result3 = result[1];
}


// A utility function to find the vertex with minimum key value, from
// the set of vertices not yet included in MST
int minKey(int key[], bool mstSet[])
{
   // Initialize min value
   int min = INT_MAX, min_index;
 
   for (int v = 0; v < V; v++)
     if (mstSet[v] == false && key[v] < min)
         min = key[v], min_index = v;
 
   return min_index;
}

/*
* Function: initDynArr
* Input:    n: integer specifying dimensions of 2D array
* Output:   2D dynamically allocated int array with values initialized to -1
*/
int ** initDynArr( int n ){
  int **myArray = new int*[n];
  for(int i=0; i<n; i++){
    myArray[i] = new int[n];
  }

  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      myArray[i][j] = -1;
    }
  }

  return myArray;
}


// Function to loop for each edge of MST, remove edge, and run MST algorithm again
void iterMST(int **parent, int n, int **graph, int &result2, int &result3)
{
  int weight;
  //array to store possible MST's
  int *result = new int[V-1];
   for (int i = 1; i < V; i++){
      

    //store as temp variable
    weight = graph[i][parent[0][i]];

    graph[i][parent[0][i]] = 0;  //"remove" this edge
    graph[parent[0][i]][i] = 0;

    result[i-1] = primMST(graph, parent[i]); //run algorithm without that edge, store solution into an array
    
    graph[i][parent[0][i]] = weight; //restore edge
    graph[parent[0][i]][i] = weight;
   }

   findLowestTwo(result, result2, result3);
}

 
// Function to construct and print MST for a graph represented using adjacency
// matrix representation
int primMST(int **graph, int *parent)
{ 
     memset(parent, V, 0); //set parent to all 0's
     int key[V];   // Key values used to pick minimum weight edge in cut
     bool mstSet[V];  // To represent set of vertices not yet included in MST
 
     // Initialize all keys as INFINITE
     for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;
 
     // Always include first 1st vertex in MST.
     key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
     parent[0] = -1; // First node is always root of MST 
 
     // The MST will have V vertices
     for (int count = 0; count < V-1; count++)
     {
        // Pick the minimum key vertex from the set of vertices
        // not yet included in MST
        int u = minKey(key, mstSet);
 
        // Add the picked vertex to the MST Set
        mstSet[u] = true;
 
        // Update key value and parent index of the adjacent vertices of
        // the picked vertex. Consider only those vertices which are not yet
        // included in MST
        for (int v = 0; v < V; v++)
 
           // graph[u][v] is non zero only for adjacent vertices of m
           // mstSet[v] is false for vertices not yet included in MST
           // Update the key only if graph[u][v] is smaller than key[v]
          if (graph[u][v] && mstSet[v] == false && graph[u][v] <  key[v])
             parent[v]  = u, key[v] = graph[u][v];
     }
     // print the constructed MST
     return printMST(parent, V, graph);
}

 
 
// driver program to test above function
int main()
{

  int **Q, result1, result2, result3;

  //create output file:
  ofstream outputFile;
  outputFile.open("output.txt");

  //read in data from input.txt
  ifstream inputFile;
  inputFile.open("input.txt");

  if(inputFile.is_open()){
    inputFile >> V;

    //Create and initialize matrix
    Q = initDynArr(V);    //store adjacency matrix

    //retrieve matrix information
    for(int i=0; i<V; i++){
      for(int j=0; j<V; j++){
        inputFile >> Q[i][j];   //store that index
        inputFile.ignore(1, ','); //disregard comma
          }
      }
  }
  else{
      cout << "Error in opening input file...\n";
    }

/*
//testing adjacency matrix
    for(int i=0; i<V; i++){
      for(int j=0; j<V; j++){
        cout << Q[i][j] << "\t";
      }
      cout << endl;
    }
*/

    int **parent = new int*[V];  // Array to store constructed MST's
    for(int i=0; i<V; i++){
      parent[i] = new int[V];
    }

    //run our algorithm
    result1 = primMST(Q, parent[0]);
    //find the next lowest 2
    iterMST(parent, V, Q, result2, result3);



    //store solution in output.txt
    if(outputFile.is_open()){
      outputFile << result1;
      outputFile << "\n";
      outputFile << result2;
      outputFile << "\n";
      outputFile << result3;
    }
    else{
      cout << "Error in opening output file...\n";
    }


  //clean up
  inputFile.close();
  outputFile.close();
  for(int i=0; i<V; i++){
    delete[] Q[i];
  }
  delete[] Q;
 
  return 0;
}