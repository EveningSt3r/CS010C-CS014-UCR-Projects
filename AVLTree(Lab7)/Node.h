#pragma once

#include <string>

struct Node {
  std::string data;
  int count;
  Node* left;
  Node* right;
  Node(const std::string& data);
};
