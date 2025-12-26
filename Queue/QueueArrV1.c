#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct{
    int items[MAX];
    int count; // Logic: This makes life much easier!
} List;

typedef struct{
    List list;
    int front;
    int rear;
} Queue;

Queue* initialize();
bool isFull(Queue* q);
bool isEmpty(Queue* q);
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
int front(Queue* q);
void display(Queue* q);

int main(){
    int valFront;
    Queue *Q = initialize();
    
    // Logic: Filling the queue
    enqueue(Q, 1);
    enqueue(Q, 2);
    enqueue(Q, 3);
    enqueue(Q, 4);
    
    // Logic: Removing items
    dequeue(Q);
    dequeue(Q);

    valFront = front(Q);
    printf("=== VARIATION 1 (Counter Based) ====\n");
    printf("The value at the front is %d\n", valFront);
    printf("ITEMS:\n");
    display(Q);

    return 0;   
}

Queue* initialize(){
    Queue *q = malloc(sizeof(Queue));
    if(q == NULL){
        printf("Memory allocation failed!");
        exit(1);
    }
    q->list.count = 0;
    
    // Logic: -1 indicates the pointers are currently "offline" or invalid
    q->front = -1;
    q->rear = -1;
    
    return q;
}

bool isFull(Queue* q){
    // Logic: Simple check thanks to the counter
    return q->list.count == MAX;
}

bool isEmpty(Queue* q){
    // Logic: Simple check thanks to the counter
    return q->list.count == 0;
}

void enqueue(Queue* q, int value){
    if(isFull(q)){
        printf("Queue is full\n");
        return;
    }

    // Logic: Special Case for First Element
    // If the queue was empty, we need to "wake up" the pointers from -1 to 0.
    if (isEmpty(q)){
        q->front = 0;
        q->rear = 0;
    } else {
        // Logic: Circular Increment
        // If rear is at index 9 (MAX-1), (9+1)%10 becomes 0. It wraps around!
        q->rear = (q->rear + 1) % MAX;
    }
    
    q->list.items[q->rear] = value;
    q->list.count++;
}

int dequeue(Queue* q){
    if(isEmpty(q)){
        printf("Queue is empty\n");
        return -1;
    }
    
    int value = q->list.items[q->front];
    
    // Logic: Special Case for Last Element
    // If we are removing the ONLY item left (count is 1),
    // we must reset the queue back to its initialized state (-1).
    if (q->list.count == 1){
        q->front = -1;
        q->rear = -1;
    } else {
        // Logic: Circular Increment
        // Move front forward. If front was 9, it wraps to 0.
        q->front = (q->front + 1) % MAX;
    }
    
    q->list.count--;
    return value;
}

int front(Queue* q){
    if(isEmpty(q)){
        printf("Queue is empty\n");
        return -1;
    }
    return q->list.items[q->front];
}

void display(Queue* q){
    int a, idx = 0;
    
    if(isEmpty(q)){
        printf("Queue is empty\n");
        return;
    }
    
    // Logic: Displaying a Circular Queue
    // We cannot just loop from 0 to count. The data might start at index 8 and wrap to index 1.
    // Formula: (Start Index + Offset) % Size
    for(a = 0; a < q->list.count; a++){
        idx = (q->front + a) % MAX; // Calculate the true array index
        printf("%d ", q->list.items[idx]);
    }
    printf("\n");
}