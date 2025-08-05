#pragma once
#include <iostream>

using std::ostream; 


struct IntNode {
    int data;
    IntNode *prev;
    IntNode *next;
    IntNode(int data) : data(data), prev(0), next(0) {}
};

class IntList {
    // dummyHead and dummyTail act as Nodes representing head and tail
    // These are never accessed but just make the head and tail not nullptr
    private:
        IntNode* dummyHead;
        IntNode* dummyTail;
    public:
        IntList();
        ~IntList();  // Rule of three, but we are only implementing the destructor
        IntList(const IntList&) = delete;  // Don't let C++ write these for you
        IntList& operator=(const IntList&) = delete;
        void push_front(int);
        void pop_front();
        void push_back(int);
        void pop_back();
        bool empty() const;
        friend ostream &operator<<(ostream&, const IntList&);
        void printReverse() const;

};