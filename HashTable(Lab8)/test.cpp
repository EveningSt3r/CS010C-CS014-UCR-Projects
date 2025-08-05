#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "HashTable.h"

bool test1() {
  cout << endl;
  cout << "Test 1 begins" << endl;
  HashTable table(100);
  cout << "Table constructed" << endl;
  if (table.contains("abc")) {
    cout << "contains returned true when it should have return false - hashtable empty" << endl;
    return false;
  }
  table.put("abc", 3);
  cout << "Puts abc" << endl;
  if (!table.contains("abc")) {
    cout << "contains returned false when it should have returned true - hashtable size of 1" << endl;
    return false;
  }
  if (table.contains("abcd")) {
    cout << "contains returned true when it should have returned false - hashtable size of 1" << endl;
    return false;
  }
  cout << "abc Passed" << endl;
  table.put("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", 2);
  cout << "Puts abc...ABC..." << endl;
  if (!table.contains("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ")) {
    cout << "contains returned false when it should have returned true - hashtable size of 2" << endl;
    return false;
  }
  if (table.contains("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXY")) {
    cout << "contains returned true when it should have returned false - hashtable size of 2" << endl;
    return false;
  }
  cout << "All Contains Tests Passed!" << endl;
  return true;
}

char genRandChar(char small, char large) {
  return small + rand() % (large - small + 1);
}

string genRandWord(int size) {
  string word;
  for (int i = 1; i <= size; ++i) {
    word += genRandChar('a', 'z');
    word += genRandChar('A', 'Z');
  }
  return word;
}

bool isEqual(double a, double b) {
  return fabs(a - b) < 0.001;
}

bool test2() {
  srand(time(0));
  cout << endl;
  cout << "Test 2 begins" << endl;
  HashTable table(5 + rand() % 6);
  double avg;
  string word;
  int score;
  int totalScore;
  int numWords;
  int numDuplicates;
  vector<string> words;
  vector<double> averages;

   
  cout << "Table constructed" << endl;
  table.put("aABb", 1);
  cout << "Puts aABb:1" << endl;
  avg = table.getAverage("aABb");
  if (!isEqual(avg, 1.0)) {
    cout << "getAverage returned " << avg << " when it should have returned 1.0" << endl;
    return false;
  }
  table.put("aABb", 3);
  cout << "Puts aABb:3" << endl;
  avg = table.getAverage("aABb");
  if (!isEqual(avg, 2.0)) {
    cout << "getAverage returned " << avg << " when it should have returned 2.0" << endl;
    return false;
  }
  word = genRandWord(4);
  score = 1 + rand() % 4;
  table.put(word, score);
  cout << "Puts " << word << ":" << score << endl;
  avg = table.getAverage(word);
  if (!isEqual(avg, score)) {
    cout << "getAverage returned " << avg << " when it should have returned " << score << endl;
    return false;
  }
   
  cout << "Begin Random Words Test" << endl;
  numWords = 20 + rand() % 41;
  for (int i = 1; i <= numWords; ++i) {
    numDuplicates = 1 + rand() % 5;
    totalScore = 0;
    word = genRandWord(1 + rand() % 15);
    for (int j = 1; j <= numDuplicates; ++j) {
      score = 1 + rand() % 4;
      totalScore += score;
      table.put(word, score);
      cout << "Puts " << word << ":" << score << endl;
    }
    words.push_back(word);
    averages.push_back(static_cast<double>(totalScore) / numDuplicates);
  }
   
  for (unsigned i = 0; i < words.size(); ++i) {
    avg = table.getAverage(words.at(i));
    if (!isEqual(avg, averages.at(i))) {
      cout << "getAverage returned " << avg << " when it should have returned " << averages.at(i) << endl;
      return false;
    }
  }
   
  cout << "All getAverage Tests Passed!" << endl;
  return true;
}


int main() {
  bool one = test1();
  bool two = test2();
  if (not one) {
    cout << endl;
    cout << "FIX TEST 1 PROBLEMS" << endl;
  }
  if (not two) {
    cout << endl;
    cout << "FIX TEST 2 PROBLEMS" << endl;
  }
  return 0;
}
