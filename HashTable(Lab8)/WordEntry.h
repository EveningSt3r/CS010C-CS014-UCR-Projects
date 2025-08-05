#pragma once

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class WordEntry {
private:
  string word;
  int numAppearances;
  int totalScore;
public:
  WordEntry(const string &, int);
  void addNewAppearance(int);
  const string & getWord() const;
  double getAverage() const;
};
