/**
 * @file main.c
 * @brief Improved Dynamic Stack Interface Demonstration
 * @author Jaden Mardini
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/dynamic_stack.h"

#define VALUE_ONE 25
#define VALUE_TWO 50
#define VALUE_THREE 125
#define STACK_CAPACITY 500

static void demonstrate_stack_operations(void) {
    printf("=== Dynamic Stack Operations Demo ===\n");
    
    Stack* stack = stack_create(STACK_CAPACITY);
    if (!stack) {
        fprintf(stderr, "Error: Failed to create stack\n");
        return;
    }
    
    printf("Created stack with capacity: %zu\n", stack_capacity(stack));
    
    const int values[] = {VALUE_ONE, VALUE_TWO, VALUE_THREE};
    const size_t num_values = sizeof(values) / sizeof(values[0]);
    
    for (size_t i = 0; i < num_values; i++) {
        StackResult result = stack_push(stack, values[i]);
        if (result == STACK_SUCCESS) {
            printf("Pushed: %d (Stack size: %zu)\n", values[i], stack_size(stack));
        } else {
            printf("Failed to push %d: %s\n", values[i], stack_error_string(result));
        }
    }
    
    int popped_value;
    StackResult result = stack_pop(stack, &popped_value);
    if (result == STACK_SUCCESS) {
        printf("Popped value: %d\n", popped_value);
    } else {
        printf("Failed to pop: %s\n", stack_error_string(result));
    }
    
    stack_destroy(stack);
}

int main(void) {
    printf("=== Professional Dynamic Stack Implementation ===\n");
    printf("Author: Jaden Mardini\n\n");
    
    demonstrate_stack_operations();
    
    return EXIT_SUCCESS;
}
