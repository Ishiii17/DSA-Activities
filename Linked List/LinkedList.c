#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *next;
} Node;

typedef struct{
    Node *head;
    int count; // Logic: Keeps track of size so we don't have to count manually
} List; 

/* --- PROTOTYPES --- */
List* initialize(); 
void empty(List *list);
void insertFirst(List *list, int data); 
void insertLast(List *list, int data); 
void insertPos(List *list, int data, int index);  
void deleteStart(List *list);  
void deleteLast(List *list); 
void deletePos(List *list, int index); 
int retrieve(List *list, int index); 
int locate(List *list, int data); 
void display(List *list); 

int main(){
    List *L = initialize();
    int ret, loc;
    
    // [NOTE] Testing Insertions
    insertFirst(L, 5);
    insertFirst(L, 6);
    insertFirst(L, 2); // List is now: 2 -> 6 -> 5 -> NULL
    
    // [NOTE] Testing Retrieve
    ret = retrieve(L, 0);
    printf("Data in index 0 is %d\n", ret); // Should be 2
    
    // [NOTE] Testing Locate
    loc = locate(L, 6);
    printf("Data 6 found at index %d\n", loc); // Should be 1
    
    display(L);
    
    // [NOTE] Always clean up memory
    empty(L);
    free(L); // Free the wrapper struct itself
    
    return 0;
}

List* initialize(){
    // Logic: allocate space for the 'Wrapper' on the Heap
    List *newList = malloc(sizeof(List));
    
    if (newList == NULL){
        printf("Memory allocation failed");
        return NULL;
    } 
    
    newList->head = NULL;
    newList->count = 0;
    return newList;
}

void insertFirst(List *list, int data){
    Node *newNode = malloc(sizeof(Node));

    // Logic: "Push" logic
    // 1. New node points to current Head
    // 2. Head moves to New Node
    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;
    list->count++;
}

void insertLast(List *list, int data){
    Node *newNode = malloc(sizeof(Node));
    Node *current;

    newNode->data = data;
    newNode->next = NULL; // It will be last, so next is NULL
    
    if (list->head == NULL){
        // Logic: If empty, it's the same as insertFirst
        list->head = newNode;
    } else {
        // Logic: Traverse to the very end
        current = list->head;    
        while(current->next != NULL){
            current = current->next;
        }
        // Logic: Link the old last node to the new node
        current->next = newNode;
    }
    list->count++;
}

void insertPos(List *list, int data, int index){
    int pos;
    
    if (index < 0 || index > list->count){
        printf("Index must be valid\n");
        return;
    }
    
    // Logic: Delegate to specific functions for edge cases
    if (index == 0){
        insertFirst(list, data);
        return;
    }
    if(index == list->count){
        insertLast(list, data);
        return;
    }
    
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    
    Node *current = list->head;
    
    // Logic: Stop at 'index - 1' (The node BEFORE the target spot)
    for(pos = 0; pos < index - 1; pos++){
        current = current->next;
    }

    // Logic: Wiring
    // 1. New Node points to the node AFTER current
    // 2. Current (the one before) points to New Node
    newNode->next = current->next;
    current->next = newNode;
    list->count++;
}

void deleteStart(List *list){
    if (list->head == NULL) return; 

    Node *current = list->head;
    
    // Logic: Move head forward one step, then free the old head
    list->head = current->next;
    free(current);
    list->count--;
}

void deleteLast(List *list){
    int pos;
    if (list->head == NULL) return;

    // Logic: Special case for single item
    if (list->count == 1){
        free(list->head);
        list->head = NULL;
        list->count--;
        return;
    }

    Node *current = list->head;
    
    // Logic: Stop at 'count - 2' (The node BEFORE the last node)
    // We need to stop here so we can set current->next to NULL.
    for(pos = 0; pos < list->count - 2; pos++){
        current = current->next;
    }
    
    free(current->next); // Free the last node
    current->next = NULL; // Make this node the new last node
    list->count--;
}

void deletePos(List *list, int index){
    int pos;
    if (index < 0 || index >= list->count) {
          printf("Invalid index\n");
        return;
    }

    if(index == 0){
        deleteStart(list);
        return;
    }
    
    Node *current = list->head;
    
    // Logic: Traverse to 'index - 1'
    for(pos = 0; pos < index - 1; pos++){
        current = current->next;
    }
    
    // Logic: Bypass the target node
    Node *temp = current->next; // Save target
    current->next = temp->next; // Link previous to next
    free(temp); // Delete target
    list->count--;
}

int retrieve(List *list, int index){
    int pos;
      if (list->head == NULL) {
        printf("List is empty\n");
        return -1;  
    }
    if (index < 0 || index >= list->count) {
        printf("Invalid index\n");
        return -1;
    }
    Node *current = list->head;
    
    // Logic: Walk to the specific index
    for(pos = 0; pos < index; pos++){
        current = current->next;
    }
    return current->data;
}    

int locate(List *list, int data){
    if (list->head == NULL) {
        printf("List is empty\n");
        return -1;  
    }
    
    Node *current = list->head;
    int index = 0;
    
    // Logic: Walk and compare
    for (; current != NULL; current = current->next, index++) {
        if (current->data == data) {
            return index;
        }
    }
    return -1;
}

void empty(List *list){
    Node *current = list->head;
    Node *temp;
    
    // Logic: Walk through list, freeing nodes one by one
    while(current != NULL){
        temp = current;
        current = current->next; // Move safely before freeing
        free(temp);
    }
    list->head = NULL;
    list->count = 0;
}

void display(List *list){
    Node *current = list->head;
    
    if(current == NULL){
        printf("List is empty\n");
        return;
    }
    
    while(current != NULL){
        printf("[%d] -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}