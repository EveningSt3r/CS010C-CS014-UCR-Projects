#include "Node.h"

#include <string>

Node::Node(const std::string& data)
  :data(data), count(1), left(nullptr), right(nullptr) {
}
