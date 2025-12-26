#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// [NOTE] I increased MAX to 10 so you have more room to test.
#define MAX 10 
#define NIL -1

typedef struct {
    int elem; // The data
    int next; // The "pointer" (actually the index of the next node)
} Cell, HeapSpace[MAX];

typedef struct {
    HeapSpace H; // The "RAM" (array of nodes)
    int avail;   // The "Head" of the empty node list
} VHeap;

typedef int List; // A List is just the index of the first node

// Prototypes
void initialize(VHeap *V);
int allocSpace(VHeap* V);
void deallocSpace(VHeap* V, int index);
void insertFirst(int* L, VHeap* V, int elem);
void insertLast(int* L, VHeap* V, int elem);
void insertSorted(int* L, VHeap* V, int elem);
void delete(int* L, VHeap* V, int elem);
void deleteAllOccurrence(int* L, VHeap* V, int elem);
void display(int L, VHeap V);

int main() {
    VHeap V;
    List L = NIL; // Start with an empty list (-1)

    initialize(&V);

    insertFirst(&L, &V, 10);
    insertLast(&L, &V, 30);
    insertSorted(&L, &V, 20); // Should go between 10 and 30
    insertSorted(&L, &V, 20); // Duplicate test

    display(L, V);

    delete(&L, &V, 20); // Deletes the first 20
    display(L, V);

    deleteAllOccurrence(&L, &V, 20); // Deletes remaining 20s
    display(L, V);

    return 0;
}

void initialize(VHeap *V){
    int i;
    // Logic: Thread the array so every node points to the next one.
    // 0 points to 1, 1 points to 2, etc. This creates our "Available List".
    V->avail = 0; 
    for(i = 0; i < MAX - 1; i++){
        V->H[i].next = i + 1;
    }
    // The last slot points to NIL because it's the end of the available space.
    V->H[MAX - 1].next = NIL;
}

int allocSpace(VHeap* V){
    // Logic: "Pop" a node from the Avail list.
    int idx = V->avail;
    
    if(idx != NIL){
        // Move the head of Avail to the next free node.
        V->avail = V->H[idx].next;
    }
    return idx; // Return the index of the reserved node
}

void deallocSpace(VHeap* V, int index){
    // Logic: "Push" the node back to the FRONT of the Avail list.
    // This recycles the node so it can be used again.
    if (index != NIL && index < MAX) {
        V->H[index].next = V->avail;
        V->avail = index;
    }
}

void insertFirst(int* L, VHeap* V, int elem){
    // Logic: Get a free node first.
    int idx = allocSpace(V);
    
    if(idx != NIL){
        V->H[idx].elem = elem;
        
        // Link new node to the current head of List.
        V->H[idx].next = *L;
        
        // Update the Head pointer to point to this new node.
        *L = idx;
    }
}

void insertLast(int* L, VHeap* V, int elem){
    int idx = allocSpace(V);
    
    if(idx != NIL){
        V->H[idx].elem = elem;
        V->H[idx].next = NIL; // It will be the last, so next is NIL.

        // Logic: Special case for empty list
        if(*L == NIL){
            *L = idx;
        } else {
            // Logic: Traverse to find the last node
            int trav = *L;
            while(V->H[trav].next != NIL){
                trav = V->H[trav].next;
            }
            // Link the old last node to our new node
            V->H[trav].next = idx;
        }
    }
}

void insertSorted(int* L, VHeap* V, int elem){
    // Logic: Pointer-to-Pointer Traversal
    // 'trav' holds the ADDRESS of the link we need to change.
    // It automatically handles the "insert at head" vs "insert middle" logic.
    int *trav = L;
    
    // Stop if we hit end (NIL) OR if current node is bigger than new data.
    while(*trav != NIL && V->H[*trav].elem < elem){
        trav = &V->H[*trav].next; // Move the pointer to the 'next' field
    }

    int idx = allocSpace(V);
    if(idx != NIL){
        V->H[idx].elem = elem;
        
        // Logic: Insert the node at the specific link 'trav' is pointing to.
        V->H[idx].next = *trav;
        *trav = idx;
    }
}

void delete(int* L, VHeap* V, int elem){
    // Logic: Pointer-to-Pointer Traversal
    int *trav = L;
    
    // Find the node pointing to our target element
    while(*trav != NIL && V->H[*trav].elem != elem){
        trav = &V->H[*trav].next;
    }

    // Logic: If found (*trav is not NIL)
    if(*trav != NIL){
        int temp = *trav; // Store index to delete
        
        // Make the link skip over the deleted node
        *trav = V->H[temp].next;
        
        // Recycle the node
        deallocSpace(V, temp);
    }
}

void deleteAllOccurrence(int* L, VHeap* V, int elem){
    // Logic: Similar to delete, but we keep looping.
    int *trav = L;
    
    while(*trav != NIL){
        if(V->H[*trav].elem == elem){
            int temp = *trav;
            
            // Skip the node
            *trav = V->H[temp].next;
            
            // Recycle
            deallocSpace(V, temp);
            
            // Note: We do NOT move 'trav' here because *trav now points to a NEW node 
            // (the one after the deleted one) which we haven't checked yet.
        } else {
            // Only advance if we didn't delete anything
            trav = &V->H[*trav].next;
        }
    }
}

void display(int L, VHeap V){
    int trav = L;
    printf("List: ");
    while(trav != NIL){
        printf("%d -> ", V.H[trav].elem);
        trav = V.H[trav].next;
    }
    printf("NIL\n");
}