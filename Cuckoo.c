
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 11
#define MAX_DISPLACEMENTS ROW

// Function declarations
int hash1(int key);
int hash2(int key);
void rehash(int a1[ROW], int a2[ROW]);
void insertElement(int a1[ROW], int a2[ROW], int n);
void printArray(int a[ROW]);

int hash1(int key) {
    return key % ROW;
}

int hash2(int key) {
    return (key / ROW) % ROW;
}

void rehash(int a1[ROW], int a2[ROW]) {
    int old_a1[ROW], old_a2[ROW];
    for (int i = 0; i < ROW; i++) {
        old_a1[i] = a1[i];
        old_a2[i] = a2[i];
        a1[i] = -1;
        a2[i] = -1;
    }

    for (int i = 0; i < ROW; i++) {
        if (old_a1[i] != -1) {
            insertElement(a1, a2, old_a1[i]);
        }
        if (old_a2[i] != -1) {
            insertElement(a1, a2, old_a2[i]);
        }
    }
}

void insertElement(int a1[ROW], int a2[ROW], int n) {
    int count = 0;

    while (count < MAX_DISPLACEMENTS) {
        int pos1 = hash1(n);
        if (a1[pos1] == -1) {
            a1[pos1] = n;
            return;
        }
        int temp = a1[pos1];
        a1[pos1] = n;
        n = temp;
        
        int pos2 = hash2(n);
        if (a2[pos2] == -1) {
            a2[pos2] = n;
            return;
        }
        temp = a2[pos2];
        a2[pos2] = n;
        n = temp;
        count++;
    }

    // If insertion fails after many attempts, rehashing is needed
    rehash(a1, a2);
}

void printArray(int a[ROW]) {
    for (int i = 0; i < ROW; i++) {
        if (a[i] == -1) {
            printf("|   |");
        } else {
            printf("| %d |", a[i]);
        }
    }
    printf("\n");
}

int main() {
    int a1[ROW], a2[ROW];
    
    for (int i = 0; i < ROW; i++) {
        a1[i] = -1;
        a2[i] = -1;
    }

    int choice, n;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Enter a number\n");
        printf("2. Print the hash tables\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the number: ");
                scanf("%d", &n);
                insertElement(a1, a2, n);
                break;
            case 2:
                printf("\nHash Table 1:\n");
                printArray(a1);
                printf("\nHash Table 2:\n");
                printArray(a2);
                break;
            case 3:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }

    return 0;
}