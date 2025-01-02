#include <stdio.h>
#include <stdlib.h>
#include <limits.h>  // For INT_MIN

/**
 * @struct node
 * @brief A structure representing a node in the linked list.
 * @details Each node contains an integer `data` and a pointer to the next node, `link`.
 */
typedef struct node
{
    int data;         /**< Integer data of the node */
    struct node *link; /**< Pointer to the next node in the linked list */
} Node;

/**
 * @brief Creates a new node with a given data value.
 * @param data The integer value to be stored in the node.
 * @return A pointer to the newly created node.
 */
Node* createNode(int data);

/**
 * @brief Pushes an item onto the stack represented by the linked list.
 * @param top_ref A double pointer to the top of the stack.
 * @param data The integer value to be pushed onto the stack.
 * @return 1 if the push operation was successful.
 */
int push(Node **top_ref, int data);

/**
 * @brief Checks if the stack is empty.
 * @param top A pointer to the top of the stack.
 * @return 1 if the stack is empty, 0 otherwise.
 */
int isEmpty(Node *top);

/**
 * @brief Pops the top element from the stack.
 * @param top_ref A double pointer to the top of the stack.
 * @return The value of the popped element. If the stack is empty, returns INT_MIN.
 */
int pop(Node **top_ref);

/**
 * @brief Peeks at the top element of the stack without removing it.
 * @param top A pointer to the top of the stack.
 * @return The value of the top element. If the stack is empty, returns INT_MIN.
 */
int peek(Node *top);

/**
 * @brief Displays all elements in the stack.
 * @param top A pointer to the top of the stack.
 */
void display(Node *top);

/**
 * @brief Reverses the stack using two auxiliary stacks.
 * @param top_ref A double pointer to the top of the stack.
 */
void reverse(Node** top_ref);

/**
 * @brief Main function to drive the menu and stack operations.
 * @details It initializes two stacks and allows the user to perform various operations like push, pop, peek, display,
 *          switch between stacks, and reverse the stack.
 * @return 0 to indicate successful execution of the program.
 */
int main()
{
    Node *top1 = NULL; /**< Stack 1 */
    Node *top2 = NULL; /**< Stack 2 */
    Node **active = &top1; /**< Pointer to the active stack (default Stack 1) */
    int choice; /**< User choice for the menu */
    int value; /**< Value to be pushed or popped */
    int stackChoice; /**< Stack choice for switching between Stack 1 and Stack 2 */

    do
    {
        // Display the current active stack
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
            // Push element onto the current active stack
            printf("Enter element to be pushed: ");
            scanf("%d", &value);
            push(active, value);
            break;

        case 2:
            // Pop element from the current active stack
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
            // Peek the top element of the current active stack
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
            // Display all elements of the current active stack
            display(*active);
            break;

        case 5:
            // Switch between Stack 1 and Stack 2
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
            // Reverse the current active stack
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

/**
 * @brief Creates a new node with the given data value.
 * @param data The integer value to be stored in the node.
 * @return A pointer to the newly created node.
 */
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

/**
 * @brief Pushes a new node with data onto the stack.
 * @param top_ref A double pointer to the top of the stack.
 * @param data The data to be pushed onto the stack.
 * @return 1 if the push operation is successful.
 */
int push(Node **top_ref, int data)
{
    Node *new = createNode(data);
    new->link = *top_ref;
    *top_ref = new;
    return 1;
}

/**
 * @brief Pops the top node from the stack.
 * @param top_ref A double pointer to the top of the stack.
 * @return The data of the popped node. If the stack is empty, returns INT_MIN.
 */
int pop(Node **top_ref)
{
    if (*top_ref == NULL)
    {
        return INT_MIN; // Return INT_MIN if the stack is empty
    }
    int val = (*top_ref)->data;
    Node *temp = *top_ref;
    *top_ref = (*top_ref)->link;
    free(temp);
    return val;
}

/**
 * @brief Checks if the stack is empty.
 * @param top A pointer to the top of the stack.
 * @return 1 if the stack is empty, 0 otherwise.
 */
int isEmpty(Node *top)
{
    return top == NULL;
}

/**
 * @brief Peeks at the top element of the stack without removing it.
 * @param top A pointer to the top of the stack.
 * @return The value of the top element. If the stack is empty, returns INT_MIN.
 */
int peek(Node *top)
{
    if (isEmpty(top))
    {
        return INT_MIN; // Return INT_MIN if the stack is empty
    }
    return top->data;
}

/**
 * @brief Displays all elements of the stack.
 * @param top A pointer to the top of the stack.
 */
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

/**
 * @brief Reverses the stack using two auxiliary stacks.
 * @param top_ref A double pointer to the top of the stack.
 */
void reverse(Node** top_ref)
{
    if (*top_ref == NULL)
    {
        printf("Cannot reverse an empty Stack!\n");
        return;
    }

    Node* aux1 = NULL;
    Node* aux2 = NULL;

    // Transfer all elements from original stack to aux1
    while (*top_ref != NULL)
    {
        int value = pop(top_ref);
        push(&aux1, value);
    }

    // Transfer all elements from aux1 to aux2
    while (aux1 != NULL)
    {
        int value = pop(&aux1);
        push(&aux2, value);
    }

    // Transfer all elements from aux2 back to the original stack
    while (aux2 != NULL)
    {
        int value = pop(&aux2);
        push(top_ref, value);
    }

    printf("Reversed Successfully!\n");
}
