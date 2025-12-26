#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct node {
    int key;
    struct node* next;
} Node;

// Logic: An array of Pointers. 
// Each slot 'table[i]' holds the head of a Linked List.
Node* table[SIZE];

int hash(int key) {
    return key % SIZE;
}

void initialize() {
    int i;
    // Logic: Set every list to NULL (empty) to start.
    // If we don't do this, the pointers will point to garbage memory.
    for(i = 0; i < SIZE; i++) {
        table[i] = NULL;
    }
}

void insert(int key) {
    int index = hash(key);
    
    // Logic Step 1: Create the new node
    Node* temp = malloc(sizeof(Node));
    temp->key = key;
    
    // Logic Step 2: Insert at HEAD (Beginning)
    // We insert at the front because it is O(1) fast.
    // We don't need to loop to the end of the list.
    // 1. Make new node point to whatever is currently first.
    temp->next = table[index]; 
    // 2. Update the table to point to our new node.
    table[index] = temp;
}

void delete(int key) {
    int index = hash(key);
    Node* curr = table[index];
    Node* prev = NULL;

    // Logic Step 1: Traverse the List
    // We keep track of 'prev' because to delete 'curr', 
    // we need to stitch 'prev' to 'curr->next'.
    while(curr != NULL && curr->key != key) {
        prev = curr;
        curr = curr->next;
    }

    // Logic Step 2: Check if found
    if(curr != NULL) {
        // Case A: Deleting the FIRST node (Head)
        if(prev == NULL) {
            table[index] = curr->next;
        } 
        // Case B: Deleting a MIDDLE or LAST node
        else {
            prev->next = curr->next;
        }
        
        // Logic Step 3: Free memory
        free(curr);
    }
}

void search(int key) {
    int index = hash(key);
    Node* curr = table[index];

    // Logic: Search ONLY the specific chain at this index.
    // We don't care about the rest of the table.
    while(curr != NULL) {
        if(curr->key == key) {
            printf("Found %d\n", key);
            return;
        }
        curr = curr->next;
    }
    printf("Not Found %d\n", key);
}

void display() {
    int i;
    for(i = 0; i < SIZE; i++) {
        printf("%d: ", i);
        Node* curr = table[i];
        
        // Logic: Print the chain
        while(curr != NULL) {
            printf("%d -> ", curr->key);
            curr = curr->next;
        }
        printf("NULL\n");
    }
}

int main() {
    initialize();

    // [NOTE] Collision Test
    // 10, 20 will go to index 0.
    // 15, 25, 35 will go to index 5.
    insert(10);
    insert(20); // 20 will become the new Head of index 0
    insert(15);
    insert(25);
    insert(35); // 35 will become the new Head of index 5

    display();

    search(15);
    delete(20); // Deleting the Head of index 0

    display();

    return 0;
}