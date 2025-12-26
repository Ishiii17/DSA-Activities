#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int data;
    struct Node *next;
}Node;

typedef struct Queue{
    Node *front; // The Exit (Head of list)
    Node *rear;  // The Entrance (Tail of list)
}Queue;

Queue* initialize();
bool isFull(Queue* q);
bool isEmpty(Queue* q);
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
int front(Queue* q);
void display(Queue* q);
void freeQueue(Queue *q); 

int main(){
    Queue *Q = initialize();
    
    // Logic: People join at the Rear
    enqueue(Q,1); // 1
    enqueue(Q,3); // 1 -> 3
    enqueue(Q,5); // 1 -> 3 -> 5
    enqueue(Q,4); // 1 -> 3 -> 5 -> 4
    
    // Logic: Person at the Front leaves (1 leaves)
    dequeue(Q);   // 3 -> 5 -> 4
    
    // Logic: Check who is now at the Front
    int value = front(Q);
    printf("Value at the front is: %d\n", value); // Should be 3
    
    display(Q);
    freeQueue(Q);
    
    return 0;   
}

Queue* initialize(){
    Queue *q = malloc(sizeof(Queue));
    if(q == NULL){
        printf("Memory allocation failed!");
        return NULL;
    }
    q->front = NULL;
    q->rear = NULL;
    return q;       
}

bool isFull(Queue* q){
    return false;
}

bool isEmpty(Queue* q){
    // Logic: If the front is NULL, nobody is in line.
    return q->front == NULL;
}

void enqueue(Queue* q, int value){
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL){
        printf("Memory allocation failed!");
        return;
    }
    
    newNode->data = value;
    newNode->next = NULL; // Rear node always points to NULL
    
    // Logic: Dealing with the Queue state
    if(isEmpty(q)){
        // If empty, the new guy is both the Front AND the Rear
        q->front = newNode;
        q->rear = newNode;
    } else{
        // Logic Step 1: Link the OLD rear to the NEW node
        q->rear->next = newNode;
        
        // Logic Step 2: Update the 'rear' pointer to the new node
        // (Note: You did this outside the else, which is clever and valid!)
    }
    q->rear = newNode; 
}

int dequeue(Queue* q){
    if(isEmpty(q)){
        printf("Queue is empty!");
        return -1;
    }
    
    // Logic Step 1: Target the Front (Exit)
    Node *temp = q->front;
    int value = q->front->data;
    
    // Logic Step 2: Move Front pointer to the next person
    q->front = temp->next;
    
    // Logic Step 3: Special Case (Queue becomes empty)
    // If we just removed the last person, 'front' became NULL.
    // We must ensure 'rear' is also set to NULL.
    if(q->front == NULL){
        q->rear = NULL;
    }
    
    free(temp);
    return value;
}

int front(Queue* q){
    if(isEmpty(q)){
        printf("Queue is empty!");
        return -1;
    }
    return q->front->data;
}

void display(Queue* q){
    if(isEmpty(q)){
        printf("Queue is empty");
        return;
    }
    
    // Logic: Iterate from Front (Start) to Rear (End)
    Node *temp = q->front;
    while(temp!=NULL){
        printf("%d -> ",temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void freeQueue(Queue *q){
    while(!isEmpty(q)){
        dequeue(q);
    }
    free(q);
}