#pragma once
#include <string>

#include "Node.h"

class AVLTree{
  private:
    Node *root;
    void visualizeTree(const Node* subtree, int indent=0) const;
  public:
    AVLTree();
    ~AVLTree();
    AVLTree(const AVLTree&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;
    void destroy(Node*);

    void inOrder() const;
    void inOrder(Node*) const;

    // required
    void insert(Node*&, const std::string&);
    void insert(const std::string&);
    const int balanceFactor(Node*) const;
    void printBalanceFactors() const;


    // student-made
    void rotateRight(Node* &node);
    void rotateLeft(Node* &node);
    
    // pre-written visualization function (kept in for debugging purposes)
    void visualizeTree() const { visualizeTree(root); }
};
