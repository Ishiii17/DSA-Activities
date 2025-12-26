#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Logic: The "Repair" function (often called siftDown or sinkDown).
// It assumes the subtrees are already heaps, but the root 'i' might be too small.
// It pushes 'i' down the tree until it dominates its children.
void heapify(int arr[], int n, int i) {
    int largest = i;       // Initialize largest as root
    int left = 2 * i + 1;  // Calculate left child index
    int right = 2 * i + 2; // Calculate right child index

    // Logic Step 1: Compare with Left Child
    // Check if left child exists (left < n) AND is bigger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Logic Step 2: Compare with Right Child
    // Check if right child exists AND is bigger than whatever is currently largest
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Logic Step 3: Swap and Recurse
    // If the root wasn't the largest, swap it with the winner.
    if (largest != i) {
        swap(&arr[i], &arr[largest]);

        // Logic: The child at 'largest' is now changed, so we must 
        // fix that subtree too. (Recursively push the value down)
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    // Logic Phase 1: Build the Max-Heap
    // We start from the last non-leaf node (n / 2 - 1) and go up to 0.
    // Why? Because leaf nodes are already valid heaps of size 1.
    // We only need to fix the parents.
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Logic Phase 2: Extract Elements
    // At this point, arr[0] is the biggest number in the array.
    for (int i = n - 1; i > 0; i--) {
        
        // Step A: Move current root (largest) to the end of the array.
        // It is now in its final sorted position.
        swap(&arr[0], &arr[i]);

        // Step B: Repair the reduced heap
        // We call heapify on the root (index 0) with size 'i'.
        // We reduced size by 1 so the sorted elements at the end are ignored.
        heapify(arr, i, 0);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    heapSort(arr, n);
    printArray(arr, n);

    return 0;
}