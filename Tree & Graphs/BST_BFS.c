#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *LC;
    struct node *RC;
} Node, *BST;

// Logic: A Queue is required for BFS to store "nodes to visit later".
// We use a simple array-based queue here.
typedef struct {
    BST q[100];
    int front;
    int rear;
} Queue;

void initQueue(Queue *q) {
    q->front = 0;
    q->rear = 0;
}

int isEmpty(Queue *q) {
    // Logic: If front chases rear and catches up, the queue is empty.
    return q->front == q->rear;
}

void enqueue(Queue *q, BST n) {
    // Logic: Add node to the end and increment rear index.
    // (Note: In a real app, check for Overflow here i.e., rear < 100)
    q->q[q->rear++] = n;
}

BST dequeue(Queue *q) {
    // Logic: Return the node at the front and increment front index.
    return q->q[q->front++];
}

void bfsTraversal(BST root) {
    if (root == NULL) return;

    Queue q;
    initQueue(&q);

    // Logic Step 1: Prime the pump
    // Start by adding the Root to the queue.
    enqueue(&q, root);

    // Logic Step 2: Loop until Queue is Empty
    // As long as there are nodes waiting to be processed...
    while (!isEmpty(&q)) {
        
        // Logic Step 3: Dequeue and Visit
        // Remove the guy at the front of the line and print him.
        BST curr = dequeue(&q);
        printf("%d ", curr->data);

        // Logic Step 4: Enqueue Children
        // If the current node has children, add them to the BACK of the line.
        // This ensures we finish the current level before touching the next level.
        if (curr->LC != NULL)
            enqueue(&q, curr->LC);

        if (curr->RC != NULL)
            enqueue(&q, curr->RC);
    }
}

int main() {
    // Logic: Manual Tree Construction
    //      10
    //     /  \
    //    5    15
    BST root = malloc(sizeof(Node));
    root->data = 10;
    root->LC = malloc(sizeof(Node));
    root->LC->data = 5;
    root->LC->LC = NULL;
    root->LC->RC = NULL;
    root->RC = malloc(sizeof(Node));
    root->RC->data = 15;
    root->RC->LC = NULL;
    root->RC->RC = NULL;

    printf("BFS (Level Order): ");
    bfsTraversal(root); // Output: 10 5 15
    printf("\n");
    
    return 0;
}