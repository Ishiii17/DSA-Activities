#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// [NOTE] BITFIELD DEFINITION
// By saying ": 8", we restrict 'field' to exactly 8 bits.
// Even though 'unsigned int' is usually 32 bits, this struct will only use the first 8.
// This limits our Set to elements {0, 1, 2, 3, 4, 5, 6, 7}.
typedef struct{
    unsigned int field: 8; 
} Set;

/* --- PROTOTYPES --- */
void initialize(Set *set);
void insert(Set *set, int element);
void deletes(Set *set, int element);
bool find(Set set, int element);
Set unions(Set A, Set B);
Set intersection(Set A, Set B);
Set difference(Set A, Set B);
void display(unsigned char set);
void displayBinary(unsigned char set);
void displayDecimal(unsigned char set);


int main(){
    Set setA, setB, setC;
    
    // Logic: Start with empty sets (00000000)
    initialize(&setA);
    initialize(&setB);
    
    // Logic: Insert 1, 2, 3 into Set A
    // Binary: 00001110 (14 in decimal)
    insert(&setA, 1);
    insert(&setA, 2);
    insert(&setA, 3);
    
    printf("Set A:\n");
    // [NOTE] Accessing the bitfield member using dot notation (.field)
    display(setA.field);
    displayDecimal(setA.field);
    displayBinary(setA.field);
    
    // Logic: Insert 2, 4, 5 into Set B
    // Binary: 00110100 (52 in decimal)
    insert(&setB, 2);
    insert(&setB, 4);
    insert(&setB, 5);
    
    printf("\nSet B:\n");
    display(setB.field);
    displayDecimal(setB.field);
    displayBinary(setB.field);
    
    printf("\nSet C Operations:");
    
    printf("\nUnions: (A | B)\n");
    // Logic: Combine bits (Merge sets)
    setC = unions(setA, setB);
    display(setC.field);
    
    printf("\nIntersection: (A & B)\n");
    // Logic: Find common bits (Common elements)
    setC = intersection(setA, setB);
    display(setC.field);
    
    printf("\nDifference: (A - B)\n");
    // Logic: Remove bits of B from A
    setC = difference(setA, setB);
    display(setC.field);
    
    return 0;
}

void initialize(Set *set){
    // Logic: Clear all bits to 0
    set->field = 0;
}

void insert(Set *set, int element){
    // Logic: Check Bounds (0-7)
    if(element >= 0 && element < 8){
        unsigned int mask = 1 << element;
        // Logic: OR operation to turn the specific bit ON
        set->field |= mask;
    }
}

void deletes(Set *set, int element){
    if(element >= 0 && element < 8){
        unsigned int mask = 1 << element;
        // Logic: AND with NOT mask (e.g., & 11111011) to turn bit OFF
        set->field &= ~mask;
    }
}

bool find(Set set, int element){
    if(element >= 0 && element < 8){
        unsigned int mask = 1 << element;
        // Logic: Check if the specific bit is ON
        if(set.field & mask){
            return true;
        }
    }
    return false;
}

Set unions(Set A, Set B){
    Set C;
    // Logic: Standard Bitwise OR
    C.field = A.field | B.field;
    return C;
}

Set intersection(Set A, Set B){
    Set C;
    // Logic: Standard Bitwise AND
    C.field = A.field & B.field;
    return C;
}

Set difference(Set A, Set B){
    Set C;
    // Logic: A AND (NOT B)
    C.field = A.field & ~(B.field);
    return C;
}

// [NOTE] For display functions, we can treat the bitfield like a regular unsigned char/int
void display(unsigned char set){
    int a;
    printf("{ ");
    for(a = 0; a < 8; a++){
        // Logic: Check bit 'a'. If result is non-zero, print 'a'.
        if(set & (1 << a)){
            printf("%d, ", a);
        }
    }
    printf(" }\n");
}

void displayDecimal(unsigned char set){
    printf("Decimal value is: { %d }\n", set);
}

void displayBinary(unsigned char set){
    printf("Binary Value: { ");
    int a;
    // Logic: Loop backwards (7 to 0) to print binary correctly (MSB to LSB)
    for(a = 7; a >= 0; a--){
        unsigned char mask = 1 << a;
        if((set & mask)){
            printf("1");
        } else {
            printf("0");
        }
    }
    printf(" }\n");
}