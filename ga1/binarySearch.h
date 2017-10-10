/*
    Function "binSearch" finds the index of the element in the .dat file closest
    (less than or equal to) the number "x" to be searched for
    Inputs:  fileName - file path and file name of .dat file to be searched
                    x - number to be searched for
                start - starting index of the array to be searched
                  end - ending index of the array to be searched
    Outputs: index of the closeset (<=) element
*/
int binSearch(string fileName, int start, int end, long x){
  cout << "start: " << start << "   end: " << end << endl;
  if (start == end){
    return start;
  }
  else {
    int a = (end - start)/2;
    long entry = getFromFile(fileName, start+a);
    cout << "a: " << a << "   start+a: " << start+a << "   entry: " << entry << endl;

    if (entry > x){
      // binary search the left side
      return binSearch(fileName, start, start+a, x);
    }
    else { // then entry < x
      // binary search the right side
      return binSearch(fileName, start+a+1, end, x);
    }
  }

}
