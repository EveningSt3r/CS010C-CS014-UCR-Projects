#include <iostream>
#include "Heap.h"

using std::cout;
using std::runtime_error;
using std::endl;

Heap::Heap() : numItems(0) {}

Heap::~Heap() {
  // while data exists, delete and change size
  while(numItems > 0) {
    delete heap[numItems - 1];
    --numItems;
  }
}
// if heap is not full, allocate a new print job
// percolate up new print job and change size
void Heap::enqueue(PrintJob* job) {
  if(numItems >= MAX_HEAP_SIZE) {
    return;
  } else {
    heap[numItems] = job;
    percolateUp(numItems);
    ++numItems;
  }
}

// if numItems > 1, swap the root value with the last value in the back
// percolate down the root (now the last value) to restore heap property
void Heap::dequeue() {
  if(numItems < 1) {
    return;
  }
  if(numItems == 1) {
    heap[0] = nullptr;
    --numItems;
    return;
  }
  if(numItems > 1) {
    heap[0] = heap[numItems - 1];
    --numItems;
    trickleDown(0);
  }
}

PrintJob* Heap::highest() {
  // check and return heap[0] root (highest in max heap)
  if(numItems >= 1) {
    return heap[0];
  } else {
    return nullptr;
  }
}

void Heap::print() {
  // print the root (highest in max heap)'s data
  if(numItems < 1 || heap[0] == nullptr) {
    return;
  }
  try {
    cout << "Priority: " << highest()->getPriority() << ", ";
    cout << "Job Number: " << highest()->getJobNumber() << ", ";
    cout << "Number of Pages: " << highest()->getPages() << endl;
  } catch (const runtime_error& error) {
    cout << "Runtime error: " << error.what() << endl;
  }
}

void Heap::trickleDown(int nodeIndex) {
  // start at root and percolate down swapped max node until max heap is restored
  // find left child index
  int childIndex = 2 * nodeIndex + 1;
  // value to trickle down
  PrintJob* value = heap[nodeIndex];
  while(childIndex < numItems) {
    // only call to root, max value is current
    PrintJob *maxValue = value;
    int maxIndex = -1;
    // check left and right children if they exist
    for(int i = 0; i < 2 && i + childIndex < numItems; ++i) {
      if(heap[i + childIndex]->getPriority() > maxValue->getPriority()) {
        // if child has higher priority change max and change max index
        maxValue = heap[i + childIndex];
        maxIndex = i + childIndex;
      }
    }
    // If neither child has higher priority max heap has been restored
    if(maxValue == value) {
      return;
    } else {
      // swap with the larger child
      PrintJob* temp = heap[nodeIndex];
      heap[nodeIndex] = heap[maxIndex];
      heap[maxIndex] = temp;
      // move node at nodeIndex down to child's position
      nodeIndex = maxIndex;
      // left child is recomputed for loop restart
      childIndex = 2 * nodeIndex + 1;
    }
  }
}

void Heap::percolateUp(int nodeIndex) {
  // Percolate node at nodeIndex up the heap until max-heap property is restored
  while(nodeIndex > 0) {
    // parent node index
    int parentIndex = (nodeIndex - 1) / 2;
    // if the current node has lower or equal priority than its parent, stop
    // max-heap is restored
    if(heap[nodeIndex]->getPriority() <= heap[parentIndex]->getPriority()) {
      return;
    } else {
      // swap node at nodeIndex and node at parentIndex
      // set node Index to parentIndex before loop restarts
      PrintJob* temp = heap[nodeIndex];
      heap[nodeIndex] = heap[parentIndex];
      heap[parentIndex] = temp;
      nodeIndex = parentIndex;
    }
  }
}
