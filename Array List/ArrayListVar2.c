#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct{
    int elem[MAX];
    int count;
} Etype, *EPtr;

void initialize(EPtr L); 
void insertPos(EPtr L, int data, int position);
void deletePos(EPtr L, int position);
int locate(EPtr L, int data);
void insertSorted(EPtr L, int data);
void display(EPtr L);

int main(){
    EPtr L = (EPtr)malloc(sizeof(Etype));
    initialize(L);
    
    insertPos(L,1,0);
    insertPos(L,3,1);
    insertPos(L,5,2);
    insertPos(L,10,3);
    
    insertSorted(L,8);

    int found = locate(L,5);
    if (found != -1){
        printf("Data found at position %d!\n", found);
    } else {
        printf("Data NOT found!\n");
    }
    display(L);
    return 0;
}

void initialize(EPtr L){
    // Logic: Set the counter to 0 so the list is considered "empty".
    // We use the arrow (->) because L is a pointer.
    L->count = 0;
}

void insertPos(EPtr L, int data, int position){
    int a;
    
    // Logic Step 1: Validation
    // We check two things:
    // A. Is the list full? (count < MAX)
    // B. Is the position valid? (Cannot skip slots, e.g., putting data at pos 5 when we only have 2 items)
    if(L->count < MAX && position >= 0 && position <= L->count) {
        
        // Logic Step 2: Shifting to make space (The "Scoot Over" Loop)
        // We start from the LAST item and move backwards to the desired position.
        // We copy the item from index 'a' to 'a+1' (one step to the right).
        // This creates a duplicate open slot at 'position'.
        for(a = L->count - 1; a >= position; a--) {
            L->elem[a + 1] = L->elem[a];
        }
        
        // Logic Step 3: Insert
        // Now that the space is open, we put the new data in.
        L->elem[position] = data;
        
        // Logic Step 4: Update Count
        // We have one more item, so we increase the total count.
        L->count++;
    } else {
        printf("Invalid position or list full.\n");
    }
}

void display(EPtr L){
    int a;
    // Logic: Iterate from 0 up to 'count'.
    // We do NOT go up to MAX because the rest of the array is garbage data.
    for(a = 0; a < L->count; a++){
        printf("%d | ", L->elem[a]);
    }
    printf("\n");
}

void deletePos(EPtr L, int position){
    int a = 0;

    // Logic Step 1: Validation
    // Ensure the position exists (between 0 and count-1).
    if(position >= 0 && position < L->count) {
        
        // Logic Step 2: Shifting to fill the gap
        // We start at the 'position' we want to delete.
        // We pull the item from the right ('a+1') into the current spot ('a').
        // This effectively overwrites the item we wanted to delete.
        for(a = position; a < L->count - 1; a++) {
            L->elem[a] = L->elem[a + 1];
        }
        
        // Logic Step 3: Update Count
        // We have one less item, so we decrease the total count.
        // The last item in the array is now technically a duplicate, but we ignore it because count is lower.
        L->count--;
    } else {
        printf("Invalid position.\n");
    }
}

int locate(EPtr L, int data){
    int a = 0;
    
    // Logic: Linear Search
    // Check every box one by one from start to finish.
    for(a = 0; a < L->count; a++){
        // If the current box matches our data, return the index 'a'.
        if (L->elem[a] == data){
            return a;
        }
    }
    // Logic: If the loop finishes without returning, the data isn't there. Return -1.
    return -1;
}

void insertSorted(EPtr L, int data){
    int a;
    
    // Logic Step 1: Check if full
    if (L->count >= MAX) {
        printf("List is full.\n");
        return;
    }

    // Logic Step 2: Find Spot AND Shift
    // This loop does two jobs at once:
    // 1. It starts at the end of the list.
    // 2. It checks: "Is the number here bigger than the new data?"
    //    YES -> Move that big number to the right to make room (elem[a+1] = elem[a]).
    //    NO  -> We found the correct spot (or reached the start). Stop the loop.
    for(a = L->count - 1; a >= 0 && L->elem[a] > data; a--){
        L->elem[a+1] = L->elem[a]; 
    } 
    
    // Logic Step 3: Insert
    // The loop stopped one step BEFORE the correct spot (because of a--),
    // so we put the data at 'a + 1'.
    L->elem[a+1] = data;
    
    // Logic Step 4: Update Count
    L->count++;
}