#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 

// --- STRUCT DEFINITIONS ---

typedef struct node {
    char name[50];
    char role[50];  
    int priority;   
    struct node* next;
} Node;

typedef struct {
    Node* front; // Logic: We only need to track the front because insertion happens in the middle.
} PriorityQueue;

// --- PROTOTYPES ---
PriorityQueue* initialize();
void enqueue(PriorityQueue* pq, char* name, char* role);
char* dequeue(PriorityQueue* pq);
bool isGuestInQueue(PriorityQueue* pq, char* targetName);
void findGuestsLike(PriorityQueue* pq, char* roleFragment);
void display(PriorityQueue* pq);

int main() {
    printf("Initializing Wedding Guest Queue...\n");
    PriorityQueue* weddingQ = initialize();

    printf("\n--- Guests Arriving ---\n");
    // Logic: Regular Guest (Priority 1)
    enqueue(weddingQ, "John Smith", "Regular Guest");
    // Logic: Family (Priority 50) -> Should cut in front of John
    enqueue(weddingQ, "Maria Clara", "Mother of Family");
    // Logic: VIP (Priority 20) -> Should go between Maria and John
    enqueue(weddingQ, "Alice Guo", "VIP Sponsor");
    // Logic: Groom (Priority 100) -> Should go to the very front
    enqueue(weddingQ, "Jose Rizal", "Groom"); 
    
    display(weddingQ);

    printf("\n--- Searching for 'Alice Guo' ---\n");
    if (isGuestInQueue(weddingQ, "Alice Guo")) {
        printf("Yes, she is on the list.\n");
    } else {
        printf("Not found.\n");
    }

    printf("\n--- Finding all 'Family' members ---\n");
    findGuestsLike(weddingQ, "Family");

    printf("\n--- Seating Guests (High Priority First) ---\n");
    
    // Logic: We must free the string returned by dequeue because it was malloc'd
    char* seatedGuest = dequeue(weddingQ);
    if (seatedGuest) {
        printf("Seated: %s\n", seatedGuest);
        free(seatedGuest); 
    }

    seatedGuest = dequeue(weddingQ);
    if (seatedGuest) {
        printf("Seated: %s\n", seatedGuest);
        free(seatedGuest);
    }

    display(weddingQ);

    return 0;
}

// --- IMPLEMENTATION ---

PriorityQueue* initialize() {
    PriorityQueue *pq = malloc(sizeof(PriorityQueue));
    if(pq == NULL){
        printf("Memory Allocation Failed");
        return NULL;
    }
    pq->front = NULL;
    return pq; 
}

void enqueue(PriorityQueue* pq, char* name, char* role) {
    Node *newNode = malloc(sizeof(Node));
    strcpy(newNode->name, name);
    strcpy(newNode->role, role);
    newNode->next = NULL;

    // Logic Step 1: Assign Priority Score
    // We convert text roles into comparable integers.
    if(strcmp(newNode->role, "Bride") == 0 || strcmp(newNode->role, "Groom") == 0){
        newNode->priority = 100;
    }
    else if(strstr(newNode->role, "Family") != NULL){
        newNode->priority = 50;
    }
    else if(strstr(newNode->role, "VIP") != NULL){
        newNode->priority = 20;
    } else {
        newNode->priority = 1;
    }
   
    // Logic Step 2: Insertion
    // Case A: The list is empty OR the new person is MORE important than the current Head.
    // They become the new Front.
    if(pq->front == NULL || newNode->priority > pq->front->priority){
        newNode->next = pq->front;
        pq->front = newNode;
    } 
    // Case B: Traverse to find the correct spot.
    else {
        Node *temp = pq->front;
        
        // Loop Condition: 
        // 1. We aren't at the end (temp->next != NULL)
        // 2. The NEXT person has HIGHER or EQUAL priority (temp->next->priority >= newNode->priority)
        // Logic: We skip people who are more important than us. We stop right before someone LESS important.
        while(temp->next != NULL && temp->next->priority >= newNode->priority){
            temp = temp->next;
        }
        
        // Insert AFTER 'temp'
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

char* dequeue(PriorityQueue* pq) {
    if (pq == NULL || pq->front == NULL) return NULL;
    
    // Logic Step 1: Isolate the Head
    Node *oldFront = pq->front;
    pq->front = oldFront->next;
    
    // Logic Step 2: Save the Data
    // We cannot return 'oldFront->name' directly because we are about to free oldFront.
    // We must malloc a new string to pass back to main().
    char *saved = malloc(strlen(oldFront->name) + 1);
    strcpy(saved, oldFront->name);

    // Logic Step 3: Free the Node
    free(oldFront);
    return saved; 
}

bool isGuestInQueue(PriorityQueue* pq, char* targetName) {
    Node *trav = pq->front;
    while(trav != NULL){
        // Logic: Exact match required
        if(strcmp(trav->name, targetName) == 0){
            return true;
        }
        trav = trav->next;
    }
    return false; 
}

void findGuestsLike(PriorityQueue* pq, char* roleFragment) {
    Node *trav = pq->front;
    while(trav != NULL){
        // Logic: Partial match allowed (e.g., "Family" matches "Mother of Family")
        if(strstr(trav->role, roleFragment) != NULL){
            printf("Found: %s (%s)\n", trav->name, trav->role);
        }
        trav = trav->next;
    }
}

void display(PriorityQueue* pq) {
    Node *trav = pq->front;
    printf("\n--- Current Queue Status ---\n");
    while(trav != NULL){
        printf("[%d] %s (%s)\n", trav->priority, trav->name, trav->role);
        trav = trav->next;
    }
    printf("----------------------------\n");
}