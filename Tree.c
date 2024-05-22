#include <stdlib.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

struct node *createNode(int value)
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
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

struct node *minValueNode(struct node *node)
{
    struct node *current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

struct node *deleteNodeRecursive(struct node *root, int value)
{
    if (root == NULL)
        return root;

    if (value < root->data)
        root->left = deleteNodeRecursive(root->left, value);
    else if (value > root->data)
        root->right = deleteNodeRecursive(root->right, value);
    else
    {
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }
        struct node *temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNodeRecursive(root->right, temp->data);
    }
    return root;
}

struct node *deleteWithoutRecursion(struct node *root, int value)
{
    struct node *current = root;
    struct node *parent = NULL;

    while (current != NULL && current->data != value)
    {
        parent = current;
        if (value < current->data)
            current = current->left;
        else
            current = current->right;
    }

    if (current == NULL)
        return root;

    if (current->left == NULL)
    {
        if (parent == NULL)
            root = current->right;
        else if (current == parent->left)
            parent->left = current->right;
        else
            parent->right = current->right;
        free(current);
        return root;
    }
    else if (current->right == NULL)
    {
        if (parent == NULL)
            root = current->left;
        else if (current == parent->left)
            parent->left = current->left;
        else
            parent->right = current->left;
        free(current);
        return root;
    }
    else
    {
        struct node *temp = minValueNode(current->right);
        current->data = temp->data;

        struct node *successor_parent = current;
        struct node *successor = current->right;
        while (successor->left != NULL)
        {
            successor_parent = successor;
            successor = successor->left;
        }

        if (successor == current->right)
        {
            successor_parent->right = successor->right;
        }
        else
        {
            successor_parent->left = successor->right;
        }

        free(successor);
        return root;
    }
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

void preorderRecursive(struct node *root)
{
    if (root == NULL)
        return;
    printf("%d ", root->data);
    preorderRecursive(root->left);
    preorderRecursive(root->right);
}

void preorderWithoutRecursion(struct node *root)
{
    if (root == NULL)
        return;
    struct node *stack[100];
    int top = -1;
    stack[++top] = root;

    while (top != -1)
    {
        struct node *temp = stack[top--];
        printf("%d ", temp->data);
        if (temp->right != NULL)
            stack[++top] = temp->right;
        if (temp->left != NULL)
            stack[++top] = temp->left;
    }
}

void postorderRecursive(struct node *root)
{
    if (root == NULL)
        return;
    postorderRecursive(root->left);
    postorderRecursive(root->right);
    printf("%d ", root->data);
}

void postorderWithoutRecursion(struct node *root)
{
    if (root == NULL)
        return;
    struct node *stack1[100];
    struct node *stack2[100];
    int top1 = -1, top2 = -1;
    stack1[++top1] = root;

    while (top1 != -1)
    {
        struct node *temp = stack1[top1--];
        stack2[++top2] = temp;
        if (temp->left != NULL)
            stack1[++top1] = temp->left;
        if (temp->right != NULL)
            stack1[++top1] = temp->right;
    }

    while (top2 != -1)
        printf("%d ", stack2[top2--]->data);
}

int main()
{
    struct node *root = NULL;
    int choice, value;
    do
    {
        printf("\n-----------------------------------\n");
        printf("\nBinary Search Tree Operations\n");
        printf("1. Insert with Recursion\n");
        printf("2. Insert without Recursion\n");
        printf("3. Delete with Recursion\n");
        printf("4. Delete without Recursion\n");
        printf("5. Inorder Traversal with Recursion\n");
        printf("6. Inorder Traversal without Recursion\n");
        printf("7. Preorder Traversal with Recursion\n");
        printf("8. Preorder Traversal without Recursion\n");
        printf("9. Postorder Traversal with Recursion\n");
        printf("10. Postorder Traversal without Recursion\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter data: ");
            scanf("%d", &value);
            root = insertRecursive(root, value);
            break;
        case 2:
            printf("Enter data: ");
            scanf("%d", &value);
            root = insertWithoutRecursion(root, value);
            break;
        case 3:
            printf("Enter data: ");
            scanf("%d", &value);
            root = deleteNodeRecursive(root, value);
            break;
        case 4:
            printf("Enter data: ");
            scanf("%d", &value);
            root = deleteWithoutRecursion(root, value);
            break;
        case 5:
            printf("Inorder Traversal with Recursion: ");
            inorderRecursive(root);
            printf("\n");
            break;
        case 6:
            printf("Inorder Traversal without Recursion: ");
            inorderWithoutRecursion(root);
            printf("\n");
            break;
        case 7:
            printf("Preorder Traversal with Recursion: ");
            preorderRecursive(root);
            printf("\n");
            break;
        case 8:
            printf("Preorder Traversal without Recursion: ");
            preorderWithoutRecursion(root);
            printf("\n");
            break;
        case 9:
            printf("Postorder Traversal with Recursion: ");
            postorderRecursive(root);
            printf("\n");
            break;
        case 10:
            printf("Postorder Traversal without Recursion: ");
            postorderWithoutRecursion(root);
            printf("\n");
            break;
        case 11:
            printf("Exit\n");
            break;
        default:
            printf("Invalid choice\n");
        }
    } while (choice != 11);
    return 0;
}