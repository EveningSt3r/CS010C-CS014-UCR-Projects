#include <exception>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::runtime_error;
using std::out_of_range;
using std::vector;
using std::cin;


vector<char> createVector() {  // Creates a vector of 26 characters (alphabet)
  int vecSize = rand() % 26;
  char c = 'a';
  vector<char> vals;
  for(int i = 0; i < vecSize; i++) {
      vals.push_back(c);
      c++;
  }
  return vals;
}

// Passes in an index of type int and a vector of type T (T could be
// string, double, int or whatever). The function returns the index
// of the min value starting from "index" to the end of the "vector".
template<typename T> unsigned min_index(const vector<T> &vals, unsigned index) {
  unsigned minIndex = index;
  for(unsigned i = index+1; i < vals.size(); ++i) {  // This is the "inner loop" of selection sort, hence loop starts at i + 1
    if(vals.at(i) < vals.at(minIndex)) {  // update minIndex if necessary throughout loop
      minIndex = i;
    }
  }
  return minIndex;

  return 0;
}

// SELECTION SORT: O(N^2)
// Array of size n (indices 0 through n-1)
// Pick smallest value from 0 to n-1 with min function
// move it to position 0, start over

template<typename T> void selection_sort(vector<T> &vals) {  // NOLINT(runtime/references)
  unsigned indexOfMin = 0;
  // indexOfMin is set to 0 to start but for every iteration of loop is reset
  // Acts as the "outer" loop of selection sort. Each call to min_index is the "inner loop"
  for(unsigned i = 0; i < vals.size(); ++i) {
    indexOfMin = min_index(vals, i);

    if(vals.at(indexOfMin) < vals.at(i)) {  // If the value at indexOfMin is less than current value, switch is performed
      T tempSwitch = vals.at(i);
      vals.at(i) = vals.at(indexOfMin);
      vals.at(indexOfMin) = tempSwitch;
    }
  }
}

template<typename T> T getElement(const vector<T>& vals, int index) {
  try {
    return vals.at(index);
  } catch (const out_of_range &excpt) {
    cout << "out of range exception occured" << endl;
  }
  return T();
}

int main() {
  // Seeding the random number generator so we get a different
  // run every time.
  srand(time(0));

  // Fill in a vector of some random size with some random
  // characters
  vector<char> vals = createVector();
  int numOfRuns = 5;  // Runs changed to 5 for testing purposes
  while(--numOfRuns >= 0) {
    cout << "Enter a number: " << endl;
    // Check input for validity
    int index;
    if (not (cin >> index)) {
      throw runtime_error("could not read the index");
    }

    try {  // try/catch block tests to see if input index is in range
      char curChar = getElement(vals, index);
      cout << "Element located at " << index << ": is " << curChar << endl;
    } catch (const out_of_range &excpt) {
      cout << "out of range exception occured. " << endl;
    }
  }

  // Test selection sort by printing (sorted) vals list
  cout << "Testing selection_sort function:" << endl;
  selection_sort(vals);
  for(unsigned i = 0; i < vals.size(); ++i) {
    cout << vals.at(i) << endl;
  }

  return 0;
}
