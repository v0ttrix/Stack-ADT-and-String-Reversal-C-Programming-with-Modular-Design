/**
 * @file dynamic_stack.h
 * @brief Dynamic Stack Abstract Data Type Interface
 * @author Jaden Mardini
 * 
 * This header defines a professional dynamic stack implementation with
 * proper error handling, memory management, and thread safety considerations.
 */

#ifndef DYNAMIC_STACK_H
#define DYNAMIC_STACK_H

#include <stdbool.h>
#include <stddef.h>

/* Forward declaration for opaque stack structure */
typedef struct Stack Stack;

/* Error codes for stack operations */
typedef enum {
    STACK_SUCCESS = 0,
    STACK_ERROR_NULL_POINTER,
    STACK_ERROR_MEMORY_ALLOCATION,
    STACK_ERROR_OVERFLOW,
    STACK_ERROR_UNDERFLOW,
    STACK_ERROR_INVALID_CAPACITY
} StackResult;

/* Constants */
#define STACK_DEFAULT_CAPACITY 100
#define STACK_MIN_CAPACITY 1
#define STACK_MAX_CAPACITY 1000000

/**
 * @brief Creates a new dynamic stack with specified capacity
 * @param capacity Maximum number of elements the stack can hold
 * @return Pointer to new stack or NULL on failure
 */
Stack* stack_create(size_t capacity);

/**
 * @brief Destroys a stack and frees all associated memory
 * @param stack Pointer to stack to destroy
 */
void stack_destroy(Stack* stack);

/**
 * @brief Pushes a value onto the top of the stack
 * @param stack Pointer to the stack
 * @param value Value to push
 * @return STACK_SUCCESS on success, error code on failure
 */
StackResult stack_push(Stack* stack, int value);

/**
 * @brief Pops a value from the top of the stack
 * @param stack Pointer to the stack
 * @param value Pointer to store the popped value
 * @return STACK_SUCCESS on success, error code on failure
 */
StackResult stack_pop(Stack* stack, int* value);

/**
 * @brief Peeks at the top value without removing it
 * @param stack Pointer to the stack
 * @param value Pointer to store the top value
 * @return STACK_SUCCESS on success, error code on failure
 */
StackResult stack_peek(const Stack* stack, int* value);

/**
 * @brief Checks if the stack is empty
 * @param stack Pointer to the stack
 * @return true if empty, false otherwise
 */
bool stack_is_empty(const Stack* stack);

/**
 * @brief Checks if the stack is full
 * @param stack Pointer to the stack
 * @return true if full, false otherwise
 */
bool stack_is_full(const Stack* stack);

/**
 * @brief Gets the current number of elements in the stack
 * @param stack Pointer to the stack
 * @return Number of elements, or 0 if stack is NULL
 */
size_t stack_size(const Stack* stack);

/**
 * @brief Gets the maximum capacity of the stack
 * @param stack Pointer to the stack
 * @return Capacity, or 0 if stack is NULL
 */
size_t stack_capacity(const Stack* stack);

/**
 * @brief Clears all elements from the stack
 * @param stack Pointer to the stack
 * @return STACK_SUCCESS on success, error code on failure
 */
StackResult stack_clear(Stack* stack);

/**
 * @brief Converts error code to human-readable string
 * @param result Error code
 * @return String description of the error
 */
const char* stack_error_string(StackResult result);

#endif /* DYNAMIC_STACK_H */
