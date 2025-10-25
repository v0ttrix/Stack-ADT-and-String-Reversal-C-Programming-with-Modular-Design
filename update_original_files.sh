#!/bin/bash

# Script to update original files with improved versions
# Author: Jaden Mardini

echo "=== Updating Original Files with Improvements ==="

# Update Spec1/main.c
cat > Spec1/main.c << 'EOF'
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
EOF

echo "Updated Spec1/main.c"

# Update Spec2/main.c
cat > Spec2/main.c << 'EOF'
/**
 * @file main.c
 * @brief Improved String Reversal Program
 * @author Jaden Mardini
 */

#include <stdio.h>
#include <string.h>
#include "../include/static_stack.h"

#define INPUT_BUFFER_SIZE 256

int main(void) {
    printf("=== Professional String Reversal Using Character Stack ===\n");
    printf("Author: Jaden Mardini\n\n");
    
    char input_buffer[INPUT_BUFFER_SIZE];
    
    printf("Enter a string (press Enter to reverse): ");
    if (!fgets(input_buffer, sizeof(input_buffer), stdin)) {
        fprintf(stderr, "Error: Failed to read input\n");
        return 1;
    }
    
    size_t length = strlen(input_buffer);
    if (length > 0 && input_buffer[length - 1] == '\n') {
        input_buffer[length - 1] = '\0';
    }
    
    if (strlen(input_buffer) == 0) {
        printf("No input provided. Exiting.\n");
        return 0;
    }
    
    char output_buffer[INPUT_BUFFER_SIZE];
    CharStackResult result = char_stack_reverse_string(input_buffer, output_buffer, sizeof(output_buffer));
    
    if (result == CHAR_STACK_SUCCESS) {
        printf("Original: \"%s\"\n", input_buffer);
        printf("Reversed: \"%s\"\n", output_buffer);
    } else {
        printf("Error: %s\n", char_stack_error_string(result));
    }
    
    return 0;
}
EOF

echo "Updated Spec2/main.c"

# Create compatibility headers
cat > Spec1/stack_utils.h << 'EOF'
#ifndef STACK_UTILS_H
#define STACK_UTILS_H

#include "../include/dynamic_stack.h"

typedef Stack* StackPtr;

#define initializeStack(size) stack_create(size)
#define pushToStack(stack, value) stack_push(stack, value)
#define isStackEmpty(stack) stack_is_empty(stack)
#define isStackFull(stack) stack_is_full(stack)
#define freeStack(stack) stack_destroy(stack)

static inline int popFromStack(Stack* stack) {
    int value = 0;
    StackResult result = stack_pop(stack, &value);
    return (result == STACK_SUCCESS) ? value : 0;
}

#endif
EOF

echo "Updated Spec1/stack_utils.h"

cat > Spec2/stack.h << 'EOF'
#ifndef STACK_H
#define STACK_H

#include "../include/static_stack.h"

#define full() char_stack_is_full()
#define empty() char_stack_is_empty()

static inline int push(char c) {
    return char_stack_push(c) == CHAR_STACK_SUCCESS ? 1 : 0;
}

static inline char pop(void) {
    char c = '\0';
    CharStackResult result = char_stack_pop(&c);
    return (result == CHAR_STACK_SUCCESS) ? c : '\0';
}

#endif
EOF

echo "Updated Spec2/stack.h"

cat > Spec2/stack.c << 'EOF'
#include "stack.h"
/* Implementation provided by static_stack.c */
EOF

echo "Updated Spec2/stack.c"

echo ""
echo "=== All files updated successfully ==="
