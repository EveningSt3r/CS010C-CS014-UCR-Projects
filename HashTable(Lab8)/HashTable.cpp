#include "HashTable.h"
#include "WordEntry.h"
#include <vector>
#include <list>
#include <string>

/* HashTable constructor
*  input s is the size of the array
*  set s to be size
*  initialize array of lists of WordEntry
*/
HashTable::HashTable (int s) {
  size = s;
  hashTable = new list<WordEntry>[size];
}

// use delete[] on table and set to nullptr to avoid memory leak
HashTable::~HashTable() {
  delete[] hashTable;
  hashTable = nullptr;
}


/* computeHash
*  return an integer based on the input string
*  used for index into the array in hash table
*  be sure to use the size of the array to 
*  ensure array index doesn't go out of bounds
*/
int HashTable::computeHash(const string &s) const {
  unsigned hash = 0;
  unsigned multiplier = 37;
  // choose prime number as multiplier
  // hash starts at 0 and gets larger every character in s
  // final string is returned as modulo size
  for(char c : s) {
    hash = hash * multiplier + static_cast<unsigned>(c);
  }
  return hash % size;
}


/* put
*  input: string word and int score to be inserted
*  First, look to see if word already exists in hash table
*   if so, addNewAppearence with the score to the WordEntry
*   if not, create a new Entry and push it on the list at the
*   appropriate array index
*/
void HashTable::put(const string &s, int score) {
  // collisions handled via list item
  auto& bucket = hashTable[computeHash(s)];
  if(contains(s)) {
    for(auto& entry : bucket) {
      if(entry.getWord() == s) {
        // collision: increment appearances
        entry.addNewAppearance(score);
      }
    }
  } else {
    WordEntry word = WordEntry(s, score);
    hashTable[computeHash(s)].push_front(word);
  }
}

/* getAverage
*  input: string word 
*  output: the result of a call to getAverage()
*          from the WordEntry
*  Must first find the WordEntry in the hash table
*  then return the average
*  If not found, return the value 2.0 (neutral result)
*/
double HashTable::getAverage(const string &s) const {
  if(contains(s)) {
    // non-const auto is used because of non-const function getAverage
    auto &bucket = hashTable[computeHash(s)];
    for(auto &entry : bucket) {
      if(entry.getWord() == s) {
        return entry.getAverage();
      }
    }
  }
  return 2.0;
}

/* contains
* input: string word
* output: true if word is in the hash table
*         false if word is not in the hash table
*/
bool HashTable::contains(const string &s) const {
  // bucket finds the correct entries for string s
  const auto& bucket = hashTable[computeHash(s)];
  for(const auto& entry : bucket) {
    // search bucket for string
    if(entry.getWord() == s) {
      return true;
    }
  }

  return false;
}

