#include "AVLTree.h"

#include <iostream>
#include <algorithm>
#include <string>

using std::max;
using std::cout;
using std::endl;
using std::string;

AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() {
  destroy(root);
}

// recursive traversal to delete every node, called in destructor for safe deletion
void AVLTree::destroy(Node* node) {
  if(node == nullptr) {
    return;
  }
  destroy(node->left);
  destroy(node->right);

  delete node;
}

// This is a helper function that traverses the tree to compute the height
static int computed_height(const Node* subtree) {
  if (subtree == nullptr) return 0;
  return max(computed_height(subtree->left), computed_height(subtree->right))+1;
}

void AVLTree::insert(const string&key) {
  // calls recursive helper to start at root
  insert(root, key);
}

void AVLTree::insert(Node* &node, const string& key) {
  // base case: empty spot, node inserted
  if(node == nullptr) {
    node = new Node(key);
    return;
  }
  // recursively traverse down the tree
  if(key < node->data) {
    insert(node->left, key);
  } else if (key > node->data) {
    insert(node->right, key);
  } else {
    ++node->count;
    return;
  }

  // recursively return until node is now root
  // root is most likely unbalanced. Proceed:
  // (recursive calls ignore this part until end)
  int balance = balanceFactor(node);

  // Case: left left
  if(balance > 1 && key < node->left->data) {
    // rotate node right
    rotateRight(node);
    return;
  }

  // Case: right right
  if(balance < -1 && key > node->right->data) {
    // rotate node left
    rotateLeft(node);
    return;
  }

  // Case: left right
  if(balance > 1 && key > node->left->data) {
    // rotate key (node's left) left
    rotateLeft(node->left);
    // rotate node right
    rotateRight(node);
    return;
  }

  // Case: right left
  if(balance < -1 && key < node->right->data) {
    // rotate key (node's right) right
    rotateRight(node->right);
    // rotate node left
    rotateLeft(node);
    return;
  }
}

// Tx variable represents T followed by (x) representing an integer
// where T1, T2, T3 are appropriate in the tree

void AVLTree::rotateRight(Node*& node) {
  // only update smallest unbalanced subtree
  // rotate right involves node's left pointer being shifted
  // node is set to where its formerly left pointer was

  Node* formerLeft = node->left;
  Node* Tx = formerLeft->right;
  formerLeft->right = node;
  node->left = Tx;

  node = formerLeft;
  return;
}
void AVLTree::rotateLeft(Node*& node) {
  // only update smallest unbalanced subtree
  // rotate left involves node's right pointer being shifted
  // node is set to where its formerly right pointer was

  Node* formerRight = node->right;
  Node* Tx = formerRight->left;
  formerRight->left = node;
  node->right = Tx;

  node = formerRight;
  return;
}

const int AVLTree::balanceFactor(Node* node) const {
  int leftBalance;
  int rightBalance;
  // balanceFactor is recursively called for every node
  // at every level of the tree, the initial subtree is
  // calculated
  leftBalance = computed_height(node->left);
  rightBalance = computed_height(node->right);
  return leftBalance - rightBalance;
}

void AVLTree::printBalanceFactors() const {
  if(root == nullptr) {
    return;
  }
  // call modified BSTree inOrder function to print balance factors
  inOrder(root);
  // visualizeTree(root, 1); used during debugging
}

void AVLTree::inOrder(Node* tree) const {
  if(tree == nullptr) {
    return;
  }
  // do left, print key, do right
  inOrder(tree->left);
  cout << (tree->data) << "(" << balanceFactor(tree) << "), ";
  inOrder(tree->right);
}


// We visualize a tree as text
void AVLTree::visualizeTree(const Node* subtree, int indent) const {
  // Indenting some spaces
  for(int i = 0; i < indent; ++i) {
    cout << ' ';
  }

  if (subtree == nullptr) {
    cout << "-empty-" << endl;
  } else {
    cout << subtree->data << ' ' << '(' << (computed_height(subtree->left)-computed_height(subtree->right)) << ')' << endl;
    visualizeTree(subtree->left, indent+4);
    visualizeTree(subtree->right, indent+4);
  }
}
