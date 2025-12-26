#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
#define EMPTY -1
#define DELETED -2 // [NOTE] This is the "Tombstone". It means "Used to be here".

int table[SIZE];

int hash(int key) {
    return key % SIZE;
}

void initialize() {
    int i;
    // Logic: Mark all slots as technically empty to start.
    for(i = 0; i < SIZE; i++) {
        table[i] = EMPTY;
    }
}

void insert(int key) {
    int index = hash(key);
    int start = index;

    // Logic: Find a valid spot.
    // We skip slots that are currently occupied.
    // [CRITICAL] We treat DELETED slots as "available to overwrite".
    // However, your specific loop condition skips DELETED spots too effectively?
    // Wait, let's look closer:
    // "while(table[index] != EMPTY && table[index] != DELETED)"
    // This loop continues as long as the slot is FULL (not empty AND not deleted).
    // So if it hits a DELETED slot, the loop stops, and we insert there.
    // This is CORRECT efficient reuse of space!
    while(table[index] != EMPTY && table[index] != DELETED) {
        index = (index + 1) % SIZE;
        // Logic: Stop if we circled back to the start (Table is full).
        if(index == start) {
            printf("Table is full!\n");
            return;
        }
    }
    table[index] = key;
}

void delete(int key) {
    int index = hash(key);
    int start = index;

    // Logic: Search for the item to delete.
    // We stop at EMPTY because linear probing guarantees the item 
    // couldn't be past an EMPTY slot.
    // [CRITICAL] We DO NOT stop at DELETED. We skip over tombstones 
    // because the item we want might be further down.
    while(table[index] != EMPTY) {
        if(table[index] == key) {
            // Logic: Mark as DELETED instead of EMPTY.
            // If we marked it EMPTY, a search for an item that collided 
            // and lives at index+1 would stop here incorrectly.
            table[index] = DELETED;
            return;
        }
        index = (index + 1) % SIZE;
        if(index == start) return;
    }
}

void search(int key) {
    int index = hash(key);
    int start = index;

    // Logic: Same as delete. 
    // Continue searching as long as we don't hit an EMPTY wall.
    // We treat DELETED slots as "Keep moving, nothing here, but check next".
    while(table[index] != EMPTY) {
        if(table[index] == key) {
            printf("Found %d at index %d\n", key, index);
            return;
        }
        index = (index + 1) % SIZE;
        if(index == start) break;
    }
    printf("Not Found %d\n", key);
}

void display() {
    int i;
    for(i = 0; i < SIZE; i++) {
        if(table[i] == EMPTY)
            printf("%d: [   ] (Empty)\n", i);
        else if(table[i] == DELETED)
            printf("%d: [ X ] (Tombstone)\n", i);
        else
            printf("%d: [ %d ]\n", i, table[i]);
    }
    printf("\n");
}

int main() {
    initialize();

    printf("--- Inserting 10, 20, 15, 25, 35 ---\n");
    // 10 -> index 0
    // 20 -> index 0 (Collision) -> index 1
    // 15 -> index 5
    // 25 -> index 5 (Collision) -> index 6
    // 35 -> index 5 (Collision) -> index 6 (Collision) -> index 7
    insert(10);
    insert(20);
    insert(15);
    insert(25);
    insert(35);

    display();

    printf("--- Searching 15 and Deleting 20 ---\n");
    search(15);
    delete(20); // This puts a Tombstone at index 1

    display();

    // [NOTE] Test the Tombstone Logic
    // If we search for 35 now (which is at 7), we start at 5.
    // We check 5 (15) -> No.
    // We check 6 (25) -> No.
    // We check 7 (35) -> Yes.
    // 
    // Now imagine we delete 20 (at index 1).
    // If we search for something that hashed to 0 but lives at 2,
    // the search starts at 0, sees 1 is DELETED, and CORRECTLY continues to 2.
    
    return 0;
}