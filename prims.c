#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// Maximum number of vertices in the graph
#define MAX 100

// Function to find the vertex with the minimum key value, from the set of vertices not yet included in the MST
int minKey(int key[], bool mstSet[], int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (mstSet[v] == false && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }

    return min_index;
}

// Function to print the constructed MST stored in parent[]
void printMST(int parent[], int graph[MAX][MAX], int V) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++) {
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
    }
}

// Function to construct and print MST for a graph represented using adjacency matrix representation
void primMST(int graph[MAX][MAX], int V) {
    int parent[MAX]; // Array to store constructed MST
    int key[MAX]; // Key values used to pick minimum weight edge in cut
    bool mstSet[MAX]; // To represent set of vertices not yet included in MST

    // Initialize all keys as INFINITE
    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    // Always include first 1st vertex in MST.
    key[0] = 0; // Make key 0 so that this vertex is picked as first vertex
    parent[0] = -1; // First node is always root of MST

    // The MST will have V vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum key vertex from the set of vertices not yet included in MST
        int u = minKey(key, mstSet, V);

        // Add the picked vertex to the MST Set
        mstSet[u] = true;

        // Update key value and parent index of the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not yet included in MST
        for (int v = 0; v < V; v++) {
            // graph[u][v] is non zero only for adjacent vertices of u
            // mstSet[v] is false for vertices not yet included in MST
            // Update the key only if graph[u][v] is smaller than key[v]
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Print the constructed MST
    printMST(parent, graph, V);
}

// Function to print the menu
void printMenu() {
    printf("\nMenu:\n");
    printf("1. Input Graph\n");
    printf("2. Run Prim's Algorithm to find MST\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}

// Function to input the graph
void inputGraph(int graph[MAX][MAX], int *V) {
    printf("Enter the number of vertices: ");
    scanf("%d", V);

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < *V; i++) {
        for (int j = 0; j < *V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
}

int main() {
    int graph[MAX][MAX];
    int V = 0;
    int choice;

    while (1) {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inputGraph(graph, &V);
                break;
            case 2:
                if (V == 0) {
                    printf("Graph not input yet. Please input the graph first.\n");
                } else {
                    primMST(graph, V);
                }
                break;
            case 3:
                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
/*Menu:
1. Input Graph
2. Run Prim's Algorithm to find MST
3. Exit
Enter your choice: 1
Enter the number of vertices: 5
Enter the adjacency matrix:
0 2 0 6 0
2 0 3 8 5
0 3 0 0 7
6 8 0 0 9
0 5 7 9 0

Menu:
1. Input Graph
2. Run Prim's Algorithm to find MST
3. Exit
Enter your choice: 2
Edge    Weight
0 - 1   2
1 - 2   3
0 - 3   6
1 - 4   5

Menu:
1. Input Graph
2. Run Prim's Algorithm to find MST
3. Exit*/