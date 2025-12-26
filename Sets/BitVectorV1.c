#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void initialize(unsigned char *set);
void insert(unsigned char *set, int element);
void deletes(unsigned char *set, int element);
bool find(unsigned char set, int element);
unsigned char set_union(unsigned char A, unsigned char B);
unsigned char intersection(unsigned char A, unsigned char B);
unsigned char difference(unsigned char A, unsigned char B);
unsigned char symmetric_difference(unsigned char A, unsigned char B);
void display(unsigned char set);
void displayDecimal(unsigned char set);
void displayBinary(unsigned char set);

int main(){
    unsigned char setA, setB;
    
    initialize(&setA);
    initialize(&setB);
    
    // Logic: 1<<1 (2), 1<<2 (4), 1<<3 (8). Total = 14 (00001110)
    insert(&setA, 1);
    insert(&setA, 2);
    insert(&setA, 3);
    
    printf("Set A:\n");
    display(setA);
    displayDecimal(setA);
    displayBinary(setA);
    
    insert(&setB, 2);
    insert(&setB, 4);
    insert(&setB, 5);
    
    printf("\nSet B:\n");
    display(setB);
    displayDecimal(setB);

    // Logic: OR operation combines bits (1 if present in EITHER)
    printf("\nUnion (A | B):\n");
    display(set_union(setA, setB));
    
    // Logic: AND operation filters bits (1 if present in BOTH)
    printf("\nIntersection (A & B):\n");
    display(intersection(setA, setB));
    
    // Logic: A AND (NOT B) removes B's bits from A
    printf("\nDifference (A - B):\n");
    display(difference(setA, setB));
    
    // Logic: XOR operation (1 if present in ONE, but not BOTH)
    printf("\nSymmetric Difference (A ^ B):\n");
    display(symmetric_difference(setA, setB));
    
    printf("\nFound 3 in SET A? %s\n", find(setA, 3) ? "YES" : "NO");
    printf("Found 1 in SET B? %s\n", find(setB, 1) ? "YES" : "NO");
    
    return 0;
}

void initialize(unsigned char *set){
    // Logic: Set all 8 bits to 0. Empty Set.
    *set = 0;
}

void insert(unsigned char *set, int element){
    // Logic: Check bounds (0-7)
    if(element >= 0 && element < 8){
        // Logic Step 1: Create a mask. 
        // If element is 2, 1<<2 becomes 00000100.
        unsigned char mask = 1 << element;
        
        // Logic Step 2: Bitwise OR (|)
        // Turns the specific bit ON without messing up other bits.
        *set |= mask;
    }   
}

void deletes(unsigned char *set, int element){
    if(element >= 0 && element < 8){
        unsigned char mask = 1 << element;
        
        // Logic Step 1: Invert the mask (~)
        // 00000100 becomes 11111011
        
        // Logic Step 2: Bitwise AND (&)
        // Keeps all bits identical except the target bit, which is forced to 0.
        *set &= ~mask;
    }
}

bool find(unsigned char set, int element){
    if(element >= 0 && element < 8){
        unsigned char mask = 1 << element;
        // Logic: Mask the set. If result is non-zero, the bit was 1.
        return (set & mask) != 0;
    }
    return false;
}

unsigned char set_union(unsigned char A, unsigned char B){
    // Logic: Merges the sets.
    return A | B;
}

unsigned char intersection(unsigned char A, unsigned char B){
    // Logic: Keeps only common elements.
    return A & B;
}

unsigned char difference(unsigned char A, unsigned char B){
    // Logic: Start with A, then force-delete everything in B.
    // A & (~B)
    return A & (~B);
}

unsigned char symmetric_difference(unsigned char A, unsigned char B){
    // Logic: Exclusive OR. Elements in A or B, but not both.
    return A ^ B;
}

void display(unsigned char set){
    int a;
    printf("{ ");
    // Logic: Check every bit from 0 to 7.
    for(a = 0; a < 8; a++){
        // If the bit at position 'a' is ON, print 'a'.
        if(set & (1 << a)){
            printf("%d, ", a);
        }
    }
    printf("} \n");
}

void displayDecimal(unsigned char set){
    // Logic: Shows the integer value of the 8-bit number
    printf("Decimal Value: { %d } \n", set);
}

void displayBinary(unsigned char set){
    int a;
    // Logic: Iterate backwards (7 to 0) to print binary from Left to Right.
    for(a = 7; a >= 0; a--){
        unsigned char mask = 1 << a;
        if(set & mask){
            printf("1");
        } else{
            printf("0");
        }
    }
    printf("\n");
}