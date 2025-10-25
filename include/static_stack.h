/**
 * @file static_stack.h
 * @brief Static Character Stack Interface
 * @author Jaden Mardini
 * 
 * This header defines a static character stack implementation optimized
 * for string reversal operations with built-in safety checks.
 */

#ifndef STATIC_STACK_H
#define STATIC_STACK_H

#include <stdbool.h>
#include <stddef.h>

/* Constants */
#define CHAR_STACK_MAX_SIZE 256
#define CHAR_STACK_EMPTY_CHAR '\0'

/* Error codes for character stack operations */
typedef enum {
    CHAR_STACK_SUCCESS = 0,
    CHAR_STACK_ERROR_OVERFLOW,
    CHAR_STACK_ERROR_UNDERFLOW,
    CHAR_STACK_ERROR_INVALID_INPUT
} CharStackResult;

/**
 * @brief Pushes a character onto the stack
 * @param c Character to push
 * @return CHAR_STACK_SUCCESS on success, error code on failure
 */
CharStackResult char_stack_push(char c);

/**
 * @brief Pops a character from the stack
 * @param c Pointer to store the popped character
 * @return CHAR_STACK_SUCCESS on success, error code on failure
 */
CharStackResult char_stack_pop(char* c);

/**
 * @brief Peeks at the top character without removing it
 * @param c Pointer to store the top character
 * @return CHAR_STACK_SUCCESS on success, error code on failure
 */
CharStackResult char_stack_peek(char* c);

/**
 * @brief Checks if the character stack is empty
 * @return true if empty, false otherwise
 */
bool char_stack_is_empty(void);

/**
 * @brief Checks if the character stack is full
 * @return true if full, false otherwise
 */
bool char_stack_is_full(void);

/**
 * @brief Gets the current number of characters in the stack
 * @return Number of characters in the stack
 */
size_t char_stack_size(void);

/**
 * @brief Gets the maximum capacity of the character stack
 * @return Maximum capacity
 */
size_t char_stack_capacity(void);

/**
 * @brief Clears all characters from the stack
 * @return CHAR_STACK_SUCCESS on success
 */
CharStackResult char_stack_clear(void);

/**
 * @brief Converts error code to human-readable string
 * @param result Error code
 * @return String description of the error
 */
const char* char_stack_error_string(CharStackResult result);

/**
 * @brief Reverses a string using the character stack
 * @param input Input string to reverse
 * @param output Buffer to store reversed string (must be at least strlen(input)+1)
 * @param max_length Maximum length of output buffer
 * @return CHAR_STACK_SUCCESS on success, error code on failure
 */
CharStackResult char_stack_reverse_string(const char* input, char* output, size_t max_length);

#endif /* STATIC_STACK_H */
