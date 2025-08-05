#pragma once

#include "Node.h"

class BSTree {
  Node* root;

public:
  BSTree(): root(nullptr) {}
  ~BSTree() {
    // Safe to delete nullptr, so no check needed
    // The Node class recursively deletes its children
    delete root;
  }
  BSTree(const BSTree&) = delete;
  BSTree& operator=(const BSTree&) = delete;
  
  void insert(const string& key);
  bool search(const string& key) const;
  bool search(const Node*, const string&) const;
  string largest() const;
  string smallest() const;
  int height(const string& key) const;
  int height(const Node*) const;
  Node* searchNode(const string&, Node*) const;
  void remove(const string& key);
  Node* searchParent(const string&) const;

  void preOrder() const;
  void postOrder() const;
  void inOrder() const;

private:
  void remove(Node*, Node*, const string& key);
  void preOrder(Node* tree) const;
  void postOrder(Node* tree) const;
  void inOrder(Node* tree) const;

};
