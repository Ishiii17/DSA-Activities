#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int hash(int key) {
    return key % SIZE;
}

void insert(int key) {
    int index = hash(key);
    char filename[20];

    // Logic: Dynamic Filename Generation
    // We create a unique file for each bucket: "bucket_0.txt", "bucket_1.txt", etc.
    sprintf(filename, "bucket_%d.txt", index);

    // Logic: Open in Append Mode ("a")
    // If the file exists, we add to the end (Collision Handling).
    // If it doesn't exist, the OS creates it for us.
    FILE *fp = fopen(filename, "a");
    if(fp == NULL) return;

    // Logic: Store the key
    // We add a newline (\n) so each key is on its own line, making it easy to read later.
    fprintf(fp, "%d\n", key);
    fclose(fp);
}

void search(int key) {
    int index = hash(key);
    char filename[20];
    int x;

    sprintf(filename, "bucket_%d.txt", index);

    // Logic: Open in Read Mode ("r")
    FILE *fp = fopen(filename, "r");
    
    // Logic: Check if bucket exists
    // If the file is NULL, it means nothing has ever hashed to this index.
    if(fp == NULL) {
        printf("Not Found %d\n", key);
        return;
    }

    // Logic: Linear Search through the File
    // We read the file integer by integer. This is the equivalent of traversing a linked list.
    while(fscanf(fp, "%d", &x) != EOF) {
        if(x == key) {
            printf("Found %d\n", key);
            fclose(fp);
            return;
        }
    }

    fclose(fp);
    printf("Not Found %d\n", key);
}

int main() {
    // [NOTE] Important Logic Detail:
    // 10, 15, 20, 25, 30 all equal 0 when mod by 5.
    // This causes a massive collision! 
    // ALL these numbers will go into "bucket_0.txt".
    insert(10);
    insert(15);
    insert(20);
    insert(25);
    insert(30);

    search(15); // Will scan bucket_0.txt
    search(99); // Will scan bucket_4.txt (which likely doesn't exist)

    return 0;
}