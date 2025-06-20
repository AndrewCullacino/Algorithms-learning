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
static inline void swap(Item items[], int i, int j);
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
// Selection sort

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