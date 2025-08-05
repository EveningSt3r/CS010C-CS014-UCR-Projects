#pragma once
#include "PrintJob.h"


class Heap {
private:
  static const int MAX_HEAP_SIZE = 10;

  PrintJob* heap[MAX_HEAP_SIZE];      // Notice this is an array of PrintJob pointers
  int numItems;  // current number of items in heap

public:
  /* Initializes an empty heap.*/
  Heap();
  ~Heap();
  Heap(const Heap& other) = delete;
  Heap& operator=(const Heap &rhs) = delete;

  /* Inserts a PrintJob to the heap without
  violating max-heap properties.*/
  void enqueue(PrintJob* job);

  /* Removes the node with highest priority from the heap. 
  Follow the algorithm on priority-queue slides. */
  void dequeue();

  /* Returns the node with highest priority.*/
  PrintJob* highest();

  /* Prints the PrintJob with highest priority in the following format:
     Priority: priority, Job Number: jobNum, Number of Pages: numPages
     (Add a new line at the end.) */
  void print();

private:
  void percolateUp(int nodeIndex);
  void trickleDown(int nodeIndex);
};
