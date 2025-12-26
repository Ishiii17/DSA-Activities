#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    int items[MAX];
    int top;
} Stack;

/* --- PROTOTYPES --- */
Stack* initialize();
bool isFull(Stack* s);
bool isEmpty(Stack* s);
void push(Stack* s, int value);
int pop(Stack* s);
int peek(Stack* s);
int top(Stack *s);
void display(Stack* s);

int main() {
    int topS, peekS, popS;

    Stack *S = initialize();

    push(S, 1);
    push(S, 3);
    push(S, 2);
    push(S, 5);

    printf("=== VARIATION 1 (Static Array) ====\n");
    
    // Logic: Remove the top item (5)
    popS = pop(S);
    printf("Popped value: %d\n", popS);

    // Logic: Look at the new top item (2)
    peekS = peek(S);
    
    // Logic: Check the current index of the top marker (should be index 2)
    topS = top(S);

    printf("Value of (peek): %d\n", peekS);
    printf("Index of (top): %d\n", topS);

    printf("\nITEMS in stack:\n");
    display(S);

    free(S);
    return 0;
}

Stack* initialize() {
    Stack *s = malloc(sizeof(Stack));
    if (s == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    // Logic: Set Top to -1.
    // This indicates the stack is empty because index 0 is the first valid slot.
    s->top = -1;
    return s;
}

bool isFull(Stack* s) {
    // Logic: If Top reached the last index (MAX - 1), there is no room left.
    return s->top == MAX - 1;
}

bool isEmpty(Stack* s) {
    // Logic: If Top is -1, no items have been pushed yet.
    return s->top == -1;
}

void push(Stack* s, int value) {
    if (isFull(s)) {
        printf("Error: Stack is full! Cannot push %d\n", value);
        return;
    }
    // Logic Step 1: Increment the Top marker to point to the next empty slot.
    s->top++; 
    // Logic Step 2: Place the value into that slot.
    s->items[s->top] = value;
}

int pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return -1;
    }
    
    // Logic Step 1: Save the value at the current Top.
    int value = s->items[s->top];
    
    // Logic Step 2: Decrement Top.
    // We don't need to delete the data; we just move the marker down.
    // Any future push will simply overwrite the old value.
    s->top--;
    
    return value;
}

int peek(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return -1;
    }
    // Logic: Return the value at Top without moving the marker.
    return s->items[s->top];  
}

int top(Stack* s) {
    // Logic: Return the actual array index (e.g., 0, 1, 2) of the Top marker.
    return s->top;  
}

void display(Stack* s) {
    int a;
    
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return;
    }
    // Logic: Iterate backwards from Top down to 0.
    // This visualizes the stack correctly (Last In, First Out).
    for (a = s->top; a >= 0; a--) {
        printf("%d\n", s->items[a]);
    }
}