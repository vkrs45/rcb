#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *left, *right;
};

struct node *createNode(int key)
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = key;
    newnode->left = NULL;
    newnode->right = NULL;
    return (newnode);
}

struct node *insertRecursive(struct node *root, int value)
{
    if (root == NULL)
        return createNode(value);

    if (value < root->data)
        root->left = insertRecursive(root->left, value);
    else if (value > root->data)
        root->right = insertRecursive(root->right, value);

    return root;
}

struct node *insertWithoutRecursion(struct node *root, int value)
{
    struct node *newNode = createNode(value);
    struct node *current = root;
    struct node *parent = NULL;

    while (current != NULL)
    {
        parent = current;
        if (value < current->data)
            current = current->left;
        else if (value > current->data)
            current = current->right;
        else
            return root;
    }

    if (parent == NULL)
        root = newNode;
    else if (value < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;

    return root;
}

void inorderRecursive(struct node *root)
{
    if (root == NULL)
        return;
    inorderRecursive(root->left);
    printf("%d ", root->data);
    inorderRecursive(root->right);
}

void inorderWithoutRecursion(struct node *root)
{
    struct node *stack[100];
    int top = -1;
    struct node *current = root;

    while (current != NULL || top != -1)
    {
        while (current != NULL)
        {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        printf("%d ", current->data);
        current = current->right;
    }
}

void countNodesWithRecursion(struct node *root, int *count)
{
    if (root != NULL)
    {
        countNodesWithRecursion(root->left, count);
        (*count)++;
        countNodesWithRecursion(root->right, count);
    }
}

int countNodesIterative(struct node *root)
{
    int count = 0;
    struct node *stack[100];
    int top = -1;

    if (root == NULL)
        return 0;

    stack[++top] = root;

    while (top != -1)
    {
        struct node *current = stack[top--];
        count++;

        if (current->right != NULL)
            stack[++top] = current->right;
        if (current->left != NULL)
            stack[++top] = current->left;
    }
    return count;
}

void mirrorWithRecursion(struct node *node)
{
    if (node == NULL)
        return;
    else
    {
        struct node *temp;

        mirrorWithRecursion(node->left);
        mirrorWithRecursion(node->right);

        temp = node->left;
        node->left = node->right;
        node->right = temp;
    }
}

void mirrorIterative(struct node *root)
{
    if (root == NULL)
        return;

    struct node *stack[1000];
    int top = -1;

    stack[++top] = root;

    while (top >= 0)
    {
        struct node *current = stack[top--];
        struct node *temp = current->left;
        current->left = current->right;
        current->right = temp;

        if (current->left != NULL)
            stack[++top] = current->left;
        if (current->right != NULL)
            stack[++top] = current->right;
    }
}

int heightWithRecursion(struct node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        int left = heightWithRecursion(root->left);
        int right = heightWithRecursion(root->right);
        if (left > right)
        {
            return left + 1;
        }
        else
        {
            return right + 1;
        }
    }
}
  
int heightIterative(struct node *root)
{
    if (root == NULL)
        return 0;

    int height = 0;
    struct node *queue[1000];
    int front = -1, rear = -1;

    queue[++rear] = root;

    while (front != rear)
    {
        int nodeCount = rear - front;

        while (nodeCount > 0)
        {
            struct node *current = queue[++front];

            if (current->left != NULL)
                queue[++rear] = current->left;

            if (current->right != NULL)
                queue[++rear] = current->right;

            nodeCount--;
        }

        height++;
    }

    return height;
}

int main()
{
    struct node *root = NULL;
    int count = 0;
    int choice, value;
    do
    {
        printf("\n\n1. Insert (Recursive)\n");
        printf("2. Insert (Iterative)\n");
        printf("3. Inorder Traversal (Recursive)\n");
        printf("4. Inorder Traversal (Iterative)\n");
        printf("5. Count Nodes (Recursive)\n");
        printf("6. Count Nodes (Iterative)\n");
        printf("7. Mirror Tree (Recursive)\n");
        printf("8. Mirror Tree (Iterative)\n");
        printf("9. Height of Tree (Recursive)\n");
        printf("10. Height of Tree (Iterative)\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &value);
            root = insertRecursive(root, value);
            break;
        case 2:
            printf("Enter value to insert: ");
            scanf("%d", &value);
            root = insertWithoutRecursion(root, value);
            break;
        case 3:
            printf("Inorder Traversal (Recursive): ");
            inorderRecursive(root);
            printf("\n");
            break;
        case 4:
            printf("Inorder Traversal (Iterative): ");
            inorderWithoutRecursion(root);
            printf("\n");
            break;
        case 5:
            countNodesWithRecursion(root, &count);
            printf("Number of nodes in tree (Recursive): %d\n", count);
            break;
        case 6:
            printf("Number of nodes in tree (Iterative): %d\n", countNodesIterative(root));
            break;
        case 7:
            mirrorWithRecursion(root);
            printf("Mirror tree (Recursive) created.\n");
            inorderRecursive(root);
            printf("\n");
            break;
        case 8:
            mirrorIterative(root);
            printf("Mirror tree (Iterative) created.\n");
            inorderRecursive(root);
            printf("\n");
            break;
        case 9:
            printf("Height of tree (Recursive): %d\n", heightWithRecursion(root));
            break;
        case 10:
            printf("Height of tree (Iterative): %d\n", heightIterative(root));
            break;
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please enter a number between 0 and 10.\n");
        }
    } while (choice != 0);

    return 0;
}