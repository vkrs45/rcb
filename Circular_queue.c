#include <stdio.h>
#define N 5
int queue[N];
int front = -1;
int rear = -1;

int isEmpty()
{
    if (front == -1 && rear == -1)
        return 1;
    else
        return 0;
}

int isFull()
{
    if (((rear + 1) % N) == front)
        return 1;
    else
        return 0;
}

int onlyOne()
{
    if (front == rear)
        return 1;
    else
        return 0;
}

void Enqueue(int x)
{
    if (isFull())
    {
        printf("Overflow\n");
    }

    else if (isEmpty())
    {
        front = rear = 0;
        queue[rear] = x;
    }

    else
    {
        rear = (rear + 1) % N;
        queue[rear] = x;
    }
}
  
void Dequeue()
{
    if (isEmpty())
    {
        printf("Underflow\n");
    }

    else if (onlyOne())
    {
        printf("Deleted element is %d", queue[front]);
        front = rear = -1;
    }

    else
    {
        printf("Deleted element is %d", queue[front]);
        front = (front + 1) % N;
    }
}

void Display()
{
    int i = front;

    if (isEmpty())
    {
        printf("Underflow\n");
    }

    else
    {
        while (i != rear)
        {
            printf("%d ", queue[i]);
            i = (i + 1) % N;
        }

        printf("%d", queue[i]);
    }
}

void Peek()
{
    if (isEmpty())
    {
        printf("Underflow\n");
    }

    else
    {
        printf("%d", queue[front]);
    }
}

int main()
{

    int choice;

    do
    {
        printf("\n\nEnter the choice\n\n");
        printf("1.Enqueue the element\n2.Dequeue the element\n3.Display the element\n4.Peek (front element)\n5.Exit the code\n\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            int x;
            printf("Enter the element\n");
            scanf("%d", &x);
            Enqueue(x);
            break;
        }

        case 2:
        {
            Dequeue();
            break;
        }

        case 3:
        {
            Display();
            break;
        }

        case 4:
        {
            Peek();
            break;
        }
        }

    } while (choice != 5);

    return 0;
}