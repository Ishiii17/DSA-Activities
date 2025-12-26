#include <stdio.h>
#include <stdlib.h> // Added for exit() safety checks

#define SIZE 10
#define EMPTY -1 // [NOTE] We assume valid data is positive integers

int hash(int key) {
    return key % SIZE;
}

void initialize() {
    // Logic: "wb" (Write Binary) creates a new file (or overwrites existing).
    FILE *fp = fopen("hashtable.dat", "wb");
    int empty = EMPTY;

    // Logic: Fill the file with -1s so we know which spots are free.
    // This is like initializing an array, but on the hard drive.
    for(int i = 0; i < SIZE; i++)
        fwrite(&empty, sizeof(int), 1, fp);

    fclose(fp);
}

void insert(int key) {
    // Logic: "rb+" (Read/Write Binary). 
    // We need 'r' to check if a spot is empty, and '+' to write if it is.
    FILE *fp = fopen("hashtable.dat", "rb+");
    
    // Safety check (always good for file IO)
    if (fp == NULL) { printf("File error!\n"); return; }

    int index = hash(key);
    int value;

    // Logic Step 1: Linear Probing Loop
    // We try the hashed index. If full, we move to index+1.
    // We stop after SIZE attempts (to avoid infinite loops if full).
    for(int i = 0; i < SIZE; i++) {
        
        // Logic Step 2: Move Cursor & Read
        // fseek jumps the cursor to the byte offset of our index.
        fseek(fp, index * sizeof(int), SEEK_SET);
        fread(&value, sizeof(int), 1, fp);

        // Logic Step 3: Check Collision
        if(value == EMPTY) {
            // Logic Step 4: Write (The Tricky Part!)
            // fread moved the cursor forward. We must move it BACK to the start 
            // of this cell before writing, or we will overwrite the NEXT cell.
            fseek(fp, index * sizeof(int), SEEK_SET);
            fwrite(&key, sizeof(int), 1, fp);
            
            fclose(fp); // Save and close immediately
            return;
        }

        // Logic Step 5: Collision handling
        // Spot was taken. Move to next index (wrap around using %).
        index = (index + 1) % SIZE;   
    }

    // If we reach here, the table is full.
    printf("Table is full. Cannot insert %d\n", key);
    fclose(fp);
}

void search(int key) {
    // Logic: "rb" (Read Binary) is sufficient for searching.
    FILE *fp = fopen("hashtable.dat", "rb");
    if (fp == NULL) { printf("File error!\n"); return; }

    int index = hash(key);
    int value;

    for(int i = 0; i < SIZE; i++) {
        // Logic Step 1: Jump and Read
        fseek(fp, index * sizeof(int), SEEK_SET);
        fread(&value, sizeof(int), 1, fp);

        // Logic Step 2: Match Found
        if(value == key) {
            printf("Found %d at index %d\n", key, index);
            fclose(fp);
            return;
        }

        // Logic Step 3: Stop Early Optimization
        // In Linear Probing, if we hit an EMPTY slot, the value cannot exist 
        // further down the chain. We can stop searching immediately.
        if(value == EMPTY)
            break;

        // Logic Step 4: Continue Probing
        index = (index + 1) % SIZE;
    }

    fclose(fp);
    printf("Not Found %d\n", key);
}

int main() {
    initialize();

    // [NOTE] This will create a 40-byte file (10 ints * 4 bytes)
    insert(10); // Hashes to 0
    insert(20); // Hashes to 0 -> Collision -> Moves to 1
    insert(15); // Hashes to 5
    insert(25); // Hashes to 5 -> Collision -> Moves to 6
    insert(35); // Hashes to 5 -> Collision -> Moves to 6 (Full) -> Moves to 7

    search(15);
    search(35); // Should find at index 7
    search(99); // Should fail

    return 0;
}