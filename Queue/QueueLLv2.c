#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int data;
    struct Node *next;
} Node;

typedef struct Queue{
    Node *front; // [NOTE] In your logic, this acts as the TAIL (Entrance)
    Node *rear;  // [NOTE] In your logic, this acts as the HEAD (Exit)
} Queue;

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
    
    // Logic: Adding to the 'front' (Entrance)
    enqueue(Q, 1);
    enqueue(Q, 3);
    enqueue(Q, 5);
    enqueue(Q, 4);
    
    // Logic: Removing from the 'rear' (Exit)
    dequeue(Q);
    
    // Logic: Peeking at the 'rear' (Exit)
    int value = front(Q);
    printf("Value at the exit is: %d\n", value);
    
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
    // Logic: Linked lists only fill up if computer RAM is full.
    return false;
}

bool isEmpty(Queue* q){
    // Logic: If there is no one at the exit (rear), the queue is empty.
    return q->rear == NULL;
}

void enqueue(Queue* q, int value){
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL){
        printf("Memory allocation failed!");
        return;
    }
    
    newNode->data = value;
    newNode->next = NULL;
    
    if(isEmpty(q)){
        // Logic: First node is both the entrance and exit
        q->front = newNode;
        q->rear = newNode;
    } else{
        // Logic Step 1: Link the current entrance (front) to the new node
        q->front->next = newNode;
        // Logic Step 2: Update the 'front' pointer to be the new node
        q->front = newNode;
    }
}

int dequeue(Queue* q){
    if(isEmpty(q)){
        printf("Queue is empty!");
        return -1;
    }
    
    // Logic Step 1: Target the exit (rear)
    Node *temp = q->rear;
    int value = q->rear->data;
    
    // Logic Step 2: Move the exit pointer to the next person in line
    q->rear = temp->next;
    
    // Logic Step 3: Special Case
    // If we removed the last item, 'rear' becomes NULL.
    // We must also set 'front' to NULL so the queue is fully reset.
    if(q->rear == NULL){
        q->front = NULL;
    }
    
    free(temp);
    return value;
}

int front(Queue* q){
    if(isEmpty(q)){
        printf("Queue is empty!");
        return -1;
    }
    // Logic: Return data at the exit (rear)
    return q->rear->data;
}

void display(Queue* q){
    if(isEmpty(q)){
        printf("Queue is empty");
        return;
    }
    
    // Logic: Start from the Exit (rear) and walk towards the Entrance (front)
    Node *temp = q->rear;
    while(temp != NULL){
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void freeQueue(Queue *q){
    // Logic: Reuse dequeue to clear nodes, then free the container
    while(!isEmpty(q)){
        dequeue(q);
    }
    free(q);
}