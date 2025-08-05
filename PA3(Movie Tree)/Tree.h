#pragma once

#include "Node.h"

using std::string;

class Tree {
private:
  Node* root;

public:
  Tree();
  ~Tree();
  Tree(const Tree&) = delete;
  Tree& operator=(const Tree&) = delete;
  
  void insert( const string & );
  void preOrder() const;
  void inOrder() const;
  void postOrder() const;
  void split(Node*, const string&);
  void remove( const string & );
  void remove(const string&, Node*);
  Node* search( const string & );
  void destroy(Node*);

private:

  void insert(Node* curr, const string& word);
  bool isLeaf(Node*);
  void addData(Node* addHere, const string& word);
  void preOrder(const Node* curr) const;
  void inOrder(const Node* curr) const;
  void postOrder(const Node* curr) const;
  bool hasTwoChildSibling(Node* sibling) const;
  Node* search(Node* curr, const string& word);
};
