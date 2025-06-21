#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "Item.h"

#define MAX_ITEMS 100000000

////////////////////////////////////////////////////////////////////////

// Sorting algorithms
static void selectionSort(Item items[], int lo, int hi);

static void bubbleSort(Item items[], int lo, int hi);
static void insertionSort(Item items[], int lo, int hi);
static void shellSort(Item items[], int lo, int hi);
static void mergeSort(Item items[], int lo, int hi);
static void naiveQuickSort(Item items[], int lo, int hi);
static void medianOfThreeQuickSort(Item items[], int lo, int hi);
static void randomisedQuickSort(Item items[], int lo, int hi);

// Utilities provided: this is actually very useful to learn

// swap the item[j] to the position i
static inline void swap(Item items[], int i, int j);

// display every element in the array
static void display(Item items[], int lo, int hi);


// main function
int main(int argc, char* argv[]) {
    // allocate memory for the item: [AVOID STACK OVERFLOW]
    // Also in the future, when the typedef of item changed, we just need to change header, providing convenience
    Item* items = malloc(MAX_ITEMS * sizeof(Item));

    // check the availability 
	if (items == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}

    // read the input, use the defined function 'read', which stands for scanf, increased readability
    int n = 0;
    while (n < MAX_ITEMS && read(items[n]) == 1) {
        n++;
    }

    // then, we will use switch case structure to realize the orders
	/*
		SORT is a macro passed in through `clang -D`
		s - selection sort
		b - bubble sort
		i - insertion sort
		h - shell sort - not assessed in 25T1
		m - merge sort
		N - naive quick sort
		M - median of three quick sort
		R - randomised quick sort
		o - bogo sort
	*/

    // This error is because we will compile with clang -D, where DSORT = '', so we have define the SORT when
    // compiling this program, no need to worry here as long as compling with -DSORT, which we included in
    // makefile
	switch (SORT) {
		case 's': selectionSort(items, 0, n - 1);          break;
		case 'b': bubbleSort(items, 0, n - 1);             break;
		case 'i': insertionSort(items, 0, n - 1);          break;
		case 'h': shellSort(items, 0, n - 1);              break;
		case 'm': mergeSort(items, 0, n - 1);              break;
		case 'N': naiveQuickSort(items, 0, n - 1);         break;
		case 'M': medianOfThreeQuickSort(items, 0, n - 1); break;
		case 'R':
			srand(time(NULL));
			randomisedQuickSort(items, 0, n - 1);
			break;

		default:
			fprintf(stderr, "Invalid sorting method\n");
			exit(1);
			break;
	}
	// display results
	display(items, 0, n - 1);
}


////////////////////////////////////////////////////////////////////////
// Sorting Algorithms                                                 //
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Selection sort: All cases: O(n^2)

/**
 * 1. Find the smallest value
 * 2. Swap to the first
 * 3. Change the bondaries
 * 4. Repeat until the array is sorted
 */

static void selectionSort(Item items[], int lo, int hi) {

	// first to find the smallest, initialize it as the first element
    for (int i = lo; i < hi; i++) {

		// this is the index
		int min = i;
		
		for (int j = i + 1; j <= hi; j++) {
			// the compare logic: if the item[j] is smaller than the founded min

			if (lt(items[j], items[min])) {
				// update the index if smaller found
				min = j;
			}
		}

		swap(items, i, min);
		/**
		 * this also same as:
		 * 
		 * if min != j
		 * int temp = item[i];
		 * item[i] = item[min];
		 * item[min] = temp; 
		 */
	}

}

////////////////////////////////////////////////////////////////////////
// Bubble sort: O(n^2)

/**
 * 1. Compare adjacent element starting from the beginning
 * 2. Swap them if they are in wrong order
 * 3. Repeat with the reduced range
 */

static void bubbleSort(Item items[], int lo, int hi) {
	// from the highest index, so that each iteration could decrease the unsorted range
	for (int i = hi; i > lo; i--) {
		bool swapped = false;
		for (int j = lo; j < i; j++) {
			// compare to ajacent element
			if (gt(items[j], items[j+1])) {
				swap(items, j, j+1);
				swapped = true;
			}
		}

		// if no swap occur, the array is sorted
		if (!swapped) break;

	}


}


////////////////////////////////////////////////////////////////////////
// Insertion sort: O(n^2)

/**
 * 1. spliting the array into sorted part (the 1st element) and unsorted part (the rest of array)
 * 2. Taking one element from the unsorted and insert it to the right place
 */
static void insertionSort(Item items[], int lo, int hi) {
	for (int i = lo + 1; i <= hi; i++) {
		// current element should start from index 1, compare to index0, cause default is arr[0] is sortded
		Item key = items[i];
		int j = i - 1;	// start comparing with its previous value

		// compare the key to all its previous elements
		while (j >= lo && gt(items[j], key)) {
			items[j + 1] = items[j];	// shift this element right
			j--;
		}

		// to find the correct position for key
		items[j + 1] = key;
		
	}

}

////////////////////////////////////////////////////////////////////////
// Shell sort
///////////////////////////////////////////////////////////////////////

/**
 * Best case: O(nlogn) Else: depend on the gap sequence
 */

/**
 * 1. Choose a gap seqence
 * 2. h-sorting
 * 		Compare elements that are in h positions apart, swap if wrong order
 * 3. when gap = 1. perform insertion sort
 */

static void shellSort(Item items[], int lo, int hi) {

	// 1. Gap initialization
	int size = hi - lo + 1;
	int h;

	// using Knuth's sequence (1, 4, 13, 40...)
	// this step is used to calculate the largest valid gap
	for (h = 1; h <= (size - 1)/9; h = (3 * h) + 1);

	// 2. Perform gap insertion sort with decreasing gap
	while (h > 0) {

		// For each gap value, perform insertion sort on elements gap positions apart
		for (int i = lo + h; i <= hi; i++) {
			// store current eleemnt
			Item currentItem = items[i];

			// Find the position for ciurrent by compare to gap position before
			int j = i;

			// move elements that are greater than currentItem gap positions ahead
			while (j >= lo + h && gt(items[j - h], currentItem)){
				items[j] = items[j - h];	// shift elements forwardf
				j -= h;						// move back by h positions
			}

			// place curritem in its correct position
			items[j] = currentItem;

		}


		// reduce gap for next iteration
		h = h / 3;

	}


}

////////////////////////////////////////////////////////////////////////
// Mergesort: O(nlogn)

/**
 * 1. Divide the array into smaller subarrays
 * 2. recursviely sort these subarrays
 * 3. merge the sorted subarrays
 */

static void mergeSort(Item items[], int lo, int hi) {
	// Base case: if the lo > hi, return
	if (lo >= hi)	return;

	// Else. we will continue dividing
	int mid = (lo + hi) / 2;		// find the middle index
	mergeSort(items, lo, mid);		// sort left half	
	mergeSort(items, mid + 1, hi);	// sort right half
	merge(items, lo, mid, hi);		// merge the 2 haves


}

static void merge(Item items[], int lo, int mid, int hi) {

	// allocate temporary space
	Item* temp = malloc((hi - lo + 1) * sizeof(Item));

	int i = lo;
	int j = mid + 1;	// index starting from right side
	int k = 0;


	// Compare elements from both and pick smaller ones
	while (i <= mid && j <= hi) {
		if (le(items[i], items[j])) {
			temp[k++] = items[i++];
			/**
			 * This piece of code is post-increment(后加)
			 * same as:
			 * temp[k] = items[i];
			 * i++;
			 * k++;
			 * 
			 */
		} else {
			temp[k++] = items[j++];
		}
	}

	// Copy remaining if any
	while (i <= mid) temp[k++] = items[i++];
	while (j <= hi) temp[k++] = items[j++];

	// copy back to original array
	for (i = lo, k = 0; i <= hi; i++, k++) {
		items[i] = temp[k];
	}

	free(temp);
}

////////////////////////////////////////////////////////////////////////
// Quicksort: divide and conquer: 分而治之
// worst case O(n^2) Average: o(nlogn)

/**
 * 1. select a pivot element from array
 * 2. partition(分割) around the pivot
 * 3. recursivly sorting the subarrays
 */

static int partition(Item items[], int lo, int hi) {

	Item pivot = items[lo];

	int l = lo + 1;
	int r = hi;
	while(true) {
		while (l < r && le(items[l], pivot)) l++;
		while (l < r && ge(items[r], pivot)) r--;
		if (l == r) break;
		swap(items, l, r);

	}

	if (lt(pivot, items[l])) l--;
	swap(items, lo, l);
	return l;

}

static void naiveQuickSort(Item items[], int lo, int hi)
{
	if (lo >= hi) return;
	int pivotIndex = partition(items, lo, hi);
	naiveQuickSort(items, lo, pivotIndex - 1);
	naiveQuickSort(items, pivotIndex + 1, hi);
}




////////////////////////////////////
// Quick sort: Median of three
// reduce the chance of hitting worst case

static void medianOfThreeQuickSort(Item items[], int lo, int hi)
{
    if (lo >= hi) return;
    medianOfThree(items, lo, hi);
    int pivotIndex = partition(items, lo, hi);
    medianOfThreeQuickSort(items, lo, pivotIndex - 1);
    medianOfThreeQuickSort(items, pivotIndex + 1, hi);
}

static void medianOfThree(Item a[], int lo, int hi)
{
    int mid = (lo + hi) / 2;
    if (gt(a[mid], a[lo])) swap(a, mid, lo);
    if (gt(a[lo],  a[hi])) swap(a, lo,  hi);
    if (gt(a[mid], a[lo])) swap(a, mid, lo);
}
















// The inline keyword is a hint to the compiler suggesting it should replace function calls with the actual 
// function code directly, rather than making a traditional function call.
static inline void swap(Item items[], int i, int j) {
    int temp = items[i];
    items[i] = items[j];
    items[j] = temp;
}

static void display(Item items[], int lo, int hi) {

    // display all the elements in the array
    for (int i = lo; i < hi; i++) {
        show(i);
        printf("\n");
    }

}