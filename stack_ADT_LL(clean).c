#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node
{
    int data;
    struct node *link;
} Node;

Node* createNode(int data);
int push(Node **top_ref, int data);
int isEmpty(Node *top);
int pop(Node **top_ref);
int peek(Node *top);
void display(Node *top);
void reverse(Node** top_ref);

int main()
{
    Node *top1 = NULL;
    Node *top2 = NULL;
    Node **active = &top1;
    int choice;
    int value;
    int stackChoice;

    do
    {
        printf("Current Stack: %s\n", active == &top1 ? "Stack 1" : "Stack 2");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Switch Stack\n");
        printf("6. Reverse\n");
        printf("7. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter element to be pushed: ");
            scanf("%d", &value);
            push(active, value);
            break;

        case 2:
            value = pop(active);
            if (value != INT_MIN)
            {
                printf("Popped Element: %d\n", value);
            }
            else
            {
                printf("Stack is Empty! Cannot pop.\n");
            }
            break;

        case 3:
            value = peek(*active);
            if (value != INT_MIN)
            {
                printf("Top Element: %d\n", value);
            }
            else
            {
                printf("Stack is Empty! Cannot peek.\n");
            }
            break;

        case 4:
            display(*active);
            break;

        case 5:
            printf("Switch to:\n1. Stack 1\n2. Stack 2\nEnter your choice: ");
            scanf("%d", &stackChoice);
            if (stackChoice == 1)
            {
                active = &top1;
                printf("Switched to Stack 1.\n");
            }
            else if (stackChoice == 2)
            {
                active = &top2;
                printf("Switched to Stack 2.\n");
            }
            else
            {
                printf("Invalid choice! Staying with the current stack.\n");
            }
            break;

        case 6:
            reverse(active);
            break;

        case 7:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid Choice! Try Again!\n");
        }
    } while (choice != 7);

    return 0;
}

Node *createNode(int data)
{
    Node *newNode = malloc(sizeof(Node));
    if (!newNode)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->link = NULL;
    return newNode;
}

int push(Node **top_ref, int data)
{
    Node *new = createNode(data);
    new->link = *top_ref;
    *top_ref = new;
    return 1;
}

int pop(Node **top_ref)
{
    if (*top_ref == NULL)
    {
        return INT_MIN;
    }
    int val = (*top_ref)->data;
    Node *temp = *top_ref;
    *top_ref = (*top_ref)->link;
    free(temp);
    return val;
}

int isEmpty(Node *top)
{
    return top == NULL;
}

int peek(Node *top)
{
    if (isEmpty(top))
    {
        return INT_MIN;
    }
    return top->data;
}

void display(Node *top)
{
    if (isEmpty(top))
    {
        printf("Stack is Empty\n");
        return;
    }

    Node *temp = top;
    while (temp != NULL)
    {
        printf("%d\n", temp->data);
        temp = temp->link;
    }
    printf("\n");
}

void reverse(Node** top_ref)
{
    if (*top_ref == NULL)
    {
        printf("Cannot reverse an empty Stack!\n");
        return;
    }

    Node* aux1 = NULL;
    Node* aux2 = NULL;

    while (*top_ref != NULL)
    {
        int value = pop(top_ref);
        push(&aux1, value);
    }

    while (aux1 != NULL)
    {
        int value = pop(&aux1);
        push(&aux2, value);
    }

    while (aux2 != NULL)
    {
        int value = pop(&aux2);
        push(top_ref, value);
    }

    printf("Reversed Successfully!\n");
}
