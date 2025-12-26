#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    int adj[MAX][MAX]; // Logic: A grid where 1 means connected, 0 means not.
    int vertices;
} Graph;

void initGraph(Graph* g, int v) {
    int i, j;
    g->vertices = v;
    // Logic: Clear the matrix. Initially, no nodes are connected.
    for(i = 0; i < v; i++) {
        for(j = 0; j < v; j++) {
            g->adj[i][j] = 0;
        }
    }
}

void addEdge(Graph* g, int u, int v) {
    // Logic: Undirected Graph.
    // If 0 is connected to 1, then 1 must be connected to 0.
    g->adj[u][v] = 1;
    g->adj[v][u] = 1;
}

// --- DFS LOGIC (The Recursive "Stack" Approach) ---
void DFSUtil(Graph* g, int v, int visited[]) {
    int i;
    
    // Logic Step 1: Mark current node as visited and print it.
    visited[v] = 1;
    printf("%d ", v);
    
    // Logic Step 2: Check all possible connections (0 to vertices).
    for(i = 0; i < g->vertices; i++) {
        // Logic Step 3: If there is a connection (adj[v][i] == 1) 
        // AND we haven't visited 'i' yet...
        if(g->adj[v][i] && !visited[i]) {
            // Logic Step 4: DIVE DEEPER immediately (Recursion).
            DFSUtil(g, i, visited);
        }
    }
}

void DFS(Graph* g, int start) {
    // Logic: Need a visited array to stop infinite loops in cycles.
    int visited[MAX] = {0}; 
    printf("DFS Traversal: ");
    DFSUtil(g, start, visited);
    printf("\n");
}

// --- BFS LOGIC (The Iterative "Queue" Approach) ---
void BFS(Graph* g, int start) {
    int visited[MAX] = {0};
    
    // Logic: Simple Array Queue
    int queue[MAX];
    int front = 0, rear = 0;
    int i;

    // Logic Step 1: Start by enqueueing the first node
    visited[start] = 1;
    queue[rear++] = start;
    
    printf("BFS Traversal: ");

    // Logic Step 2: Loop until the queue is empty
    while(front < rear) {
        // Logic Step 3: Dequeue the current node and print it
        int curr = queue[front++];
        printf("%d ", curr);

        // Logic Step 4: Scan all neighbors
        for(i = 0; i < g->vertices; i++) {
            // If connected and not visited...
            if(g->adj[curr][i] && !visited[i]) {
                visited[i] = 1;     // Mark visited immediately so we don't add it twice
                queue[rear++] = i;  // Enqueue it to be processed later
            }
        }
    }
    printf("\n");
}

void display(Graph* g) {
    int i, j;
    printf("Adjacency Matrix:\n");
    for(i = 0; i < g->vertices; i++) {
        for(j = 0; j < g->vertices; j++) {
            printf("%d ", g->adj[i][j]);
        }
        printf("\n");
    }
}

int main() {
    Graph g;
    initGraph(&g, 5);

    // Logic: Creating this structure:
    //      0
    //     / \
    //    1   2
    //   / \
    //  3   4
    
    addEdge(&g, 0, 1);
    addEdge(&g, 0, 2);
    addEdge(&g, 1, 3);
    addEdge(&g, 1, 4);

    display(&g);
    
    // Logic: Should print 0 1 3 4 2 (Goes deep left first)
    DFS(&g, 0);
    
    // Logic: Should print 0 1 2 3 4 (Layer by layer)
    BFS(&g, 0);

    return 0;
}