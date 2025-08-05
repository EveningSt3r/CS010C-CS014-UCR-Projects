#include "IntList.h"

#include <iostream>
#include <string>
using std::ostream;
using std::runtime_error;
using std::cout;
// Not using namespace std

IntList::IntList() {
    dummyHead = new IntNode(-1);  // dummy Nodes set to -1 not to confuse
    dummyTail = new IntNode(-1);
    dummyHead->next = dummyTail;
    dummyHead->prev = nullptr;
    dummyTail->prev = dummyHead;
    dummyTail->next = nullptr;
}

IntList::~IntList() {
    /* Destructor goes through all Nodes and deletes 
    while using temp variable to not memory leak */
    IntNode *curr = dummyHead;
    while(curr != nullptr) {
        IntNode *toDelete = curr;
        curr = curr->next;
        delete toDelete;
    }
}

ostream &operator<<(ostream &out, const IntList &rhs) {
    /* Replacement operator prints all Nodes in a list,
    not outputting a space for the last entry. */
    IntNode *curr = rhs.dummyHead->next;
    while(curr != rhs.dummyTail) {
        out << curr->data;
        if(curr->next != rhs.dummyTail) {
            out << " ";
        }
        curr = curr->next;
    }
    return out;
}

void IntList::push_front(int value) {
    /* push_front inserts a node with parameter value
    at the front of the list (after the dummyHead) */
    IntNode* frontNode = new IntNode(value);
    if(empty()) {
        // Special case for empty list
        dummyHead->next = frontNode;
        dummyTail->prev = frontNode;
        frontNode->next = dummyTail;
        frontNode->prev = dummyHead;
    } else {
        // non special case
        dummyHead->next->prev = frontNode;
        frontNode->next = dummyHead->next;
        dummyHead->next = frontNode;
        frontNode->prev = dummyHead;
    }
}

void IntList::pop_front() {
    // pop_front removes the node at the front of the list (after dummyHead)
    if(empty()) {  // If list is empty special case, nothing happens
        throw runtime_error("List is empty, nothing to remove");
    } else {  // Otherwise create temprorary node for deletion
        IntNode* toRemove = dummyHead->next;
        dummyHead->next = toRemove->next;
        toRemove->next->prev = dummyHead;
        delete toRemove;
    }
}

void IntList::push_back(int value) {
    /* push_back inserts a node of parameter value 
    at the back of the list (before the dummyTail) */
    if(empty()) {
        // If the list is empty push_front fulfills the same purpose
        push_front(value);
    } else {
        // Otherwise update pointers accordingly at the back
        IntNode* backNode = new IntNode(value);
        backNode->prev = dummyTail->prev;
        dummyTail->prev->next = backNode;
        dummyTail->prev = backNode;
        backNode->next = dummyTail;
    }
}

void IntList::pop_back() {
    // pop_back removes the last Node (before dummyTail)
    if(empty()) {
        // If list is empty throw error because nothing to remove
        throw runtime_error("List is empty, nothing to remove");
    } else {
        // Otherwise update pointers accordingly at the back with a temprorary Node for deletion
        IntNode* toRemove = dummyTail->prev;
        toRemove->prev->next = dummyTail;
        dummyTail->prev = toRemove->prev;
        delete toRemove;
    }
}

bool IntList::empty() const {
    // Returns boolean if dummyHead's next pointer is the tail (list is otherwise empty)
    return(dummyHead->next == dummyTail);
}

void IntList::printReverse() const {
    /* Our double-linked list allows us to iterate backwards
    By starting at dummyTail and accessing prev we can access
    all the data in the list*/
    IntNode* curr = dummyTail->prev;
    while(curr != dummyHead) {
        cout << curr->data;
        if(curr->prev != dummyHead) {
            cout << " ";
        }
        curr = curr->prev;
    }
}
