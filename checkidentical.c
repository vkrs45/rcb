#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};


struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}


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
\
int areIdentical(struct Node* root1, struct Node* root2) {
    if (root1 == NULL && root2 == NULL) {
        return 1;
    }

    if (root1 == NULL || root2 == NULL) {
        return 0;
    }

    return (root1->data == root2->data) &&
           areIdentical(root1->left, root2->left) &&
           areIdentical(root1->right, root2->right);
}

void printMenu() {
    printf("\nMenu:\n");
    printf("1. Insert into Tree 1\n");
    printf("2. Insert into Tree 2\n");
    printf("3. Check if Trees are Identical\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    struct Node* root1 = NULL;
    struct Node* root2 = NULL;
    int choice, data;

    while (1) {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the data to insert into Tree 1: ");
                scanf("%d", &data);
                root1 = insert(root1, data);
                break;
            case 2:
                printf("Enter the data to insert into Tree 2: ");
                scanf("%d", &data);
                root2 = insert(root2, data);
                break;
            case 3:
                if (areIdentical(root1, root2)) {
                    printf("The trees are identical.\n");
                } else {
                    printf("The trees are not identical.\n");
                }
                break;
            case 4:
                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
