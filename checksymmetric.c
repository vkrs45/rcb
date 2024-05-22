#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node into a BST
struct Node* insert(struct Node* node, int data) {
    if (node == NULL) {
        return createNode(data);
    }

    if (data < node->data) {
        node->left = insert(node->left, data);
    } else if (data > node->data) {
        node->right = insert(node->right, data);
    }

    return node;
}

// Function to check if two subtrees are mirrors of each other
int areMirrors(struct Node* root1, struct Node* root2) {
    if (root1 == NULL && root2 == NULL) {
        return 1;
    }

    if (root1 == NULL || root2 == NULL) {
        return 0;
    }

    return (root1->data == root2->data) &&
           areMirrors(root1->left, root2->right) &&
           areMirrors(root1->right, root2->left);
}

// Function to check if a tree is symmetric
int isSymmetric(struct Node* root) {
    if (root == NULL) {
        return 1;
    }

    return areMirrors(root->left, root->right);
}

// Function to print the menu
void printMenu() {
    printf("\nMenu:\n");
    printf("1. Insert into Tree\n");
    printf("2. Check if Tree is Symmetric\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    struct Node* root = NULL;
    int choice, data;

    while (1) {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the data to insert into Tree: ");
                scanf("%d", &data);
                root = insert(root, data);
                break;
            case 2:
                if (isSymmetric(root)) {
                    printf("The tree is symmetric.\n");
                } else {
                    printf("The tree is not symmetric.\n");
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
