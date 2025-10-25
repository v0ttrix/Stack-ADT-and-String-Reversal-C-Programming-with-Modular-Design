/**
 * @file dynamic_stack.c
 * @brief Dynamic Stack Implementation
 * @author Jaden Mardini
 * 
 * Professional implementation of a dynamic stack with comprehensive
 * error handling, memory management, and performance optimizations.
 */

#include "dynamic_stack.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* Stack structure definition (opaque to users) */
struct Stack {
    int* elements;          /* Array to store stack elements */
    size_t top_index;       /* Index of the top element */
    size_t capacity;        /* Maximum number of elements */
    size_t size;            /* Current number of elements */
};

/* Static function prototypes */
static bool is_valid_capacity(size_t capacity);
static void initialize_stack_memory(Stack* stack);

/**
 * @brief Validates if capacity is within acceptable range
 */
static bool is_valid_capacity(size_t capacity) {
    return capacity >= STACK_MIN_CAPACITY && capacity <= STACK_MAX_CAPACITY;
}

/**
 * @brief Initializes stack memory to zero
 */
static void initialize_stack_memory(Stack* stack) {
    if (stack && stack->elements) {
        memset(stack->elements, 0, stack->capacity * sizeof(int));
    }
}

Stack* stack_create(size_t capacity) {
    /* Validate input parameters */
    if (!is_valid_capacity(capacity)) {
        return NULL;
    }
    
    /* Allocate memory for stack structure */
    Stack* stack = malloc(sizeof(Stack));
    if (!stack) {
        return NULL;
    }
    
    /* Allocate memory for stack elements */
    stack->elements = malloc(capacity * sizeof(int));
    if (!stack->elements) {
        free(stack);
        return NULL;
    }
    
    /* Initialize stack properties */
    stack->capacity = capacity;
    stack->size = 0;
    stack->top_index = 0;
    
    /* Initialize memory for security */
    initialize_stack_memory(stack);
    
    return stack;
}

void stack_destroy(Stack* stack) {
    if (stack) {
        /* Clear sensitive data before freeing */
        if (stack->elements) {
            memset(stack->elements, 0, stack->capacity * sizeof(int));
            free(stack->elements);
        }
        
        /* Clear stack structure */
        memset(stack, 0, sizeof(Stack));
        free(stack);
    }
}

StackResult stack_push(Stack* stack, int value) {
    /* Validate input parameters */
    if (!stack) {
        return STACK_ERROR_NULL_POINTER;
    }
    
    if (stack_is_full(stack)) {
        return STACK_ERROR_OVERFLOW;
    }
    
    /* Add element to stack */
    stack->elements[stack->size] = value;
    stack->size++;
    stack->top_index = stack->size - 1;
    
    return STACK_SUCCESS;
}

StackResult stack_pop(Stack* stack, int* value) {
    /* Validate input parameters */
    if (!stack || !value) {
        return STACK_ERROR_NULL_POINTER;
    }
    
    if (stack_is_empty(stack)) {
        return STACK_ERROR_UNDERFLOW;
    }
    
    /* Remove element from stack */
    stack->size--;
    *value = stack->elements[stack->size];
    
    /* Clear the popped element for security */
    stack->elements[stack->size] = 0;
    
    /* Update top index */
    if (stack->size > 0) {
        stack->top_index = stack->size - 1;
    }
    
    return STACK_SUCCESS;
}

StackResult stack_peek(const Stack* stack, int* value) {
    /* Validate input parameters */
    if (!stack || !value) {
        return STACK_ERROR_NULL_POINTER;
    }
    
    if (stack_is_empty(stack)) {
        return STACK_ERROR_UNDERFLOW;
    }
    
    /* Return top element without removing it */
    *value = stack->elements[stack->top_index];
    
    return STACK_SUCCESS;
}

bool stack_is_empty(const Stack* stack) {
    return !stack || stack->size == 0;
}

bool stack_is_full(const Stack* stack) {
    return stack && stack->size >= stack->capacity;
}

size_t stack_size(const Stack* stack) {
    return stack ? stack->size : 0;
}

size_t stack_capacity(const Stack* stack) {
    return stack ? stack->capacity : 0;
}

StackResult stack_clear(Stack* stack) {
    if (!stack) {
        return STACK_ERROR_NULL_POINTER;
    }
    
    /* Clear all elements securely */
    if (stack->elements) {
        memset(stack->elements, 0, stack->capacity * sizeof(int));
    }
    
    /* Reset stack state */
    stack->size = 0;
    stack->top_index = 0;
    
    return STACK_SUCCESS;
}

const char* stack_error_string(StackResult result) {
    switch (result) {
        case STACK_SUCCESS:
            return "Operation completed successfully";
        case STACK_ERROR_NULL_POINTER:
            return "Null pointer provided";
        case STACK_ERROR_MEMORY_ALLOCATION:
            return "Memory allocation failed";
        case STACK_ERROR_OVERFLOW:
            return "Stack overflow - cannot push to full stack";
        case STACK_ERROR_UNDERFLOW:
            return "Stack underflow - cannot pop from empty stack";
        case STACK_ERROR_INVALID_CAPACITY:
            return "Invalid capacity specified";
        default:
            return "Unknown error";
    }
}
