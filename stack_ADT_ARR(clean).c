#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Stack {
    int top;
    unsigned capacity;
    int* array;
};

struct Stack* initializeStack(unsigned cap) {
    struct Stack* stack = malloc(sizeof(struct Stack));
    stack->capacity = cap;
    stack->top = -1;
    stack->array = malloc(stack->capacity * sizeof(int));
    return stack;
}

int isFull(struct Stack* stack) { 
    return stack->top == (signed int)stack->capacity - 1; 
}

int isEmpty(struct Stack* stack) { 
    return stack->top == -1; 
} 

void push(struct Stack* stack, int item) {
    if (isFull(stack)) {
        printf("Stack is Full\n");
        return;
    }
    stack->top++;
    stack->array[stack->top] = item;
    printf("%d pushed to stack\n", item);
}

int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is Empty\n");
        return INT_MIN;
    }
    int val = stack->array[stack->top];
    stack->top--;
    return val;
}

int peek(struct Stack* stack) { 
    if (isEmpty(stack)) 
        return INT_MIN; 
    return stack->array[stack->top];
}

void display(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is Empty!\n");
        return;
    }
    printf("Stack elements:\n");
    for (int i = stack->top; i >= 0; i--) {
        printf("%d\n", stack->array[i]);
    }
}

void reverseStack(struct Stack* stack) {
    struct Stack* auxStack1 = initializeStack(stack->capacity);
    struct Stack* auxStack2 = initializeStack(stack->capacity);

    while (!isEmpty(stack)) {
        int item = pop(stack);
        push(auxStack1, item);
    }

    while (!isEmpty(auxStack1)) {
        int item = pop(auxStack1);
        push(auxStack2, item);
    }

    while (!isEmpty(auxStack2)) {
        int item = pop(auxStack2);
        push(stack, item);
    }

    free(auxStack1->array);
    free(auxStack1);
    free(auxStack2->array);
    free(auxStack2);

    printf("Stack has been reversed!\n");
}

int main() {
    unsigned capacity;
    printf("Enter the capacity of each stack: ");
    scanf("%u", &capacity);

    struct Stack* stack1 = initializeStack(capacity);
    struct Stack* stack2 = initializeStack(capacity);

    int choice, item, stackChoice = 1;

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

        struct Stack* currentStack = (stackChoice == 1) ? stack1 : stack2;

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

    free(stack1->array);
    free(stack1);
    free(stack2->array);
    free(stack2);

    return 0;
}
