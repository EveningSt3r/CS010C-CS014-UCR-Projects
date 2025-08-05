#include "Node.h"
#include <string>

Node::Node()
  : numData(1),
    parent(nullptr),
    left(nullptr),
    middle(nullptr),
    right(nullptr) {
}

//------------------------------------------------------------------------

Node::Node(const string& word )
  : small(word),
    numData(1),
    parent(nullptr),
    left(nullptr),
    middle(nullptr),
    right(nullptr) {
}
