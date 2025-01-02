/**
 * @file main.c
 * @date 02-01-2025
 * 
 * @brief The program implements a menu-driven stack manipulation system that allows the user to 
 * perform various stack operations including pushing, popping, peeking, displaying the stack, 
 * switching between two stacks, and reversing the stack using two auxiliary stacks.
 * 
 * This program demonstrates basic stack operations such as push, pop, peek, display, 
 * switching between two stacks, and reversing the stack using auxiliary stacks.
 * 
 * @param cap The `cap` parameter represents the capacity of the stack, which is the maximum number 
 * of elements the stack can hold. It is used to initialize the stack with a specific capacity 
 * when creating a new stack structure.
 * 
 * @return The program returns 0 at the end of the main function, which indicates the successful 
 * execution of the program.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/** 
 * Structure representing a stack.
 */
struct Stack {
    int top;             /**< Index of the top element in the stack */
    unsigned capacity;   /**< Maximum number of elements the stack can hold */
    int* array;          /**< Pointer to the array holding the stack elements */
};

/**
 * @brief Initializes a new stack with the given capacity.
 * 
 * Allocates memory for the stack and its array of integers, and sets the 
 * initial values for top and capacity.
 * 
 * @param cap The capacity of the stack.
 * @return A pointer to the newly created stack.
 */
struct Stack* initializeStack(unsigned cap) {
    struct Stack* stack = malloc(sizeof(struct Stack));  // Allocate memory for the stack
    stack->capacity = cap;                               // Set the stack capacity
    stack->top = -1;                                     // Initialize top to -1 (empty stack)
    stack->array = malloc(stack->capacity * sizeof(int)); // Allocate memory for the stack array
    return stack;
}

/**
 * @brief Checks if the stack is full.
 * 
 * @param stack A pointer to the stack.
 * @return 1 if the stack is full, 0 otherwise.
 */
int isFull(struct Stack* stack) { 
    return stack->top == (signed int)stack->capacity - 1; 
}

/**
 * @brief Checks if the stack is empty.
 * 
 * @param stack A pointer to the stack.
 * @return 1 if the stack is empty, 0 otherwise.
 */
int isEmpty(struct Stack* stack) { 
    return stack->top == -1; 
} 

/**
 * @brief Pushes an item onto the stack.
 * 
 * This function adds an item to the top of the stack if the stack is not full.
 * 
 * @param stack A pointer to the stack.
 * @param item The item to be pushed onto the stack.
 */
void push(struct Stack* stack, int item) {
    if (isFull(stack)) {
        printf("Stack is Full\n");
        return;
    }
    stack->top++;                           // Increment the top index
    stack->array[stack->top] = item;        // Insert the item at the top of the stack
    printf("%d pushed to stack\n", item);   // Print the pushed item
}

/**
 * @brief Pops an item from the stack.
 * 
 * This function removes and returns the top item from the stack if it is not empty.
 * 
 * @param stack A pointer to the stack.
 * @return The popped item if the stack is not empty; otherwise, returns INT_MIN.
 */
int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is Empty\n");
        return INT_MIN;  // Return an indicator of an empty stack
    }
    int val = stack->array[stack->top];  // Retrieve the top item
    stack->top--;                        // Decrement the top index
    return val;                          // Return the popped item
}

/**
 * @brief Peeks at the top item of the stack without removing it.
 * 
 * @param stack A pointer to the stack.
 * @return The top item of the stack if the stack is not empty; otherwise, returns INT_MIN.
 */
int peek(struct Stack* stack) { 
    if (isEmpty(stack)) 
        return INT_MIN; 
    return stack->array[stack->top];  // Return the top item without removing it
}

/**
 * @brief Displays all the items in the stack.
 * 
 * This function prints all items in the stack from top to bottom.
 * 
 * @param stack A pointer to the stack.
 */
void display(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is Empty!\n");
        return;
    }
    printf("Stack elements:\n");
    for (int i = stack->top; i >= 0; i--) {
        printf("%d\n", stack->array[i]);  // Print each item from top to bottom
    }
}

/**
 * @brief Reverses the stack using two auxiliary stacks.
 * 
 * This function reverses the contents of the stack by using two auxiliary stacks.
 * It pops all elements from the original stack and transfers them into two auxiliary stacks
 * in a way that reverses the order of the elements.
 * 
 * @param stack A pointer to the stack to be reversed.
 */
void reverseStack(struct Stack* stack) {
    struct Stack* auxStack1 = initializeStack(stack->capacity);  // First auxiliary stack
    struct Stack* auxStack2 = initializeStack(stack->capacity);  // Second auxiliary stack

    // Transfer all elements from the original stack to auxStack1
    while (!isEmpty(stack)) {
        int item = pop(stack);
        push(auxStack1, item);
    }

    // Transfer all elements from auxStack1 to auxStack2
    while (!isEmpty(auxStack1)) {
        int item = pop(auxStack1);
        push(auxStack2, item);
    }

    // Transfer all elements from auxStack2 back to the original stack
    while (!isEmpty(auxStack2)) {
        int item = pop(auxStack2);
        push(stack, item);
    }

    // Free dynamically allocated memory for the auxiliary stacks
    free(auxStack1->array);
    free(auxStack1);
    free(auxStack2->array);
    free(auxStack2);

    printf("Stack has been reversed!\n");
}

/**
 * @brief Main function that drives the menu system for stack operations.
 * 
 * The main function provides a menu-driven interface to the user, allowing them to perform
 * various stack operations such as pushing, popping, peeking, displaying, switching between
 * two stacks, and reversing the stack. The program runs in a loop until the user chooses to exit.
 * 
 * @return 0 upon successful execution.
 */
int main() {
    unsigned capacity;
    printf("Enter the capacity of each stack: ");
    scanf("%u", &capacity);

    struct Stack* stack1 = initializeStack(capacity);  // Initialize stack1
    struct Stack* stack2 = initializeStack(capacity);  // Initialize stack2

    int choice, item, stackChoice = 1;  // Default to stack1

    do {
        printf("\nCurrent Stack: Stack %d\n", stackChoice);
        printf("Menu:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Switch Stack\n");
        printf("6. Reverse Stack\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        struct Stack* currentStack = (stackChoice == 1) ? stack1 : stack2;  // Select current stack

        switch (choice) {
            case 1:
                printf("Enter item to push: ");
                scanf("%d", &item);
                push(currentStack, item);
                break;
            case 2:
                item = pop(currentStack);
                if (item != INT_MIN) {
                    printf("%d popped from stack\n", item);
                }
                break;
            case 3:
                item = peek(currentStack);
                if (item != INT_MIN) {
                    printf("Top item is: %d\n", item);
                }
                break;
            case 4:
                display(currentStack);
                break;
            case 5:
                // Switch between stack1 and stack2
                stackChoice = (stackChoice == 1) ? 2 : 1;
                printf("Switched to Stack %d\n", stackChoice);
                break;
            case 6:
                reverseStack(currentStack);
                break;
            case 7:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 7);

    // Free dynamically allocated memory for stacks
    free(stack1->array);
    free(stack1);
    free(stack2->array);
    free(stack2);

    return 0;
}
