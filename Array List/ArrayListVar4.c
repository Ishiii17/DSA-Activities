#include <stdio.h> 
#include <stdlib.h>

#define LENGTH 10

typedef struct{
    int *elemPtr; // Pointer to the dynamic array on the Heap
    int count;    // Number of active items
    int max;      // Total capacity of the array
} List;

// Prototypes (Notice we return 'void' now because we modify via pointer)
void initialize(List *L);
void insertPos(List *L, int data, int position);
void deletePos(List *L, int position);
int locate(List *L, int data);
int retrieve(List *L, int position);
void insertSorted(List *L, int data);
void display(List *L);
void resize(List *L);
void makeNULL(List *L);

int main(){
    List L; // L is created here on the Stack
    int found, ret;
    
    // We pass '&L' (the address of L) so the function can edit it directly
    initialize(&L);
    
    insertPos(&L, 1, 0);
    insertPos(&L, 3, 1);
    insertPos(&L, 5, 2);
    insertPos(&L, 10, 3);
    
    insertSorted(&L, 8);
    
    // Logic: Retrieve gets the value at index 2 (which should be 5)
    ret = retrieve(&L, 2);
    printf("Data retrieved is %d\n", ret);
    
    display(&L);
    
    // Logic: Clean up memory before the program ends
    makeNULL(&L);
    
    return 0;
}

void initialize(List *L){
    // Logic: Request memory for the array and link it to elemPtr
    L->elemPtr = malloc(sizeof(int) * LENGTH);
    if (L->elemPtr == NULL){
        printf("Memory allocation failed!");
        exit(1);
    }
    // Logic: Set initial capacity and count
    L->max = LENGTH;
    L->count = 0;
}

void resize(List *L) {
    // Logic: Attempt to double the memory size while keeping existing data
    int *temp = realloc(L->elemPtr, sizeof(int) * 2 * L->max);
    if (temp == NULL) {
        printf("Memory reallocation failed!");
        exit(1);
    }
    // Logic: Update pointer and double the max capacity tracker
    L->elemPtr = temp;
    L->max *= 2;
}

void insertPos(List *L, int data, int position) {
    int a;
    
    // Logic Step 1: Validate Position
    // We allow position == count (appending), but not greater.
    if (position < 0 || position > L->count) {
        printf("Invalid position!\n");
        return;
    }
    
    // Logic Step 2: Check Capacity
    // If full, resize immediately before trying to shift.
    if (L->count == L->max) {
        resize(L);
    }
    
    // Logic Step 3: Shift Right
    // Start from end, move elements one step right to make a hole.
    for (a = L->count - 1; a >= position; a--) {
        L->elemPtr[a + 1] = L->elemPtr[a];
    }
    
    // Logic Step 4: Insert and Increment
    L->elemPtr[position] = data;
    L->count++;
}

void display(List *L){
    int a;
    // Logic: Iterate only through active items (0 to count)
    for(a = 0; a < L->count; a++){
        printf("%d | ", L->elemPtr[a]);
    }
    printf("\n");
}

void deletePos(List *L, int position){
    int a;
    
    // Logic Step 1: Validate Position
    // Unlike insert, we cannot delete at 'count' because that index is empty.
    if (position < 0 || position >= L->count) {
        printf("Invalid position!\n");
        return;
    }

    // Logic Step 2: Shift Left
    // Overwrite the target by pulling elements from the right.
    for(a = position; a < L->count - 1; a++){
        L->elemPtr[a] = L->elemPtr[a + 1];
    }
    
    // Logic Step 3: Decrement
    L->count--;
}

int locate(List *L, int data){
    int a;
    // Logic: Linear Search
    for(a = 0; a < L->count; a++){
        if(L->elemPtr[a] == data){
            return a;
        }
    }
    return -1;
}

int retrieve(List *L, int position) {
    // Logic: Check bounds before accessing
    // Note: exit(1) is a strict choice; it kills the program if index is wrong.
    if (position < 0 || position >= L->count) {
        printf("Invalid position!\n");
        exit(1); 
    }
    // Logic: Return the value at that specific index
    return L->elemPtr[position];
}

void insertSorted(List *L, int data){
    int a;
    
    // Logic Step 1: Check Capacity
    if (L->count == L->max){
        resize(L);
    }
    
    // Logic Step 2: Shift Right while Searching
    // As long as we see a number bigger than 'data', we scoot it to the right.
    for(a = L->count - 1; a >= 0 && L->elemPtr[a] > data; a--){
        L->elemPtr[a + 1] = L->elemPtr[a];
    }
    
    // Logic Step 3: Insert
    // 'a' is now at the smaller number (or -1), so we insert at 'a+1'.
    L->elemPtr[a + 1] = data;
    L->count++;
}

void makeNULL(List *L){
    // Logic: Manual Destructor
    // 1. Free the Heap memory (the array).
    free(L->elemPtr);
    // 2. Set pointer to NULL to prevent accidental use (Dangling Pointer).
    L->elemPtr = NULL;
    // 3. Reset stats.
    L->count = 0;
    L->max = 0;
}