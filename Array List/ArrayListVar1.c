#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    int elem[MAX];
    int count;
} List;

/* --- PROTOTYPES --- */
List initialize(); 
List insertPos(List L, int data, int position);
List deletePos(List L, int position);
int locate(List L, int data);
List insertSorted(List L, int data);
void display(List L);

int main() {
    List L = initialize();
    int found;

    printf("--- Inserting 1, 3, 5, 10 ---\n");
    L = insertPos(L, 1, 0);
    L = insertPos(L, 3, 1);
    L = insertPos(L, 5, 2);
    L = insertPos(L, 10, 3);
    display(L);

    found = locate(L, 5);
    if (found != -1) {
        printf("Search: Data found at index %d\n", found);
    } else {
        printf("Search: Data NOT found!\n");
    }

    printf("--- Inserting 8 (Sorted) ---\n");
    L = insertSorted(L, 8); 
    display(L);

    return 0;
}

List initialize() {
    List newL;
    // Logic: Create a temporary local list, set count to 0, and return it.
    // This effectively "resets" the list variable in main.
    newL.count = 0; 
    return newL;
}

List insertPos(List L, int data, int position) {
    int a;

    // Logic Step 1: Validation
    // A. Is the list full? (count < MAX)
    // B. Is the position valid? (0 to count)
    if (L.count < MAX && position >= 0 && position <= L.count) {
        
        // Logic Step 2: Shift Right (Make Space)
        // Loop backwards from the last element (count-1) down to 'position'.
        // Move each element one step to the right (a -> a+1).
        for (a = L.count - 1; a >= position; a--) {
            L.elem[a + 1] = L.elem[a];
        }

        // Logic Step 3: Insert & Update
        // Place data in the now-open slot and increment count.
        L.elem[position] = data;
        L.count++;
    } else {
        printf("Error: Invalid position or list full.\n");
    }
    // Logic Step 4: Return Updated Copy
    // Since we passed by value, we must return the modified struct.
    return L;
}

void display(List L) {
    int a;
    printf("List: ");
    // Logic: Iterate from 0 to count-1. Ignore garbage values beyond 'count'.
    for (a = 0; a < L.count; a++) {
        printf("%d | ", L.elem[a]);
    }
    printf("\n");
}

List deletePos(List L, int position) {
    int a;

    // Logic Step 1: Validation
    // Ensure position is within the current range of items (0 to count-1).
    if (position >= 0 && position < L.count) {
        
        // Logic Step 2: Shift Left (Close Gap)
        // Loop forwards from 'position' to the end.
        // Pull the element from the right (a+1) into the current slot (a).
        for (a = position; a < L.count - 1; a++) {
            L.elem[a] = L.elem[a + 1];
        }

        // Logic Step 3: Update Count
        // Decrease count. The duplicate value left at the end is ignored.
        L.count--;
    } else {
        printf("Error: Invalid position.\n");
    }
    return L;
}

int locate(List L, int data) {
    int a;
    // Logic: Linear Search
    // Return the index 'a' immediately if a match is found.
    for (a = 0; a < L.count; a++) {
        if (L.elem[a] == data) {
            return a;  
        }
    }
    // Logic: Return -1 if the loop completes without finding the data.
    return -1;
}

List insertSorted(List L, int data) {
    int a;

    // Logic Step 1: Check Full
    if (L.count >= MAX) {
        printf("List is full.\n");
        return L;
    }

    // Logic Step 2: Find Position & Shift
    // Start from end. If current element > data, move it right.
    // Stop when we find an element <= data, or reach the start.
    for (a = L.count - 1; a >= 0 && L.elem[a] > data; a--) {
        L.elem[a + 1] = L.elem[a];
    }
    
    // Logic Step 3: Insert
    // We insert at 'a + 1' because the loop stopped one index to the left.
    L.elem[a + 1] = data;
    L.count++;

    return L;
}