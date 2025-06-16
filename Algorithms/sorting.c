// This sorting algorithm
/**
 * consider 3 things:
 * n: the number of items (max - min + 1)
 * C: number of comparisons between items
 * S: number of times items are swapped
 * 
 * For input order:
 * random order
 * sorted order
 * reverse-sorted order
 * 
 * Sorting algorithm should be stable
 */
typedef struct {
    char *name;
    char *str[10];
} Item;

static inline void swap(Item items[], int i, int j)
{
	Item tmp = items[i];
	items[i] = items[j];
	items[j] = tmp;
}

// Elementary sorting algorithms

/**
 * Selection sort: keep selecting the minimum value in an array until sorted
 * Worst case: C = o(n^2)
 * Not stable
 * Not adaptive
 */
void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int smallest = i;       // assume current position has smallest
        
        // look through the rest to find actual smallest
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[smallest]) {
                smallest = j;  // found something smaller
            }
        }
        
        // swap the smallest with current position
        int temp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = temp;
    }
}

/**
 * Bubble sort: bigger bubbles rise faster to the surface. Similarly, larger numbers "bubble up" to the end of the array.
 * Worst case: C = O(n^2)
 * Stable
 * Adaptive
 */
void bubbleSort(int arr[], int size) {
    for (int i = size - 1; i > 0; i--) {
        bool swapped = false;
        
        // bubble through unsorted portion
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[j + 1]) {
                // swap adjacent elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        
        // if no swaps, array is sorted
        if (!swapped) break;
    }
}

/**
 * Insertion sort: builds a sorted portion from left to right by taking each element and inserting it into its correct position within the already-sorted part.
 * Worst case: C = O(n^2)
 * Stable
 * Adaptive
 */
void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int current = arr[i];  // element to insert
        int j = i;
        
        // shift larger elements to the right
        while (j > 0 && current < arr[j - 1]) {
            arr[j] = arr[j - 1];  // move element right
            j--;
        }
        
        // insert current element in correct position
        arr[j] = current;
    }
}

// Divide and conquer sorting algorithms

/**
 * Merge sort: split the array into 2 roughly equal size
 * C = O(log2N)
 */
void mergeSort(int arr[], int size) {
    mergeSortHelper(arr, 0, size - 1);
}

void mergeSortHelper(int arr[], int lo, int hi) {
    if (lo >= hi) return;  // base case: 1 or 0 elements
    
    int mid = (lo + hi) / 2;
    
    // divide: sort left and right halves
    mergeSortHelper(arr, lo, mid);
    mergeSortHelper(arr, mid + 1, hi);
    
    // conquer: merge the sorted halves
    merge(arr, lo, mid, hi);
}

void merge(int arr[], int lo, int mid, int hi) {
    // create temporary array
    int temp[hi - lo + 1];
    int i = lo, j = mid + 1, k = 0;
    
    // merge two sorted halves
    while (i <= mid && j <= hi) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    
    // copy remaining elements
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= hi) temp[k++] = arr[j++];
    
    // copy back to original array
    for (int x = 0; x < k; x++) {
        arr[lo + x] = temp[x];
    }
}


// Non-comparison sorting