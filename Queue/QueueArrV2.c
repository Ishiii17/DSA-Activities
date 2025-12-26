#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct{
    int items[MAX];
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
    
    // Logic: rear moves, then data is added
    enqueue(Q, 1); // rear=1, items[1]=1
    enqueue(Q, 3); // rear=2, items[2]=3
    enqueue(Q, 2); // rear=3, items[3]=2
    enqueue(Q, 5); // rear=4, items[4]=5
    
    // Logic: front moves to remove data
    dequeue(Q); // removes items[1], front becomes 2
    dequeue(Q); // removes items[2], front becomes 3

    valFront = front(Q); // should be items[3] (which is 2)
    printf("=== VARIATION 2 (Circular) ====\n");
    printf("The value at the front is %d\n", valFront);
    printf("ITEMS:\n");
    display(Q); // Should print 2 5

    return 0;   
}

Queue* initialize(){
    Queue *q = malloc(sizeof(Queue));
    if(q == NULL){
        printf("Memory allocation failed!");
        exit(1);
    }

    // Logic: In this variation, Front starts 1 step ahead of Rear.
    // This state (front == rear + 1) represents "Empty".
    q->front = 1;
    q->rear = 0;
    
    return q;
}

bool isEmpty(Queue* q){
    // Logic: If Front is exactly 1 step ahead of Rear (wrapping around MAX),
    // it means there is no data between them.
    return (q->front == (q->rear + 1) % MAX);
}

bool isFull(Queue* q){
    // Logic: We sacrifice one slot. 
    // If adding one more item would make Rear bump into Front, we stop.
    // Mathematically: Is Front 2 steps ahead of Rear?
    return (q->front == (q->rear + 2) % MAX);
}

void enqueue(Queue* q, int value){
    if(isFull(q)){
        printf("Queue is full\n");
        return;
    }

    // Logic: Circular Increment
    // Move Rear forward first, THEN insert.
    q->rear = (q->rear + 1) % MAX;
    q->items[q->rear] = value;
}

int dequeue(Queue* q){
    if(isEmpty(q)){
        printf("Queue is empty\n");
        return -1;
    }
    
    // Logic: Retrieve the data at Front
    int value = q->items[q->front];
    
    // Logic: Move Front forward to "delete" the item
    q->front = (q->front + 1) % MAX;
    
    return value;
}

int front(Queue* q){
    if(isEmpty(q)){
        printf("Queue is empty\n");
        return -1;
    }
    return q->items[q->front];
}

void display(Queue* q){
    int a = q->front;
    
    if(isEmpty(q)){
        printf("Queue is empty\n");
        return;
    }
    
    // Logic: Loop until 'a' passes 'rear'.
    // We use (rear + 1) % MAX as the stopping point because in a circular queue,
    // rear might be numerically smaller than front (e.g., rear=1, front=9).
    while(a != (q->rear + 1) % MAX){
        printf("%d ", q->items[a]);
        a = (a + 1) % MAX; 
    }
    printf("\n");
}