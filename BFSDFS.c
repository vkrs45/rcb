#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
};

struct Queue* createQueue(unsigned capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

bool isFull(struct Queue* queue) {
    return (queue->size == queue->capacity);
}

bool isEmpty(struct Queue* queue) {
    return (queue->size == 0);
}

void enqueue(struct Queue* queue, int item) {
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

int dequeue(struct Queue* queue) {
    if (isEmpty(queue))
        return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

void addEdge(int** adjList, int u, int v) {
    adjList[u][v] = 1;
}

void BFS(int** adjList, int V, int startVertex) {
    bool* visited = (bool*)malloc(V * sizeof(bool));
    struct Queue* queue = createQueue(V);

    for (int i = 0; i < V; ++i)
        visited[i] = false;

    visited[startVertex] = true;
    enqueue(queue, startVertex);

    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);

        for (int adjacentVertex = 0; adjacentVertex < V; ++adjacentVertex) {
            if (adjList[currentVertex][adjacentVertex] && !visited[adjacentVertex]) {
                visited[adjacentVertex] = true;
                enqueue(queue, adjacentVertex);
            }
        }
    }

    free(visited);
    free(queue->array);
    free(queue);
}

void DFSUtil(int** adjList, int V, int startVertex, bool* visited) {
    visited[startVertex] = true;
    printf("%d ", startVertex);

    for (int adjacentVertex = 0; adjacentVertex < V; ++adjacentVertex) {
        if (adjList[startVertex][adjacentVertex] && !visited[adjacentVertex])
            DFSUtil(adjList, V, adjacentVertex, visited);
    }
}

void DFS(int** adjList, int V, int startVertex) {
    bool* visited = (bool*)malloc(V * sizeof(bool));

    for (int i = 0; i < V; ++i)
        visited[i] = false;

    DFSUtil(adjList, V, startVertex, visited);

    free(visited);
}

int main() {
    int numVertices = 0, numEdges = 0, startVertex = 0;
    int** adjList;

    while (1) {
        printf("\n\n-------Select the operation to be performed-------\n");
        printf("[1] Create Graph\n");
        printf("[2] BFS\n");
        printf("[3] DFS\n");
        printf("[0] EXIT\n");
        printf("Choose the operation you want to perform: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the number of vertices in the graph: ");
                scanf("%d", &numVertices);

                adjList = (int*)malloc(numVertices * sizeof(int));
                for (int i = 0; i < numVertices; ++i) {
                    adjList[i] = (int*)malloc(numVertices * sizeof(int));
                    for (int j = 0; j < numVertices; ++j)
                        adjList[i][j] = 0;
                }

                printf("Enter the number of edges in the graph: ");
                scanf("%d", &numEdges);

                printf("Enter the edges (vertex pairs):\n");
                for (int i = 0; i < numEdges; i++) {
                    int u, v;
                    scanf("%d %d", &u, &v);
                    addEdge(adjList, u, v);
                    addEdge(adjList, v, u); // Assuming an undirected graph
                }
                break;
            case 2:
                if (numVertices > 0 && numEdges > 0) {
                    printf("Enter the starting vertex for BFS: ");
                    scanf("%d", &startVertex);
                    if (startVertex < 0 || startVertex >= numVertices) {
                        printf("Invalid starting vertex.\n");
                        break;
                    }
                    printf("BFS traversal starting from vertex %d : ", startVertex);
                    BFS(adjList, numVertices, startVertex);
                    printf("\n");
                } else {
                    printf("Graph not created yet.\n");
                }
                break;
            case 3:
                if (numVertices > 0 && numEdges > 0) {
                    printf("Enter the starting vertex for DFS : ");
                    scanf("%d", &startVertex);
                    if (startVertex < 0 || startVertex >= numVertices) {
                        printf("Invalid starting vertex.\n");
                        break;
                    }
                    printf("DFS traversal starting from vertex %d : ", startVertex);
                    DFS(adjList, numVertices, startVertex);
                    printf("\n");
                } else {
                    printf("Graph not created yet.\n");
                }
                break;
            case 0:
                printf("\nProgram exited.\n");
                return 0;
            default:
                printf("\nInvalid choice. Please enter again.\n");
        }
    }

    return 0;
}