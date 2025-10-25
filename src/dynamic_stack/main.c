/**
 * @file main.c
 * @brief Dynamic Stack Demonstration Program
 * @author Jaden Mardini
 * 
 * Professional demonstration of dynamic stack operations with
 * comprehensive error handling and user interaction.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "dynamic_stack.h"

/* Constants for demonstration */
#define DEMO_STACK_CAPACITY 10
#define DEMO_VALUES_COUNT 5
#define INPUT_BUFFER_SIZE 256

/* Demo values to push onto the stack */
static const int DEMO_VALUES[] = {25, 50, 75, 100, 125};



/**
 * @brief Demonstrates basic stack operations
 * @param stack Pointer to the stack
 */
static void demonstrate_basic_operations(Stack* stack) {
    printf("\n=== Basic Stack Operations Demo ===\n");
    
    /* Push demo values */
    printf("\nPushing values onto the stack:\n");
    for (size_t i = 0; i < DEMO_VALUES_COUNT; i++) {
        StackResult result = stack_push(stack, DEMO_VALUES[i]);
        if (result == STACK_SUCCESS) {
            printf("  Pushed: %d (Stack size: %zu)\n", 
                   DEMO_VALUES[i], stack_size(stack));
        } else {
            printf("  Failed to push %d: %s\n", 
                   DEMO_VALUES[i], stack_error_string(result));
        }
    }
    
    /* Display stack status */
    printf("\nStack status:\n");
    printf("  Size: %zu/%zu\n", stack_size(stack), stack_capacity(stack));
    printf("  Empty: %s\n", stack_is_empty(stack) ? "Yes" : "No");
    printf("  Full: %s\n", stack_is_full(stack) ? "Yes" : "No");
    
    /* Peek at top value */
    int peek_value;
    StackResult peek_result = stack_peek(stack, &peek_value);
    if (peek_result == STACK_SUCCESS) {
        printf("  Top value (peek): %d\n", peek_value);
    }
    
    /* Pop values */
    printf("\nPopping values from the stack:\n");
    int popped_value;
    while (!stack_is_empty(stack)) {
        StackResult result = stack_pop(stack, &popped_value);
        if (result == STACK_SUCCESS) {
            printf("  Popped: %d (Stack size: %zu)\n", 
                   popped_value, stack_size(stack));
        } else {
            printf("  Failed to pop: %s\n", stack_error_string(result));
            break;
        }
    }
}

/**
 * @brief Interactive stack operations
 * @param stack Pointer to the stack
 */
static void interactive_operations(Stack* stack) {
    printf("\n=== Interactive Stack Operations ===\n");
    printf("Commands: push <value>, pop, peek, size, clear, quit\n");
    
    char command[INPUT_BUFFER_SIZE];
    int value;
    
    while (true) {
        printf("\nStack> ");
        
        if (!fgets(command, sizeof(command), stdin)) {
            break;
        }
        
        /* Parse command */
        if (strncmp(command, "push", 4) == 0) {
            if (sscanf(command + 4, "%d", &value) == 1) {
                StackResult result = stack_push(stack, value);
                if (result == STACK_SUCCESS) {
                    printf("Pushed %d. Stack size: %zu\n", value, stack_size(stack));
                } else {
                    printf("Error: %s\n", stack_error_string(result));
                }
            } else {
                printf("Usage: push <integer_value>\n");
            }
        }
        else if (strncmp(command, "pop", 3) == 0) {
            StackResult result = stack_pop(stack, &value);
            if (result == STACK_SUCCESS) {
                printf("Popped %d. Stack size: %zu\n", value, stack_size(stack));
            } else {
                printf("Error: %s\n", stack_error_string(result));
            }
        }
        else if (strncmp(command, "peek", 4) == 0) {
            StackResult result = stack_peek(stack, &value);
            if (result == STACK_SUCCESS) {
                printf("Top value: %d\n", value);
            } else {
                printf("Error: %s\n", stack_error_string(result));
            }
        }
        else if (strncmp(command, "size", 4) == 0) {
            printf("Stack size: %zu/%zu\n", stack_size(stack), stack_capacity(stack));
        }
        else if (strncmp(command, "clear", 5) == 0) {
            StackResult result = stack_clear(stack);
            if (result == STACK_SUCCESS) {
                printf("Stack cleared.\n");
            } else {
                printf("Error: %s\n", stack_error_string(result));
            }
        }
        else if (strncmp(command, "quit", 4) == 0) {
            break;
        }
        else {
            printf("Unknown command. Available: push, pop, peek, size, clear, quit\n");
        }
    }
}

/**
 * @brief Main program entry point
 */
int main(void) {
    printf("=== Dynamic Stack Demonstration ===\n");
    printf("Author: Jaden Mardini\n");
    printf("A professional C implementation of a dynamic stack ADT\n");
    
    /* Create stack with demo capacity */
    Stack* stack = stack_create(DEMO_STACK_CAPACITY);
    if (!stack) {
        fprintf(stderr, "Error: Failed to create stack\n");
        return EXIT_FAILURE;
    }
    
    printf("\nCreated stack with capacity: %zu\n", stack_capacity(stack));
    
    /* Run demonstrations */
    demonstrate_basic_operations(stack);
    
    /* Ask user if they want interactive mode */
    printf("\nWould you like to try interactive mode? (y/n): ");
    char response = getchar();
    
    if (response == 'y' || response == 'Y') {
        /* Clear input buffer */
        while (getchar() != '\n');
        interactive_operations(stack);
    }
    
    /* Cleanup */
    stack_destroy(stack);
    
    printf("\nThank you for using the Dynamic Stack Demo!\n");
    return EXIT_SUCCESS;
}
