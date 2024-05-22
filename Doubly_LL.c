
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
    struct node *prev;
};

void printDoublyLinkedList(struct node *head)
{
    struct node *ptr = head;
    while (ptr != NULL)
    {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
}

struct node *addToEmpty(struct node *head)
{
    int data;
    printf("Enter the data\n");
    scanf("%d", &data);
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->prev = NULL;
    temp->data = data;
    temp->next = NULL;

    head = temp;

    return head;
}

struct node *insertAtBegin(struct node *head)
{
    int data;
    printf("Enter the data\n");
    scanf("%d", &data);
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->prev = NULL;
    temp->data = data;
    temp->next = NULL;

    temp->next = head;
    head->prev = temp;
    head = temp;

    return head;
}

void insertAtEnd(struct node *head)
{
    int data;
    printf("Enter the data\n");
    scanf("%d", &data);
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->prev = NULL;
    temp->data = data;
    temp->next = NULL;
     
    struct node *ptr = head;
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }

    ptr->next = temp;
    temp->prev = ptr;
}

void insertBetween(struct node *head)
{
    int position, data;
    printf("Enter the position\n");
    scanf("%d", &position);
    printf("Enter the data\n");
    scanf("%d", &data);
    struct node *ptr = head;
    while (position > 1)
    {
        ptr = ptr->next;
        position--;
    }

    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->prev = NULL;
    temp->data = data;
    temp->next = NULL;

    temp->next = ptr->next;
    temp->prev = ptr;
    ptr->next = temp;
    temp->next->prev = temp;
}

struct node *deleteAtBegin(struct node *head)
{
    struct node *temp = head;
    head = temp->next;
    head->prev = NULL;

    free(temp);
    temp = NULL;

    return head;
}

void deleteAtEnd(struct node *head)
{
    struct node *ptr = head;
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }

    ptr->prev->next = NULL;

    free(ptr);
    ptr = NULL;
}

void deleteBetween(struct node* head){
    int position;
    printf("Enter the position\n");
    scanf("%d", &position);
    struct node *ptr = head;
    while (position >=1)
    {
        ptr = ptr->next;
        position--;
    }
    
    ptr->next->prev=ptr->prev;
    ptr->prev->next=ptr->next;

    free(ptr);
    ptr=NULL;
}

int main()
{
    struct node *head = NULL;
    int choice;

    do
    {
        printf("\nDoubly Linked List Menu:\n");
        printf("1. Add to Empty List\n");
        printf("2. Insert at Beginning\n");
        printf("3. Insert at End\n");
        printf("4. Insert Between\n");
        printf("5. Delete at Beginning\n");
        printf("6. Delete at End\n");
        printf("7. Delete Between\n");
        printf("8. Print List\n");
        printf("9. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            head = addToEmpty(head);
            break;

        case 2:
            head = insertAtBegin(head);
            break;

        case 3:
            insertAtEnd(head);
            break;

        case 4:
            insertBetween(head);
            break;

        case 5:
            head = deleteAtBegin(head);
            break;

        case 6:
            deleteAtEnd(head);
            break;

        case 7:
            deleteBetween(head);
            break;

        case 8:
            printDoublyLinkedList(head);
            break;

        case 9:
            printf("Exiting the program.\n");
            break;

        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 9);

    return 0;
}