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

    // Logic: Pushing fills from the back (index 9, then 8, then 7...)
    push(S, 1); // Stored at index 9
    push(S, 3); // Stored at index 8
    push(S, 2); // Stored at index 7
    push(S, 5); // Stored at index 6

    printf("=== VARIATION 2 (Growing Down) ====\n");
    
    // Logic: Pop removes from index 6. Top moves to 7.
    popS = pop(S);
    printf("Popped value: %d\n", popS);

    peekS = peek(S);
    topS = top(S);

    printf("Value of (peek): %d\n", peekS);
    printf("Top index: %d\n", topS); // Should be 7

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
    // Logic: Top starts "outside" the array on the right side.
    // Index 10 is not valid, but that's okay because we decrement before writing.
    s->top = MAX;   
    return s;
}

bool isFull(Stack* s) {
    // Logic: If Top reaches 0, we have filled indices 0 to 9. No space left.
    return s->top == 0;
}

bool isEmpty(Stack* s) {
    // Logic: If Top is back at MAX (10), nothing is valid in the array.
    return s->top == MAX;
}

void push(Stack* s, int value) {
    if (isFull(s)) {
        printf("Error: Stack is full! Cannot push %d\n", value);
        return;
    }
    // Logic Step 1: Move Top "Left" (Decrement) to the next empty slot.
    s->top--;  
    // Logic Step 2: Insert Data
    s->items[s->top] = value;
}

int pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return -1;
    }
    
    // Logic Step 1: Grab the data
    int value = s->items[s->top];
    
    // Logic Step 2: Move Top "Right" (Increment) to discard the item.
    s->top++;  
    
    return value;
}

int peek(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return -1;
    }
    // Logic: Check data at current Top index.
    return s->items[s->top];
}

int top(Stack* s) {
    return s->top;  
}

void display(Stack* s) {
    int a;
    
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return;
    }
    // Logic: Loop from the current Top (e.g., 6) up to the bottom of the stack (9).
    for (a = s->top; a < MAX; a++) {
        printf("%d\n", s->items[a]);
    }
}