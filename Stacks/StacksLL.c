#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int data;
    struct Node *next;
} Node;

// Logic: A Stack Wrapper
// We only need to know where the 'top' is. 
// Everything else hangs off that first pointer.
typedef struct Stack{
    Node *top;
} Stack;

/* --- PROTOTYPES --- */
Stack* initialize();
bool isFull(Stack* s);
bool isEmpty(Stack* s);
void push(Stack* s, int value);
int pop(Stack* s);
int peek(Stack* s);
void display(Stack* s);
void freeStack(Stack* s); 

int main(){
    Stack *S = initialize();
    
    // Logic: LIFO (Last In, First Out)
    push(S, 1); // Stack: 1
    push(S, 2); // Stack: 2 -> 1
    push(S, 5); // Stack: 5 -> 2 -> 1
    push(S, 4); // Stack: 4 -> 5 -> 2 -> 1 (Top is 4)

    // Logic: Remove the Top
    pop(S);     // Removes 4. Top becomes 5.
    
    // Logic: Check the Top without removing
    int value = peek(S);
    printf("Value at the top is: %d\n", value); // Should be 5

    display(S);
    
    // Logic: Clean up dynamic memory
    freeStack(S);
    
    return 0;
}

Stack* initialize(){
    Stack *s = malloc(sizeof(Stack));
    if (s == NULL){
        printf("Memory allocation failed");
        return NULL;
    }
    // Logic: A stack starts empty, so Top points to NULL.
    s->top = NULL;
    return s;
}

bool isFull(Stack* s){
    // Logic: A Linked List is only full if the computer runs out of RAM.
    return false;
}

bool isEmpty(Stack* s){
    // Logic: If Top is NULL, there are no nodes.
    return s->top == NULL;
}

void push(Stack* s, int value){
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL){
        printf("Memory allocation failed");
        return;
    }
    
    // Logic: Insert at HEAD
    // 1. Put data in new node.
    newNode->data = value;
    
    // 2. Make new node point to the OLD Top.
    // (This links the new guy to the rest of the chain below him).
    newNode->next = s->top;
    
    // 3. Update Top to point to the new node.
    s->top = newNode;
}

int pop(Stack* s){
    if (isEmpty(s)){
        printf("Stack is empty");
        return -1;
    }
    
    // Logic: Remove at HEAD
    // 1. Save the current Top node (so we can free it later).
    Node *temp = s->top;
    
    // 2. Save the data (so we can return it).
    int value = temp->data;
    
    // 3. Move Top pointer down to the next node.
    s->top = temp->next;
    
    // 4. Free the old Top.
    free(temp);
    
    return value;
}

int peek(Stack* s){
    if (isEmpty(s)){
        printf("Stack is empty");
        return -1;
    }
    // Logic: Just look at the data in the Top node.
    return s->top->data;
}

void display(Stack* s){
    if (isEmpty(s)){
        printf("Stack is empty");
        return;
    }
    
    Node *temp = s->top;
    
    // Logic: Iterate from Top to Bottom
    while(temp != NULL){
        printf("%d\n", temp->data); // Prints vertical stack style
        temp = temp->next;
    }
}

void freeStack(Stack* s){
    // Logic: Standard clean up
    // Keep popping until nothing is left. This frees every Node.
    while(!isEmpty(s)){
        pop(s);
    }
    // Logic: Finally, free the Stack wrapper itself.
    free(s);
}