#include <iostream>
#include <list>
#include "IntList.h"

using std::cout;
using std::endl;

int main() {
  IntList list;  // Test harness for IntList
  cout << "empty: " << list << endl;
  cout << "list.empty() = " << list.empty() << endl;
  // Check if empty() works
  list.push_front(3);
  cout << "push front 3: " << list << endl;
  list.push_back(1);
  cout << "push back 1: " << list << endl;
  list.push_back(5);
  cout << "push back 5: " << list << endl;
  list.push_front(2);
  cout << "push front 2: " << list << endl;
  // check push_front() and push_back()
  list.printReverse();
  cout << endl;
  // check printReverse()
  list.pop_back();
  cout << "pop back: " << list << endl;
  list.pop_front();
  cout << "pop front: " << list << endl;
  // check pop_front() and pop_back()

  list.printReverse();
  cout << endl;
  return 0;
}
