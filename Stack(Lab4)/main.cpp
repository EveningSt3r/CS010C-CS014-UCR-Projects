// PROFPAT: I've cleaned up the code a bit.  The quality checkers won't ding you if you
// PROFPAT: use the original version, but this should pass the normal quality rubric

// We include headers for what we use.  First system headers, then project headers
// unless this is an implementation file
#include <iostream>
#include <string>
#include <stdexcept>
#include <stack>

#include "stack.h"
// Avoid namespace directive
using std::cin;
using std::cout;
using std::endl;
using std::out_of_range;
using std::overflow_error;
using std::runtime_error;
using std::string;
using std::underflow_error;

// tests constructor, push, pop, top and empty
void test1() {
    try {
      cout << "\nstack1 constructor called";
      stack<int> stack1;
      if(stack1.empty()) {
  cout << "\nstack1 is empty.";
      } else {
  cout << "\nstack1 is not empty";
      }
      cout << "\npush 10";
      stack1.push( 10 );
      cout << "\npush 20";
      stack1.push( 20 );
      cout << "\npush 30";
      stack1.push( 30 );
      cout << "\nstack1 top: ";
      cout << stack1.top();
      cout << "\npop";
      stack1.pop();
      cout << "\nstack1 top: ";
      cout << stack1.top();
      cout << "\npop";
      stack1.pop();
      cout << "\nstack1 top: ";
      cout << stack1.top();
      cout << "\npop";
      stack1.pop();
      if(stack1.empty()) {
  cout << "\nstack1 is empty.";
      } else {
  cout << "\nstack1 is not empty";
      }
      cout << endl;
    }
    catch(underflow_error & e) {
      cout << e.what() << endl;
    }
    catch(overflow_error & e) {
      cout << e.what() << endl;
    }
    catch(out_of_range & e) {
      cout << e.what() << endl;
    }
}

// tests top on empty stack
void test2() {
  try {
    cout << "\nstack2 constructor called";
    stack<int> stack2;
    cout << "\nstack2 top: ";
    cout << stack2.top();
    cout << endl;
    throw runtime_error("should not get here");
  }
  catch(underflow_error & e) {
    cout << e.what() << endl;
  }
  catch(overflow_error & e) {
    cout << e.what() << endl;
  }
  catch(out_of_range & e) {
    cout << e.what() << endl;
  }
}

// tests pop from an empty stack
void test3() {
  try {
    cout << "\nstack3 constructor called";
    stack<int> stack3;
    cout << "\npop from empty stack\n";
    stack3.pop();
    cout << endl;
    throw runtime_error("should not get here");
  }
  catch(underflow_error & e) {
    cout << e.what() << endl;
  }
  catch(overflow_error & e) {
    cout << e.what() << endl;
  }
  catch(out_of_range & e) {
    cout << e.what() << endl;
  }
}

// tests push to a full stack
void test4() {
  try {
    cout << "\nstack4 constructor called";
    stack<int> stack4;
    cout << "\npush 20 elements";
    for(int i = 1; i <=20; ++i) {
      stack4.push(i);
    }
    cout << "\nstack4 top: ";
    cout << stack4.top();
    cout << "\npush 21\n";
    stack4.push(21);
    cout << endl;
    throw runtime_error("should not get here");
  }
  catch(underflow_error & e) {
    cout << e.what() << endl;
  }
  catch(overflow_error & e) {
    cout << e.what() << endl;
  }
  catch(out_of_range & e) {
    cout << e.what() << endl;
  }
}

// tests stack of strings
void test5() {
  try {
    cout << "\nstack5 constructor called";
    stack<string> stack5;
    cout << "\npush A";
    stack5.push("A");
    cout << "\npush B";
    stack5.push("B");
    cout << "\npush C";
    stack5.push("C");
    cout << "\nstack5 top: ";
    cout << stack5.top();
    cout << "\npop";
    stack5.pop();
    cout << "\nstack5 top: ";
    cout << stack5.top();
    cout << "\npop";
    stack5.pop();
    cout << "\nstack5 top: ";
    cout << stack5.top();
    cout << "\npop";
    stack5.pop();
    if(stack5.empty()) {
      cout << "\nstack5 is empty.";
    } else {
      cout << "\nstack5 is not empty";
    }
    cout << "\nstack5 top: \n";
    stack5.top();
    cout << endl;
    throw runtime_error("should not get here");
  }
  catch(underflow_error & e) {
    cout << e.what() << endl;
  }
  catch(overflow_error & e) {
    cout << e.what() << endl;
  }
  catch(out_of_range & e) {
    cout << e.what() << endl;
  }
}

// tests stack of strings
void test6() {
  try {
    cout << "\nstack6 constructor called";
    stack<string> stack6;
    cout << "\npush A";
    stack6.push("A");
    cout << "\npush B";
    stack6.push("B");
    cout << "\npush C";
    stack6.push("C");
    cout << "\nstack5 top: ";
    cout << stack6.top();
    cout << "\npopping two items";
    stack6.pop_two();
    cout << "\nstack5 top: ";
    cout << stack6.top();
    cout << "\npopping 2 items\n";
    stack6.pop_two();
    cout << "\nstack5 top: ";
    cout << stack6.top();
    cout << "\npopping two items\n";
    stack6.pop_two();
    if(stack6.empty()) {
      cout << "\nstack6 is empty.";
    } else {
      cout << "\nstack6 is not empty";
    }
    cout << "\nstack6 top: \n";
    stack6.top();
    cout << endl;
    throw runtime_error("should not get here");
  }
  catch(underflow_error & e) {
    cout << e.what() << endl;
  }
  catch(overflow_error & e) {
    cout << e.what() << endl;
  }
  catch(out_of_range & e) {
    cout << e.what() << endl;
  }
}

int main() {
  int test;
  cout << "Enter a test number(1-6): ";
  if (not (cin >> test)) {
    throw runtime_error("input failed");
  }
  cout << endl;

  // We did't cover this in 10B, but a switch (often called a case
  // statement) is a super nice way to do this
  switch(test) {
  case 1: test1(); break;
  case 2: test2(); break;
  case 3: test3(); break;
  case 4: test4(); break;
  case 5: test5(); break;
  case 6: test6(); break;
  default:
    throw runtime_error("Invalid test request");
  }

  return 0;
}
