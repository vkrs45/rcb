#include <stdio.h>
#include <stdlib.h>

// A structure to represent a graph edge
struct Edge {
    int src, dest, weight;
};

// A structure to represent a subset for union-find
struct Subset {
    int parent;
    int rank;
};

// A structure to represent a graph
struct Graph {
    int V, E;
    struct Edge* edge;
};

// Function to create a graph with V vertices and E edges
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*) malloc(graph->E * sizeof(struct Edge));
    return graph;
}

// A utility function to find set of an element i (uses path compression technique)
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// A function that does union of two sets of x and y (uses union by rank)
void Union(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Compare two edges according to their weights. Used in qsort() for sorting an array of edges
int compareEdges(const void* a, const void* b) {
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight > b1->weight;
}

// Function to print the constructed MST stored in result[]
void printMST(struct Edge result[], int E) {
    printf("Following are the edges in the constructed MST\n");
    int minimumCost = 0;
    for (int i = 0; i < E; ++i) {
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
        minimumCost += result[i].weight;
    }
    printf("Minimum Cost Spanning tree: %d\n", minimumCost);
}

// Function to construct and print MST for a graph represented using adjacency matrix representation
void KruskalMST(struct Graph* graph) {
    int V = graph->V;
    struct Edge result[V]; // Tnis will store the resultant MST
    int e = 0; // An index variable, used for result[]
    int i = 0; // An index variable, used for sorted edges

    // Step 1: Sort all the edges in non-decreasing order of their weight. If we are not allowed to change the given graph, we can create a copy of the array of edges
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), compareEdges);

    // Allocate memory for creating V subsets
    struct Subset* subsets = (struct Subset*) malloc(V * sizeof(struct Subset));

    // Create V subsets with single elements
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Number of edges to be taken is equal to V-1
    while (e < V - 1 && i < graph->E) {
        // Step 2: Pick the smallest edge. Check if it forms a cycle with the spanning tree formed so far. If cycle is not formed, include this edge. Else, discard it.
        struct Edge next_edge = graph->edge[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // If including this edge does not cause cycle, include it in result and increment the index of result for next edge
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    // Print the constructed MST
    printMST(result, e);

    // Free allocated memory
    free(subsets);
}

// Function to print the menu
void printMenu() {
    printf("\nMenu:\n");
    printf("1. Input Graph\n");
    printf("2. Run Kruskal's Algorithm to find MST\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}

// Function to input the graph
struct Graph* inputGraph() {
    int V, E;
    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    printf("Enter the number of edges: ");
    scanf("%d", &E);

    struct Graph* graph = createGraph(V, E);

    printf("Enter the edges (source destination weight):\n");
    for (int i = 0; i < E; i++) {
        printf("Edge %d: ", i + 1);
        scanf("%d %d %d", &graph->edge[i].src, &graph->edge[i].dest, &graph->edge[i].weight);
    }

    return graph;
}

int main() {
    struct Graph* graph = NULL;
    int choice;

    while (1) {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (graph != NULL) {
                    free(graph->edge);
                    free(graph);
                }
                graph = inputGraph();
                break;
            case 2:
                if (graph == NULL) {
                    printf("Graph not input yet. Please input the graph first.\n");
                } else {
                    KruskalMST(graph);
                }
                break;
            case 3:
                if (graph != NULL) {
                    free(graph->edge);
                    free(graph);
                }
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
2. Run Kruskal's Algorithm to find MST
3. Exit
Enter your choice: 1
Enter the number of vertices: 4
Enter the number of edges: 5
Enter the edges (source destination weight):
Edge 1: 0 1 10
Edge 2: 0 2 6
Edge 3: 0 3 5
Edge 4: 1 3 15
Edge 5: 2 3 4

Menu:
1. Input Graph
2. Run Kruskal's Algorithm to find MST
3. Exit
Enter your choice: 2
Following are the edges in the constructed MST
2 -- 3 == 4
0 -- 3 == 5
0 -- 1 == 10
Minimum Cost Spanning tree: 19

Menu:
1. Input Graph
2. Run Kruskal's Algorithm to find MST
3. Exit
Enter your choice: 3*/