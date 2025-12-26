#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// [NOTE] STRUCT DEFINITION
// A Tree Node has data and two pointers: Left Child (LC) and Right Child (RC).
typedef struct node{
    int data;
    struct node* LC;
    struct node* RC;
} Node, *BST;

/* --- PROTOTYPES --- */
void insert(BST* B, int value);
void inorder(BST B);
void preorder(BST B);
void postorder(BST B);
BST deleteNode(BST B, int value);

int main(){
    BST B = NULL; // Initialize empty tree

    // [NOTE] LOGIC: Building the Tree
    // 50 is Root.
    // 30 < 50 (Left), 70 > 50 (Right)
    // 20 < 30 (Left of Left), 40 > 30 (Right of Left)
    insert(&B, 50);
    insert(&B, 30);
    insert(&B, 70);
    insert(&B, 20);
    insert(&B, 40);
    insert(&B, 60);
    insert(&B, 80);

    // Logic: Inorder should print sorted: 20 30 40 50 60 70 80
    printf("Inorder: ");
    inorder(B);
    printf("\n");

    // Logic: Preorder (Root first): 50 30 20 40 70 60 80
    printf("Preorder: ");
    preorder(B);
    printf("\n");

    // Logic: Postorder (Root last): 20 40 30 60 80 70 50
    printf("Postorder: ");
    postorder(B);
    printf("\n");

    // Logic: Deleting Root (50).
    // The successor (smallest in Right Subtree) is 60.
    // 60 should replace 50.
    printf("Deleting 50...\n");
    B = deleteNode(B, 50);
    
    printf("Inorder after delete: ");
    inorder(B);
    printf("\n");

    return 0;
}

void insert(BST* B, int value){
    // Logic: Base Case - Found an empty spot
    if(*B == NULL){
        *B = malloc(sizeof(Node));
        (*B)->data = value;
        (*B)->LC = NULL;
        (*B)->RC = NULL;
        return;
    }

    // Logic: Recursive Step
    // If smaller, go Left. If bigger, go Right.
    if(value < (*B)->data){
        insert(&(*B)->LC, value);
    } else if(value > (*B)->data){
        insert(&(*B)->RC, value);
    }
    // Note: If value == data, we do nothing (No duplicates allowed)
}

void inorder(BST B){
    if(B != NULL){
        inorder(B->LC);        // 1. Visit Left
        printf("%d ", B->data); // 2. Visit Root
        inorder(B->RC);        // 3. Visit Right
    }
}

void preorder(BST B){
    if(B != NULL){
        printf("%d ", B->data); // 1. Visit Root
        preorder(B->LC);        // 2. Visit Left
        preorder(B->RC);        // 3. Visit Right
    }
}

void postorder(BST B){
    if(B != NULL){
        postorder(B->LC);       // 1. Visit Left
        postorder(B->RC);       // 2. Visit Right
        printf("%d ", B->data); // 3. Visit Root
    }
}

BST deleteNode(BST B, int value){
    // Logic: Base Case - Tree is empty or Item not found
    if(B == NULL){
        return NULL;
    }

    // Logic: SEARCH for the node
    if(value < B->data){
        B->LC = deleteNode(B->LC, value);
    } else if(value > B->data){
        B->RC = deleteNode(B->RC, value);
    } else {
        // Logic: NODE FOUND. Now handle deletion cases.

        // Case 1 & 2: Node has 0 or 1 child
        if(B->LC == NULL){
            BST temp = B->RC; // Save the Right child (could be NULL)
            free(B);          // Delete current node
            return temp;      // Return Right child to parent
        } else if(B->RC == NULL){
            BST temp = B->LC; // Save the Left child
            free(B);
            return temp;      // Return Left child to parent
        }

        // Case 3: Node has 2 children
        // Strategy: Find Inorder Successor (Smallest in Right Subtree)
        BST succ = B->RC;
        while(succ->LC != NULL){
            succ = succ->LC; // Keep going left
        }

        // Copy Successor's data to this node
        B->data = succ->data;
        
        // Delete the Successor (which is now a duplicate) from the Right Subtree
        B->RC = deleteNode(B->RC, succ->data);
    }
    return B;
}