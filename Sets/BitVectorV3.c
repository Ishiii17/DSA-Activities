#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ARRAY_SIZE 8

// [NOTE] TYPEDEF TRICK
// 'Set' is now an alias for an array of 8 bools.
// In C, passing an array to a function passes the address by default.
typedef bool Set[ARRAY_SIZE];

/* --- PROTOTYPES --- */
void initialize(Set set);
void insert(Set set, int element);
void deletes(Set set, int element);
bool find(Set set, int element);
void unions(Set A, Set B, Set C);
void intersection(Set A, Set B, Set C);
void difference(Set A, Set B, Set C);
void display(Set set);
void displayBinary(Set set);
void displayDecimal(Set set);

int main(){
    Set setA, setB, setC;
    
    // Logic: Pass arrays directly (no need for & operator)
    initialize(setA);
    initialize(setB);
    initialize(setC);
    
    printf("Set A:\n");
    insert(setA, 1);
    insert(setA, 2);
    insert(setA, 3);
    display(setA);
    displayDecimal(setA);
    displayBinary(setA);
    
    printf("\nSet B:\n");
    insert(setB, 2);
    insert(setB, 4);
    insert(setB, 5);
    display(setB);
    displayDecimal(setB);
    displayBinary(setB);
    
    printf("\nSet C Operations:\n");
    
    printf("\nUnion: (A | B)\n");
    // Logic: Combine A and B, store result in C
    unions(setA, setB, setC);
    display(setC);
    
    printf("\nIntersection: (A & B)\n");
    // Logic: Overwrite C with intersection result
    intersection(setA, setB, setC);
    display(setC);
    
    printf("\nDifference: (A - B)\n");
    // Logic: Overwrite C with difference result
    difference(setA, setB, setC);
    display(setC);
    
    return 0;
}

void initialize(Set set){
    int a;
    // Logic: Loop through the array and set every slot to false (Empty)
    for(a = 0; a < ARRAY_SIZE; a++){
        set[a] = false;
    }
}

void insert(Set set, int element){
    // Logic: Check Bounds.
    // [FIX] Changed > 0 to >= 0 so we can store the number 0.
    if(element >= 0 && element < ARRAY_SIZE){
        // Logic: Direct Mapping. The number 'element' is the INDEX.
        // To insert '3', we just set index 3 to TRUE.
        set[element] = true;
    }
}

void deletes(Set set, int element){
    if(element >= 0 && element < ARRAY_SIZE){
        // Logic: To delete, just set that index back to FALSE.
        set[element] = false;
    }   
}

bool find(Set set, int element){
    // Logic: Constant time lookup. Just check if the index is true.
    if(element >= 0 && element < ARRAY_SIZE) {
        return set[element];
    }
    return false;
}

void unions(Set A, Set B, Set C){
    int a;
    // Logic: Loop through every possible number (0-7)
    for(a = 0; a < ARRAY_SIZE; a++){
        // If it exists in A OR in B, set it to true in C.
        C[a] = A[a] | B[a];
    }
}

void intersection(Set A, Set B, Set C){
    int a;
    for(a = 0; a < ARRAY_SIZE; a++){
        // If it exists in A AND in B, set it to true in C.
        C[a] = A[a] & B[a];
    }
}

void difference(Set A, Set B, Set C){
    int a;
    for(a = 0; a < ARRAY_SIZE; a++){
        // Logic: A AND (NOT B). 
        // We use ! operator because these are booleans, but ~ works too if casted.
        // (A[a] && !B[a]) is the standard boolean way, but bitwise works here too.
        C[a] = A[a] & ~(B[a]); 
    }
}

void display(Set set){
    int a;
    printf("{ ");
    for(a = 0; a < ARRAY_SIZE; a++){
        // Logic: Iterate through the array. If a slot is TRUE, print its INDEX.
        if(set[a]){
            printf("%d, ", a);
        }
    }
    printf("} \n");
}

void displayBinary(Set set){
    int a;
    printf("Binary Value: { ");
    // Logic: Print backwards (7 to 0) to match standard binary representation.
    for(a = ARRAY_SIZE - 1; a >= 0; a--){
        printf("%d ", set[a]); // Prints 1 for true, 0 for false
    }
    printf("} \n");
}

void displayDecimal(Set set){
    int a;
    int decimal = 0;
    // Logic: Convert the Boolean Array into a single Integer manually.
    for(a = 0; a < ARRAY_SIZE; a++){
        if(set[a]){
            // Logic: 1<<a calculates 2^a.
            // If index 3 is true, add 2^3 (8) to the total.
            decimal += (1 << a);
        }
    }
    printf("Decimal value is: { %d }\n", decimal);
}