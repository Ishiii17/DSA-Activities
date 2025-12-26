#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// -----------------------------
// Struct Declarations
// -----------------------------
typedef struct apple {
    char name[20];
    char color[10];
    int hardness;   // 1-10
    int size_cm;
    bool ripe;
} Apple;

typedef struct node {
    Apple *app;            
    struct node *LC;      
    struct node *RC;      
} Node, *BST;

typedef struct box {
    Apple apples[50]; 
    int count;
    int capacity;
} Box;

// -----------------------------
// Function Prototypes
// -----------------------------
BST createNode(Apple *a);
BST insertBST(BST root, Apple *a);
BST deleteNode(BST root, const char *key);
BST makeAppleTree(Apple apples[], int n);   
void inorderTraversal(BST root);
void preorderTraversal(BST root);
BST harvestRecursive(BST root, Box *box);   
BST harvestRotten(BST root, Box *box);      
void initBox(Box *box, int capacity);

// -----------------------------
// Main Function
// -----------------------------
int main() {
    Box box;
    initBox(&box, 10);

    Apple apples[10] = {        
        {"Fuji", "red", 7, 8, true},
        {"Gala", "green", 6, 7, true},
        {"Honeycrisp", "red", 5, 6, false},
        {"Golden", "yellow", 8, 9, true},
        {"RedDel", "red", 6, 7, true},
        {"Granny", "green", 7, 8, true},
        {"Jonathan", "red", 8, 9, true},
        {"McIntosh", "red", 4, 7, true},
        {"PinkLady", "pink", 6, 7, true},
        {"Empire", "red", 7, 8, false}
    };

    BST tree = makeAppleTree(apples, 10);

    printf("In-order traversal (Alphabetical):\n");
    inorderTraversal(tree); // 

    printf("\n\nPre-order traversal:\n");
    preorderTraversal(tree);

    // Harvest ripe apples
    printf("\n\n--- Harvesting Ripe Apples ---\n");
    tree = harvestRecursive(tree, &box); // Update tree root!

    // Harvest rotten apples
    printf("\n\n--- Harvesting Rotten Apples ---\n");
    tree = harvestRotten(tree, &box); // Update tree root!

    printf("\n\nRemaining Apples in Tree:\n");
    inorderTraversal(tree);

    return 0;
}

BST makeAppleTree(Apple apples[], int n){   
    BST tree = NULL;
    int a;
    for(a=0; a<n; a++){
        tree = insertBST(tree, &apples[a]);
    }
    return tree;
}

BST createNode(Apple *a){
    BST root = malloc(sizeof(Node));
    if(root == NULL) return NULL;
    
    // Deep copy the Apple data
    root->app = malloc(sizeof(Apple));
    if(root->app == NULL) { free(root); return NULL; }

    strcpy(root->app->name, a->name);
    strcpy(root->app->color, a->color);
    root->app->hardness = a->hardness;
    root->app->size_cm = a->size_cm;
    root->app->ripe = a->ripe;

    root->LC = NULL;
    root->RC = NULL;
    
    return root;
}

BST insertBST(BST root, Apple *a){
    if(root == NULL){
        return createNode(a);
    }
    
    // [FIX] Sort ONLY by name to match deleteNode logic
    if(strcmp(a->name, root->app->name) < 0){
        root->LC = insertBST(root->LC, a); 
    } else if(strcmp(a->name, root->app->name) > 0){
        root->RC = insertBST(root->RC, a); 
    } else {
        printf("Apple %s already exists\n", a->name);
    }
    return root;
}

BST deleteNode(BST root, const char *key) { 
    if (root == NULL) return NULL;

    // Navigate to find the node
    if (strcmp(key, root->app->name) < 0) {
        root->LC = deleteNode(root->LC, key);
    } else if (strcmp(key, root->app->name) > 0) {
        root->RC = deleteNode(root->RC, key);
    } else {
        // Node found!
        // Case 1: Leaf Node or One Child
        if (root->LC == NULL) {
            BST temp = root->RC;
            free(root->app); // Free the apple struct
            free(root);      // Free the node
            return temp;
        } else if (root->RC == NULL) {
            BST temp = root->LC;
            free(root->app);
            free(root);
            return temp;
        } 
        
        // Case 2: Two Children (Successor Swap)
        // Find inorder successor (smallest in the right subtree)
        BST succ = root->RC;
        while (succ->LC != NULL) succ = succ->LC;

        // Copy data from successor to current node
        strcpy(root->app->name, succ->app->name);
        strcpy(root->app->color, succ->app->color);
        root->app->hardness = succ->app->hardness;
        root->app->size_cm = succ->app->size_cm;
        root->app->ripe = succ->app->ripe;

        // Delete the successor node from the right subtree
        // [NOTE] This works now because the tree is sorted by name!
        root->RC = deleteNode(root->RC, succ->app->name); 
    }
    return root;
}

void inorderTraversal(BST root){
    Node *stack[100];
    int top = -1;
    Node *curr = root;
    
    while(curr != NULL || top != -1){
        while(curr != NULL){
            stack[++top] = curr;
            curr = curr->LC;
        }
        curr = stack[top--];
        printf("%s | %s | %dcm | %s\n", curr->app->name,
                            curr->app->color, curr->app->size_cm,
                            curr->app->ripe ? "Ripe" : "Not Ripe");
        curr = curr->RC;
    }
}

void preorderTraversal(BST root){
    if(root == NULL) return;
    
    Node *stack[100];
    int top = -1;
    stack[++top] = root;
    
    while(top != -1){
        Node *curr = stack[top--];
        printf("%s\n", curr->app->name);
        
        if(curr->RC != NULL) stack[++top] = curr->RC;
        if(curr->LC != NULL) stack[++top] = curr->LC;
    }
}
        
BST harvestRecursive(BST root, Box *box){   
    if(root == NULL) return NULL;
        
    // 1. Clean the Left Subtree first
    root->LC = harvestRecursive(root->LC, box);
    
    // 2. Check the current Root
    Apple *app = root->app;
    bool criteria = false;
    
    if(strcmp(app->color, "red") == 0 && app->hardness > 6
     && app->size_cm > 7 && app->ripe){
        criteria = true;
    }
    
    if(criteria){
        if(box->count < box->capacity){
            box->apples[box->count] = *app; // Copy struct
            printf("Harvested: %s\n", app->name);
            box->count++;
        }
        // Delete current node and get the new root (could be a child or successor)
        root = deleteNode(root, app->name);
        
        // Recursively check the NEW root (in case it also matches criteria)
        return harvestRecursive(root, box);
    }
    
    // 3. Clean the Right Subtree
    root->RC = harvestRecursive(root->RC, box);
    return root;
}

BST harvestRotten(BST root, Box *box){  
    if(root == NULL) return NULL;
    
    root->LC = harvestRotten(root->LC, box);
    Apple *app = root->app;
    
    if(!app->ripe){ // Not ripe (assuming 'rotten' logic implies !ripe in your data set)
        if(box->count < box->capacity){
            box->apples[box->count] = *app;
            printf("Removed Rotten/Unripe: %s\n", app->name);
            box->count++;
        }
        root = deleteNode(root, app->name);
        return harvestRotten(root, box);
    }
    
    root->RC = harvestRotten(root->RC, box);
    return root;
}

void initBox(Box *box, int capacity){
    box->count = 0;
    box->capacity = capacity;
}