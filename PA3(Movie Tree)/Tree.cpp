#include "Tree.h"
#include <iostream>
#include <string>

using std::endl;
using std::cout;
using std::runtime_error;

// 'static' means these functions are only usable in the scope of Tree.cpp

static const string& midStr( const string& s1, const string& s2, const string& s3 ) {
  if (( s1 < s2 && s1 > s3 ) ||( s1 < s3 && s1 > s2 ) )
    return s1;
  else if (( s2 < s1 && s2 > s3 ) ||( s2 < s3 && s2 > s1 ) )
    return s2;
  else
    return s3;
}

static const string& minStr( const string& s1, const string& s2, const string& s3 ) {
  if ( s1 < s2 && s1 < s3 )
    return s1;
  else if ( s2 < s1 && s2 < s3 )
    return s2;
  else
    return s3;
}

static const string& maxStr( const string& s1, const string& s2, const string& s3 ) {
  if ( s1 > s2 && s1 > s3 )
    return s1;
  else if ( s2 > s1 && s2 > s3 )
    return s2;
  else
    return s3;
}

Tree::Tree() {
  root = NULL;
}

Tree::~Tree() {
  destroy(root);
}

void Tree::destroy(Node* node) {
  if(node == nullptr) {
    return;
  }
  destroy(node->left);
  destroy(node->middle);
  destroy(node->right);

  delete node;
}

void Tree::split(Node* curr, const string& word) {
    if (curr->numData != 2) {
      return;
    }
    if (word == curr->small || word == curr->large) {
      throw runtime_error("Duplicate");
    }

    string leftKey = minStr(curr->small, curr->large, word);
    string rightKey = maxStr(curr->small, curr->large, word);
    string middleToPromote = midStr(curr->small, curr->large, word);

    Node* leftChild = new Node(leftKey);
    Node* rightChild = new Node(rightKey);

    if (curr->parent == nullptr) {
        // curr is root → make a new root
        curr->small = middleToPromote;
        curr->large = "";
        curr->left = leftChild;
        curr->middle = rightChild;
        curr->right = nullptr;
        curr->numData = 1;
        leftChild->parent = curr;
        rightChild->parent = curr;
        return;
    }

    // assume curr has a parent but curr is not full
    Node* parent = curr->parent;

    // Determine position of curr
    // This tells us where to insert the promoted key and new children
    if (curr == parent->left) {
        // Shift parent small to large
        parent->large = parent->small;
        parent->small = middleToPromote;

        parent->right = parent->middle;
        parent->left = leftChild;
        parent->middle = rightChild;
    } else if (parent->middle == nullptr || curr == parent->middle) {
        // Insert promoted key into second slot (already ordered)
        parent->large = middleToPromote;

        parent->middle = leftChild;
        parent->right = rightChild;
    } else if (curr == parent->right) {
        // Keep parent->small where it is
        parent->large = middleToPromote;

        parent->middle = leftChild;
        parent->right = rightChild;
    }

    parent->numData = 2;
    delete curr;
}


bool Tree::isLeaf(Node* curr) {
  if(curr->numData == 1) {
    return(curr->left == nullptr && curr->right == nullptr);
  } else {
    return(curr->left == nullptr && curr->middle == nullptr && curr->right == nullptr);
  }
}

void Tree::insert( const string& word ) {
  if ( root == nullptr ) {
    root = new Node( word );
  } else {
    insert( root, word );
  }
}


void Tree::insert(Node* curr, const string& word) {
  if (curr->small == word || curr->large == word) {
    return;  // duplicate
  }

  if (isLeaf(curr)) {
    if (curr->numData == 1) {
      // Insert into 2-node leaf
      if (word < curr->small) {  // insert as small if word is smaller
        addData(curr, word);
      } else {  // insert as large
        curr->large = word;
      }
      curr->numData = 2;
    } else {
      // Node is full (3-node leaf), split required
      split(curr, word);
    }
    return;
  }

  // recursive step - traversal
  if (word < curr->small) {
    insert(curr->left, word);
  } else if (curr->numData == 1 || (curr->numData == 2 && word < curr->large)) {
    // if two-node OR three-node and word belongs in middle
    if (curr->middle != nullptr) {
      insert(curr->middle, word);
    } else if (curr->numData == 2 && word > curr->large) {
      // all other cases insert at right
      insert(curr->right, word);
    } else {
      insert(curr->middle, word);
    }
  }
}

// This is handy since it puts a key into the right spot (small or large string)
void Tree::addData( Node* addHere, const string& word ) {
  if(word < addHere->small) {
    addHere->large = addHere->small;
    addHere->small = word;
  } else {
    addHere->large = word;
  }
  addHere->numData = 2;
}

void Tree::preOrder() const {
  preOrder( root );
  cout << endl;
}

void Tree::preOrder( const Node* curr ) const {
  if(curr == nullptr) {
    return;
  }
  cout << curr->small << ", ";
  preOrder(curr->left);
  if(!curr->large.empty()) {
    cout << curr->large << ", ";
  }
  preOrder(curr->middle);
  preOrder(curr->right);
}

void Tree::inOrder() const {
  inOrder( root );
  cout << endl;
}

void Tree::inOrder(const Node* curr) const {
  if(curr == nullptr) {
    return;
  }
  inOrder(curr->left);
  cout << curr->small << ", ";
  inOrder(curr->middle);
  if(!curr->large.empty()) {
    cout << curr->large << ", ";
  }
  inOrder(curr->right);
}

void Tree::postOrder() const {
  postOrder( root );
  cout << endl;
}

void Tree::postOrder(const Node* curr) const {
  if(curr == nullptr) {
    return;
  }
  postOrder(curr->left);
  postOrder(curr->middle);
  cout << curr->small << ", ";
  postOrder(curr->right);
  if(!curr->large.empty()) {
    cout << curr->large << ", ";
  }
}

void Tree::remove(const string& word, Node* curr) {
    if (curr == nullptr) return;  // Avoid dereferencing nullptr

    // Only compare to large if node has two keys
    if (word < curr->small && curr->left != nullptr) {
        remove(word, curr->left);
    } else if (curr->numData == 2 && word > curr->large && curr->right != nullptr) {
        remove(word, curr->right);
    } else if (word > curr->small && curr->middle != nullptr
      && (curr->numData != 2 || word < curr->large)) {
      remove(word, curr->middle);
  } else if (word > curr->small && (curr->numData == 1) && curr->right != nullptr) {
      remove(word, curr->right);
    }

    // Found node with matching key — start handling deletion
    if (word == curr->small) {
        if (isLeaf(curr)) {
            if (curr == root) {
                // Leaf root
                if (curr->numData == 2) {
                    // Root has two keys, remove small and shift large
                    curr->small = curr->large;
                    curr->large = "";
                    curr->numData = 1;
                } else {
                    // Delete last key in tree
                    delete root;
                    root = nullptr;
                }
            } else {
                // Leaf non-root
                if (curr->numData == 2) {
                    // Remove small, shift large
                    curr->small = curr->large;
                    curr->large = "";
                    curr->numData = 1;
                } else {
                    // One-key leaf: delete node and adjust parent
                    Node* parent = curr->parent;

                    if (parent->left == curr) {
                        if (parent->middle != nullptr) {
                            string middleVal = parent->middle->small;
                            delete parent->middle;
                            parent->middle = nullptr;
                            delete curr;
                            parent->left = nullptr;

                            // Shift parent key
                            parent->large = middleVal;
                            parent->numData = 2;
                        }
                    } else if (parent->middle == curr) {
                        if (parent->left != nullptr) {
                            string leftVal = parent->left->small;
                            delete parent->left;
                            parent->left = nullptr;
                            delete parent->middle;
                            parent->middle = nullptr;

                            parent->large = parent->small;
                            parent->small = leftVal;
                            parent->numData = 2;
                        } else {
                          delete curr;
                          curr = nullptr;
                          parent->middle = nullptr;
                          return;
                        }
                    } else if (parent->right == curr) {
                        if (parent->left != nullptr) {
                            string leftVal = parent->left->small;
                            delete parent->left;
                            parent->left = nullptr;
                            delete parent->right;
                            parent->right = nullptr;
                            parent->large = parent->small;
                            parent->small = leftVal;
                            parent->numData = 2;
                        } else {
                          delete curr;
                          curr = nullptr;
                          parent->right = nullptr;
                          return;
                        }
                    }
                }
            }
        } else {
            // Internal node — promote a child value up
            if (curr->left && curr->middle) {
                curr->small = curr->left->small;
                curr->large = curr->middle->small;
                delete curr->left;
                delete curr->middle;
                curr->left = nullptr;
                curr->middle = nullptr;
                curr->numData = 1;
            }
        }
    } else if (curr->numData == 2 && word == curr->large) {
        // Simply remove large
        curr->large = "";
        curr->numData = 1;
    }
}



void Tree::remove(const string& word) {
  if(search(word) == nullptr) {
    return;
  }
  remove(word, root);
}


// Check if a given node (sibling) has any siblings with two children (one key)
bool Tree::hasTwoChildSibling(Node* sib) const {
  if(sib == nullptr || sib->parent == nullptr) {
    return false;
  }
  int childCount;
  if(sib->parent->numData == 1) {
    childCount = 2;
  } else {
    childCount = 3;
  }
  if(childCount == 2) {
    if(sib->parent->left == sib) {
      return(sib->parent->right->numData == 1);
    } else {
      return(sib->parent->left->numData == 1);
    }
  }
  if(childCount == 3) {
    if(sib->parent->left == sib) {
      return(sib->parent->right->numData == 1 || sib->parent->middle->numData == 1);
    } else if (sib->parent->middle == sib) {
      return(sib->parent->left->numData == 1 || sib->parent->right->numData == 1);
    } else {
      return(sib->parent->left->numData == 1 || sib->parent->middle->numData == 1);
    }
  }
  return false;
}


Node* Tree::search(const string& word) {
  return search(root, word);
}

Node* Tree::search( Node* curr, const string& word ) {
  if(curr == nullptr) {
    return nullptr;
  }
  if(curr->small == word || (curr->numData == 2 && curr->large == word)) {
    return curr;
  }

  if(word < curr->small) {
    return search(curr->left, word);
  } else if ((curr->numData == 1 && word > curr->small)
  || (curr->numData == 2 || word < curr->large)) {
    return search(curr->middle, word);
  } else {
    return search(curr->right, word);
  }
  return nullptr;
}
