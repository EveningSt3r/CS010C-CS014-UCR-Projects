#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using std::string;
using std::vector;
using std::runtime_error;
using std::cout;
using std::endl;
using std::cin;

struct Node {
    string payload;
    Node* next;
};

Node* newNode(const string& payload) {
  Node *tempNode = new Node();  // Allocate memory for new Node

  tempNode->payload = payload;
  tempNode->next = nullptr;  // pass by reference payload parameter is allocated to newNode and next is updated
  return tempNode;
}

Node* loadGame(int n, const vector<string>& names) {
    Node* head = nullptr;
    Node* prev = nullptr;
    string name;

    for (int i = 0; i < n; ++i) {
        name = names.at(i);
// Special edge case when the list is initially empty
        if(head == nullptr) {
          head = newNode(name);
          prev = head;
        } else {
          prev->next = newNode(name);
          prev = prev->next;
        }
    }

    if (prev != nullptr) {
      prev->next = head;
    }
    return head;
}

// prints list from a starting node
void print(const Node* start) {
  const Node* curr = start;
  // We check if curr is nullptr to make sure the list is not empty before we
  // start extracting data to prevent undefined behavior.
  while (curr != nullptr) {
    cout << curr->payload << endl;
    curr = curr->next;
    if (curr == start) {
      break;  // exit circular list
    }
  }
}

// josephus w circular list, k = num skips
Node* runGame(Node* start, int k) {
  if (start == nullptr) return nullptr;

  Node* curr = start;
  Node* prev = curr;
  while (curr->next != curr) {  // exit condition, last person standing
    for (int i = 0; i < k; ++i) {  // find kth node
      prev = curr;
      curr = curr->next;
    }
    Node* next = curr->next;
    prev->next = next;
    delete curr;
    curr = next;
  }

  return curr;  // last person standing
}

/* Driver program to test above functions */
int main() {
  int n = 1, k = 1, max;  // n = num names; k = num skips (minus 1)
  string name;
  vector<string> names;

  // get inputs
  cin >> n >> k;
  if (!cin) throw runtime_error("error reading n and k from input");
  while (cin >> name && name != ".") {
    names.push_back(name);
  }  // EOF or . ends input

  // initialize and run game
  Node* startPerson = loadGame(n, names);
  Node* lastPerson = runGame(startPerson, k);

  if (lastPerson != nullptr) {
    cout << lastPerson->payload << " wins!" << endl;
  } else {
    cout << "error: null game" << endl;
  }

  return 0;
}
