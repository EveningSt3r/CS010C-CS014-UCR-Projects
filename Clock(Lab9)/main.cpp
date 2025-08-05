#include <iostream>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <vector>
#include <memory>
#include <random>
#include <algorithm>
using std::cout;
using std::sort;
using std::endl;
using std::vector;
using std::clock_t;

const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000;  // clock per milliseconds
clock_t Start = clock();
// call sort function here
clock_t End = clock();
int elapsedTime = (End - Start)/CLOCKS_PER_MS;  // converts elapsed time from microseconds to milliseconds.


#include <chrono>
using std::chrono::steady_clock;
using std::chrono::microseconds;
using std::chrono::time_point;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;

// If using C++ 14, this is better as constexpr
const int NUMBERS_SIZE = 50000;

// Provided by zybooks
int genRandInt(int low, int high) {
  return low + rand() % (high - low + 1);
}

// Provided by zybooks
void fillArrays(int arr1[], int arr2[], int arr3[]) {
  for (int i = 0; i < NUMBERS_SIZE; ++i) {
    arr1[i] = genRandInt(0, NUMBERS_SIZE);
    arr2[i] = arr1[i];
    arr3[i] = arr1[i];
  }
}


int QPartition(int numbers[], int low, int high) {
  int midpoint = low + (high - low) / 2;
  int pivot = numbers[midpoint];
  // partition around middle element
  // all values less than pivot are moved left and vice versa
  // left partition returned, used by midpoint to sort subarrays
  bool done = false;
  while(!done) {
    while(numbers[low] < pivot) {
      // move low/high index forward
      ++low;
    }
    while(pivot < numbers[high]) {
      --high;
    }
    // If 0 or 1 elements left all #s are partitioned
    if(low >= high) {
      done = true;
    } else {
      // swap index at low and high
      int swapTemp = numbers[low];
      numbers[low] = numbers[high];
      numbers[high] = swapTemp;

      low += 1;
      high -= 1;
    }
  }
  return high;
}

void Quicksort_midpoint(int numbers[], int i, int k) {
  if(i >= k) {
    return;
  }
  int lowEndIndex = QPartition(numbers, i, k);
  // recursively call on both subarrays, low and high partition
  Quicksort_midpoint(numbers, i, lowEndIndex);
  Quicksort_midpoint(numbers, lowEndIndex + 1, k);
}

int partition_medianOfThree(int numbers[], int low, int high) {
  // first define pivot
  int pivot;
  int mid = (low + high) / 2;

  // select median value among numbers[low], mid, high
  if (numbers[low] < numbers[mid]) {
    if (numbers[mid] < numbers[high]) {
      pivot = mid;
    } else if (numbers[low] < numbers[high]) {
      pivot = high;
    } else {
      pivot = low;
    }
  } else {
    if (numbers[low] < numbers[high]) {
      pivot = low;
    } else if (numbers[mid] < numbers[high]) {
      pivot = high;
    } else {
      pivot = mid;
    }
  }

  // swap pivot and high, move pivot to the end
  int temp = numbers[pivot];
  numbers[pivot] = numbers[high];
  numbers[high] = temp;

  // pivot value at the end, start from beginning, one before pivot
  pivot = numbers[high];
  int left = low;
  int right = high - 1;

  // first part over, loop begins
  while(left <= right) {
    // move left index forward
    while(left <= right && numbers[left] <= pivot) {
      left++;
    }
    while(right >= left && numbers[right] >= pivot) {
      // move right index backward
      right--;
    }
    if(left < right) {
      // swap to correct portion of pivot
      int temp = numbers[left];
      numbers[left] = numbers[right];
      numbers[right] = temp;
    }
  }
  // pivot is reset to current position
  temp = numbers[left];
  numbers[left] = numbers[high];
  numbers[high] = temp;

  // final index of pivot is returned
  return left;
}

void Quicksort_medianOfThree(int numbers[], int i, int k) {
  // if low >= high array has 0 or 1 elements
  if(i >= k) {
    return;
  }
  // pivot's final position
  int lowEndIndex = partition_medianOfThree(numbers, i, k);

  // recursively sort left and right partition, (before and after pivot respectively)
  Quicksort_midpoint(numbers, i, lowEndIndex);
  Quicksort_midpoint(numbers, lowEndIndex + 1, k);
}

void InsertionSort(int numbers[], int numbersSize) {
  // i, j = inner, outer loop(s)
  int i = 0;
  int j = 0;

  // for every element
  for(i = 0; i < numbersSize; ++i) {
    j = i;
    // move current element leftward until correctly positioned
    // add it to "sorted" portion of the array
    // swap numbers[j] and numbers[j-1] to move the smaller element
    while(j > 0 && numbers[j] < numbers[j-1]) {
      int temp = numbers[j];
      numbers[j] = numbers[j-1];
      numbers[j-1] = temp;
      --j;
      // --j moves the inner loop
    }
  }
}

// We can compare other sorts we've talked about
static void BubbleSort(int numbers[], int n);

static void MergeSort(int numbers[], int left, int right);

// A helper function that will let us know if we have sorted
// everything
static bool is_sorted(int numbers[], int numbersSize) {
  if (numbersSize <= 0) return true;
  int last = numbers[0];
  for (int i=0; i < numbersSize; ++i) {
    int curr = numbers[i];
    if (curr < last) return false;
    last = curr;
  }
  return true;
}

static void copy_vector_into_array(const std::vector<int>& source, int array[]) {
  for (int i=0; i<static_cast<int>(source.size()); ++i) {
    array[i] = source[i];
  }
}

static void RadixSort(int numbers[], int size);

static void BubbleSort(int numbers[], int n) {
  for (int i = 0; i < n - 1; ++i) {
    for (int j = 0; j < n - i - 1; ++j) {
      if (numbers[j] > numbers[j + 1]) {
        std::swap(numbers[j], numbers[j + 1]);
      }
    }
  }
}

static void merge(int numbers[], int start, int mid, int end) {
  int start2 = mid + 1;

  // If the direct merge is already sorted
  if (numbers[mid] <= numbers[start2]) {
    return;
  }

  // Two pointers to maintain start of both sub-arrays to merge
  while (start <= mid && start2 <= end) {
    // If element 1 is in right place
    if (numbers[start] <= numbers[start2]) {
      start++;
    } else {
      int value = numbers[start2];
      int index = start2;

      // Shift all the elements between element 1
      // element 2, right by 1.
      while (index != start) {
        numbers[index] = numbers[index - 1];
        index--;
      }
      numbers[start] = value;

      // Update all the pointers
      start++;
      mid++;
      start2++;
    }
  }
}

static void MergeSort(int numbers[], int left, int right) {
  if (left < right) {
    int mid = (left + right)/2;
    MergeSort(numbers, left, mid);
    MergeSort(numbers, mid+1, right);
    merge(numbers, left, mid, right);
  }
}

static void RadixSort(int numbers[], int size) {
  // LOTS of assumptions here.  I assume all data are
  // postive integers;

  // I have to do passes based on the digits.  I stop
  // when I extract the largest digit
  int divisor = 1;
  bool more = true;
  for (int pass=0; more ; pass++) {
    // I need 10 buckets with a lot of room in them
    std::vector< std::vector<int> > buckets(10);
    for (int i=0; i < 10; ++i) buckets[i].reserve(NUMBERS_SIZE);

    // I pull off the pass'th digit and use it to put a number
    // into a bucket.  To get it, I divide by 1, 10, 100, 1000
    // and then do a modulo
    more = false;
    for (int i=0; i < size; ++i) {
      int digit = (numbers[i]/divisor)%10;
      if (numbers[i]/divisor/10 > 0) more = true;
      buckets[digit].push_back(numbers[i]);
    }
    divisor *= 10;

    // Copy the buckets back into numbers
    int index = 0;
    for (int i=0; i < 10; ++i) {
      const std::vector<int>& bucket = buckets[i];
      for (int j=0; j<static_cast<int>(bucket.size()); ++j) {
        numbers[index++] = bucket[j];
      }
    }
  }
}

int main() {
  // chrono time implementation(s) removed.
  std::vector<int> sample;
  sample.reserve(NUMBERS_SIZE);
  for (int i = 0; i < NUMBERS_SIZE; ++i) {
    sample.push_back(rand() % (NUMBERS_SIZE + 1));
  }
  // run test for sizes 10 100 1000 50000
  int test_sizes[4] = { 10, 100, 1000, 50000 };
  int test_array[NUMBERS_SIZE];
  for (int i=0; i < 4; ++i) {
    int size = test_sizes[i];
    cout << endl;
    cout << "-------------------- size " << size << " --------------------" << endl;

    // BUBBLE SORT
    {
      copy_vector_into_array(sample, test_array);
      clock_t Start = clock();
      BubbleSort(test_array, size);
      clock_t End = clock();
      int elapsedTime = (End - Start)/CLOCKS_PER_MS;
      cout << elapsedTime << " ms" << endl;

      cout << "Sort is " << ((is_sorted(test_array, size))?"GOOD":"BAD") << endl;
    }

    // MERGE SORT
    {
      copy_vector_into_array(sample, test_array);
      clock_t Start = clock();
      MergeSort(test_array, 0, size-1);
      clock_t End = clock();
      int elapsedTime = (End - Start)/CLOCKS_PER_MS;
      cout << elapsedTime << " ms" << endl;

      cout << "Sort is " << ((is_sorted(test_array, size))?"GOOD":"BAD") << endl;
    }

    // RADIX SORT
    {
      copy_vector_into_array(sample, test_array);
      clock_t Start = clock();
      RadixSort(test_array, size);
      clock_t End = clock();
      int elapsedTime = (End - Start)/CLOCKS_PER_MS;
      cout << elapsedTime << " ms" << endl;

      cout << "Sort is " << ((is_sorted(test_array, size))?"GOOD":"BAD") << endl;
    }
  }

  return 0;
}

