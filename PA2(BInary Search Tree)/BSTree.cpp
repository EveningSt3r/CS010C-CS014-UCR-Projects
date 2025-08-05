#include "BSTree.h"

#include <iostream>
#include <string>
#include <algorithm>

using std::string;
using std::cout;
using std::endl;


void BSTree::insert(const string& key) {
  if(root == nullptr) {
    root = new Node(key);  // If empty root is the new Node
  } else {
    Node *currentNode = root;
    // traverse either left or right until leaf is reached
    // insert at end
    while(currentNode != nullptr) {
      if(key < currentNode->key) {
        if(currentNode->left == nullptr) {
          currentNode->left = new Node(key);
          return;
          // while current is nullptr current compares its key to the parameter
        } else {
          currentNode = currentNode->left;
        }
      } else if (key > currentNode->key) {
          if(currentNode->right == nullptr) {
            currentNode->right = new Node(key);
            return;
          } else {
            currentNode = currentNode->right;
          }
      } else if (key == currentNode->key) {
        // If duplicate is found, increment count and return
        currentNode->count += 1;
        return;
      }
    }
  }
}
bool BSTree::search(const string &key) const {
  // base function calls recursive helper and returns when root is nullptr
  if(root == nullptr) {
    return false;
  } else {
    return search(root, key);
  }
}

bool BSTree::search(const Node* currentNode, const string &key) const {
  // recursive search function
  // return false is root (currentNode at start) is null
  if(currentNode == nullptr) {
    return false;
  }
  // return true if found
  if(currentNode->key == key) {
    return true;
  // otherwise recursively call helper depending on key comparison(s)
  } else if (key > currentNode->key) {
    return search(currentNode->right, key);
  } else if (key < currentNode->key) {
    return search(currentNode->left, key);
  }
  return false;
}

string BSTree::largest() const {
  if(root == nullptr) {
    return "";
  }
  // return empty if no key (empty tree)
  Node *currentNode = root;
  while(currentNode->right != nullptr) {
    currentNode = currentNode->right;
  }
  return currentNode->key;
  // traverse as far right as possible
}

string BSTree::smallest() const {
  if(root == nullptr) {
    return "";
  }
  // return empty if no key (empty tree)
  Node *currentNode = root;
  while(currentNode->left != nullptr) {
    currentNode = currentNode->left;
  }
  return currentNode->key;
  // traverse as far left as possible
}

// The height (length of longest path to the bottom) of an empty tree is -1
// Otherwise, you pick the larger of the left height and the right height
// and add one to that

int BSTree::height(const string& key) const {
  // base case calls searchNode for target's location
  if(search(key)) {
    const Node* target = searchNode(key, root);
    return height(target);
  } else {
    return -1;
  }
}

int BSTree::height(const Node* node) const {
  if(node == nullptr) {
    return -1;
  }
  // 1 + max is returned all the way up the tree
  // with a comparison at each level
  // -1 is returned for false, so 1 is added
  // so leaf nodes have height 0 on max(-1, -1)
  int leftHeight = height(node->left);
  int rightHeight = height(node->right);
  return 1 + std::max(leftHeight, rightHeight);
}

Node* BSTree::searchNode(const string &key, Node* node) const {
  if(node == nullptr) {
    return nullptr;
  }
  // return null if empty, return node if found
  if(node->key == key) {
    return node;
  }
  // recursively call itself while traversing comparing keys
  if(key < node->key) {
    return searchNode(key, node->left);
  } else {
    return searchNode(key, node->right);
  }
}

void BSTree::preOrder() const {
  if(root == nullptr) {
    return;
  }
  preOrder(root);
}

void BSTree::preOrder(Node* tree) const {
  if(tree == nullptr) {
    return;
  }
  // print key, do left, do right
  cout << (tree->key) << "(" << tree->count << "), ";
  preOrder(tree->left);
  preOrder(tree->right);
}

void BSTree::postOrder() const {
  if(root == nullptr) {
    return;
  }
  postOrder(root);
}

void BSTree::postOrder(Node* tree) const {
  if(tree == nullptr) {
    return;
  }
  // do left, do right, print key
  postOrder(tree->left);
  postOrder(tree->right);
  cout << (tree->key) << "(" << tree->count << "), ";
}

void BSTree::inOrder() const {
  if(root == nullptr) {
    return;
  }
  inOrder(root);
}

void BSTree::inOrder(Node* tree) const {
  if(tree == nullptr) {
    return;
  }
  // do left, print key, do right
  inOrder(tree->left);
  cout << (tree->key) << "(" << tree->count << "), ";
  inOrder(tree->right);
}
Node* BSTree::searchParent(const string& key) const {
  Node* currentNode = root;
  if(root == nullptr || root->key == key) {
    return nullptr;
  }
  // edge cases, empty tree or key is root
  while(currentNode != nullptr) {
    if ((currentNode->left != nullptr && currentNode->left->key == key) ||
    (currentNode->right != nullptr && currentNode->right->key == key)) {
      return currentNode;
    }
    // if either: left is NOT empty and left is key
    // or: right is NOT empty and right is key
    // return current (parent of the next)

    // otherwise: traverse by key comparison
    if(key > currentNode->key) {
      currentNode = currentNode->right;
    } else {
      currentNode = currentNode->left;
    }
  }
  return nullptr;
}

void BSTree::remove(const string& key) {  // Base function
  if (root == nullptr) {
    return;  // nothing to remove
  }
  Node* keyNode = searchNode(key, root);  // return Node with matching key
  if (keyNode == nullptr) {
    return;  // nothing to remove
  }
  remove(searchParent(key), keyNode, key);
  // call recursive helper with parent, found Node, and reference key
}

void BSTree::remove(Node* parent, Node* tree, const string& key) {
  // Find the parent and the curr node that holds that key
  // Edge case: The key is not found (do nothing)
  if(tree == nullptr) {
    return;
  }
  // Edge case.  The key count is greater than 1.  Just decrement the count
  if(tree->count > 1) {
    tree->count -= 1;
    return;
  }
  // Edge case: leaf (no children).  Just remove from parent
  if (tree->left == nullptr && tree->right == nullptr) {
    if (parent == nullptr) {  // Removing the root node (which is the only node)
      delete root;
      root = nullptr;
    } else {  // Removing an internal leaf node
        if (parent->left == tree) {
          parent->left = nullptr;  // Update parent pointer first
        } else {  // parent->right == tree
          parent->right = nullptr;
        }
        delete tree;
    }
    return;
}
    // Typical case.  Find the target
    // It is either the largest key in the left tree (if one exists)
    // or the smallest key in the right tree (since not a leaf one will exist)
    // Copy the target information into the node we found, set the target count to
    // one, and recursively remove it from left or right subtree (current node is the parent)

  // Case: Two children
  if (tree->left != nullptr) {  // largest value in left subtree
    Node* predecessorParent = tree;
    // current node, moves to left child and keeps going right until largest value
    Node* predecessor = tree->left;
    while (predecessor->right != nullptr) {
      predecessorParent = predecessor;
      predecessor = predecessor->right;
    }
    // Copy predecessor key and count into current Node then remove
    tree->key = predecessor->key;
    tree->count = predecessor->count;
    predecessor->count = 1;
    remove(predecessorParent, predecessor, predecessor->key);
  } else if (tree->right != nullptr) {  // smallest value in right subtree if not possible
    Node* successorParent = tree;
    Node* successor = tree->right;
    // current node as parent, right child then go left until end
    while (successor->left != nullptr) {
      successorParent = successor;
      successor = successor->left;
    }
    // copy successor's key and count then remove
    tree->key = successor->key;
    tree->count = successor->count;
    successor->count = 1;
    remove(successorParent, successor, successor->key);
  }
  return;
}


