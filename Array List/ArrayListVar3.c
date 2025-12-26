#include <stdio.h>
#include <stdlib.h>

#define LENGTH 10

typedef struct {
    int *elemPtr; // Pointer to the dynamic array
    int count;    // Current number of items
    int max;      // Current capacity (size of the malloc'd array)
} List;

List initialize(); // [FIX] Removed parameter, we just need to return a new list
List insertPos(List L, int data, int position);
List deletePos(List L, int position);
int locate(List L, int data);
List insertSorted(List L, int data);
void display(List L);
List resize(List L);

int main() {
    List L = initialize(); // [FIX] Clean initialization
    int found;

    L = insertPos(L, 1, 0);
    L = insertPos(L, 3, 1);
    L = insertPos(L, 5, 2);
    L = insertPos(L, 10, 3);
    
    // Logic: This will trigger a resize if we exceeded LENGTH (10)
    // For testing, you could set LENGTH to 2 to see it happen sooner.
    L = insertSorted(L, 8);

    found = locate(L, 5);
    if (found != -1) {
         printf("Data found at position %d!\n", found);
    } else {
         printf("Data NOT found!\n");
    }

    display(L);
    
    // [NOTE] Since we used malloc, good practice suggests freeing memory at the end, 
    // but for this specific exercise structure (Pass-by-value), it's complex to implement a destructor.
    // The OS will reclaim memory when the program ends.
    return 0;
}

List initialize() {
    List L;
    // Logic: Start with 0 items, but reserve space for LENGTH (10) items.
    L.count = 0;
    L.max = LENGTH;
    L.elemPtr = malloc(sizeof(int) * LENGTH);
    
    // Logic: Always check if the computer actually gave us the memory.
    if (L.elemPtr == NULL) {
        printf("Memory allocation failed.\n");
        exit(1); 
    }
    return L;
}

List insertPos(List L, int data, int position) {
    int a;
    
    // Logic Step 1: Check Capacity
    // If the list is full, we must expand the array before we can add anything.
    if (L.count >= L.max) {
        L = resize(L);
    }

    // Logic Step 2: Validation & Shifting
    // [FIX] I moved the insertion logic INSIDE this if block.
    // We must ensure position is valid (0 to count) before touching memory.
    if (position >= 0 && position <= L.count) {
        
        // Logic: Shift Right (Make Space)
        // Start from the last item and pull it to the right.
        for (a = L.count - 1; a >= position; a--) { 
            L.elemPtr[a + 1] = L.elemPtr[a];
        }
        
        // Logic: Insert & Update
        L.elemPtr[position] = data;
        L.count++;
    } else {
        printf("Invalid position!\n");
    }
    
    return L;
}

List resize(List L) {
    // Logic: Exponential Growth
    // We double the size (max * 2). This is efficient because we don't want to 
    // call realloc every single time we add one number.
    // 
    int newSize = 2 * L.max;
    int *temp = realloc(L.elemPtr, sizeof(int) * newSize);
    
    if (temp == NULL) {
        printf("Resize failed.\n");
        // Note: If realloc fails, the original data is still safe in L.elemPtr,
        // but here we exit because we can't continue.
        free(L.elemPtr); 
        exit(1);
    }
    
    // Logic: Update the struct to match the new reality
    L.elemPtr = temp;
    L.max = newSize;
    
    printf("DEBUG: Array resized to %d\n", L.max); // Optional: Helps you see it happen
    return L;
}

void display(List L) {
    int a;
    // Logic: Only print valid items (up to count), not the empty space (max).
    for (a = 0; a < L.count; a++) {
        printf("%d | ", L.elemPtr[a]);
    }
    printf("\n");
}

List deletePos(List L, int position) {
    int a;
    
    // Logic Step 1: Validation
    if (position < 0 || position >= L.count) {
        printf("Invalid position!\n");
        return L;
    }

    // Logic Step 2: Shift Left (Close Gap)
    // We overwrite the item at 'position' by pulling the next item left.
    for (a = position; a < L.count - 1; a++) {
        L.elemPtr[a] = L.elemPtr[a + 1];
    }
    
    // Logic Step 3: Update Count
    L.count--;
    return L;
}

int locate(List L, int data) {
    int a;
    // Logic: Linear Search
    for (a = 0; a < L.count; a++) {
        if (L.elemPtr[a] == data) {
            return a;
        }
    }
    return -1;
}

List insertSorted(List L, int data) {
    int a;
    
    // Logic Step 1: Expansion Check
    if (L.count >= L.max) {
        L = resize(L);
    }
    
    // Logic Step 2: Find & Shift
    // Loop runs as long as we haven't hit the start (a>=0) 
    // AND the current number is bigger than our data.
    for (a = L.count - 1; a >= 0 && L.elemPtr[a] > data; a--) {
        L.elemPtr[a + 1] = L.elemPtr[a];
    }
    
    // Logic Step 3: Insert
    L.elemPtr[a + 1] = data;
    L.count++;

    return L;
}