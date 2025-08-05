#pragma once

#include <string>

using namespace std;
struct TreeNode {
  char data;
  char key;
  TreeNode* left;
  TreeNode* right;
  TreeNode(char data, char key)
    : data(data), key(key), left(nullptr), right(nullptr)
  {
  }
};

class arithmeticExpression {
private:
  std::string infixExpression;
  TreeNode* root;

public:
  /* Initializes an empty tree and sets the infixExpression
     to the value of parameter passed in. */
  arithmeticExpression(const string& expression);

  // Implementation of destructor is REQUIRED (and rule-of-three)
  ~arithmeticExpression();
  void deleteTree(TreeNode*);
  arithmeticExpression(const arithmeticExpression&) = delete;
  arithmeticExpression &operator=(const arithmeticExpression&) = delete;

  /* Converts the infixExpression to its equivalent postfix string
     and then generates the tree and assigns the root node to the 
     root data field. The key for the first node is 'a', 'b' for the second node and so on. */
  void buildTree();

  /* Calls the recursive infix function. */
  void infix() const;

  /* Calls the recursive prefix function. */
  void prefix() const;

  /* Calls the recursive postfix function. */
  void postfix() const;

private:
  /* Helper function that returns an integer according to
     the priority of the given operator. */
  static int priority(char);

  /* Helper function that returns the postfix notation equivalent
     to the given infix expression */
  string infix_to_postfix() const;

  /* Helper function that outputs the infix notation of the arithmetic expression tree
     by performing the inorder traversal of the tree.
     An opening and closing parenthesis must be added at the 
     beginning and ending of each expression. */
  void infix(TreeNode* subtree) const;

  /* Helper function that outputs the prefix notation of the arithmetic expression tree
     by performing the preorder traversal of the tree. */
  void prefix(TreeNode* subtree) const;

  /* Helper function that outputs the postfix notation of the arithmetic expression tree
     by performing the postorder traversal of the tree. */
  void postfix(TreeNode* subtree) const;
};
