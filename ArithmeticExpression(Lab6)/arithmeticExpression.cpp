#include <iostream>
#include <sstream>
#include <stack>
#include <string>

#include "arithmeticExpression.h"

using std::cout;

arithmeticExpression::arithmeticExpression(const string& expression)
: infixExpression(expression), root(nullptr) {}
// Initialize expression tree

arithmeticExpression::~arithmeticExpression() {
    deleteTree(root);
}
// Calls helper function

void arithmeticExpression::deleteTree(TreeNode* tree) {
    if(tree == nullptr) {
        return;
    }
    deleteTree(tree->left);
    deleteTree(tree->right);
    delete tree;
}
// recursively deletes tree starting from root (called in base function)


void arithmeticExpression::buildTree() {
    // calls postfix function then makes stack
    string postFix = infix_to_postfix();
    stack<TreeNode*> charStack;
    // ab+cde+** = (a+b) * (c * (d+e))
    for(char ch : postFix) {
        if(isalpha(ch)) {
            // if character in postfix is a letter, pushes
            charStack.push(new TreeNode(ch, 0));
        } else {
            // if is an expression, builds new tree node based on stack
            TreeNode* expr = new TreeNode(ch, 0);
            TreeNode* right = charStack.top();
            charStack.pop();
            TreeNode* left = charStack.top();
            charStack.pop();
            expr->right = right;
            expr->left = left;
            charStack.push(expr);
            // remaining nodes are popped and expression node is pushed
        }
    }
    root = charStack.top();
    // once loop finishes, root node is the base expression (top of stack)
}

void arithmeticExpression::infix() const {
    infix(root);
    // calls helper function
}

void arithmeticExpression::infix(TreeNode* subtree) const {
    // if there is no more left subtree, print ( to start operation
    if(subtree != nullptr) {
        if(subtree->left != nullptr) {
            cout << "(";
        }
        // otherwise, traverse inOrder normally
        infix(subtree->left);
        cout << subtree->data;
        infix(subtree->right);
        // at the end of right subtree, close ) for operation
        if(subtree->right != nullptr) {
            cout << ")";
        }
    }
}

void arithmeticExpression::prefix() const {
    prefix(root);
    // calls helper function
}

void arithmeticExpression::prefix(TreeNode* subtree) const {
    if(subtree == nullptr) {
        return;
    }
    // normal preOrder traversal, print, left, right
    cout << subtree->data;
    prefix(subtree->left);
    prefix(subtree->right);
}

void arithmeticExpression::postfix() const {
    postfix(root);
    // calls helper function
}

void arithmeticExpression::postfix(TreeNode* subtree) const {
    if(subtree == nullptr) {
        return;
    }
    // normal postOrder traversal, left, right, print
    postfix(subtree->left);
    postfix(subtree->right);
    cout << subtree->data;
}

int arithmeticExpression::priority(char op) {
    int priority = 0;
    if (op == '(') {
        priority =  3;
    } else if (op == '*' || op == '/') {
        priority = 2;
    } else if (op == '+' || op == '-') {
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix() const {
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i < infixExpression.size(); ++i) {
        c = infixExpression.at(i);
        if (c == ' ') {
            continue;
        }
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') {  // c is an operator
            if ( c == '(') {
                s.push(c);
            } else if (c == ')') {
                while(s.top() != '(') {
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            } else {
                while(!s.empty() && priority(c) <= priority(s.top())) {
                    if (s.top() == '(') {
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        } else {  // c is an operand
            oss << c;
        }
    }
    while(!s.empty()) {
        oss << s.top();
        s.pop();
    }
    return oss.str();
}
