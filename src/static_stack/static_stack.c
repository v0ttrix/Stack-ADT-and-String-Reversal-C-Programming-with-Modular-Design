/**
 * @file static_stack.c
 * @brief Static Character Stack Implementation
 * @author Jaden Mardini
 * 
 * Professional implementation of a static character stack with
 * comprehensive error handling and string reversal functionality.
 */

#include "static_stack.h"
#include <string.h>
#include <ctype.h>

/* Static stack structure */
typedef struct {
    char elements[CHAR_STACK_MAX_SIZE];  /* Array to store characters */
    size_t top_index;                    /* Index of top element */
    size_t size;                         /* Current number of elements */
} CharStack;

/* Global static stack instance */
static CharStack g_char_stack = { {0}, 0, 0 };

/* Static function prototypes */
static bool is_valid_character(char c);
static void clear_stack_memory(void);

/**
 * @brief Validates if character is acceptable for stack operations
 */
static bool is_valid_character(char c) {
    /* Accept all printable characters and common whitespace */
    return isprint(c) || c == ' ' || c == '\t';
}

/**
 * @brief Securely clears stack memory
 */
static void clear_stack_memory(void) {
    memset(g_char_stack.elements, 0, sizeof(g_char_stack.elements));
    g_char_stack.size = 0;
    g_char_stack.top_index = 0;
}

CharStackResult char_stack_push(char c) {
    /* Validate input */
    if (!is_valid_character(c)) {
        return CHAR_STACK_ERROR_INVALID_INPUT;
    }
    
    /* Check for overflow */
    if (char_stack_is_full()) {
        return CHAR_STACK_ERROR_OVERFLOW;
    }
    
    /* Add character to stack */
    g_char_stack.elements[g_char_stack.size] = c;
    g_char_stack.size++;
    g_char_stack.top_index = g_char_stack.size - 1;
    
    return CHAR_STACK_SUCCESS;
}

CharStackResult char_stack_pop(char* c) {
    /* Validate input parameter */
    if (!c) {
        return CHAR_STACK_ERROR_INVALID_INPUT;
    }
    
    /* Check for underflow */
    if (char_stack_is_empty()) {
        *c = CHAR_STACK_EMPTY_CHAR;
        return CHAR_STACK_ERROR_UNDERFLOW;
    }
    
    /* Remove character from stack */
    g_char_stack.size--;
    *c = g_char_stack.elements[g_char_stack.size];
    
    /* Clear the popped element for security */
    g_char_stack.elements[g_char_stack.size] = '\0';
    
    /* Update top index */
    if (g_char_stack.size > 0) {
        g_char_stack.top_index = g_char_stack.size - 1;
    }
    
    return CHAR_STACK_SUCCESS;
}

CharStackResult char_stack_peek(char* c) {
    /* Validate input parameter */
    if (!c) {
        return CHAR_STACK_ERROR_INVALID_INPUT;
    }
    
    /* Check for underflow */
    if (char_stack_is_empty()) {
        *c = CHAR_STACK_EMPTY_CHAR;
        return CHAR_STACK_ERROR_UNDERFLOW;
    }
    
    /* Return top character without removing it */
    *c = g_char_stack.elements[g_char_stack.top_index];
    
    return CHAR_STACK_SUCCESS;
}

bool char_stack_is_empty(void) {
    return g_char_stack.size == 0;
}

bool char_stack_is_full(void) {
    return g_char_stack.size >= CHAR_STACK_MAX_SIZE;
}

size_t char_stack_size(void) {
    return g_char_stack.size;
}

size_t char_stack_capacity(void) {
    return CHAR_STACK_MAX_SIZE;
}

CharStackResult char_stack_clear(void) {
    clear_stack_memory();
    return CHAR_STACK_SUCCESS;
}

const char* char_stack_error_string(CharStackResult result) {
    switch (result) {
        case CHAR_STACK_SUCCESS:
            return "Operation completed successfully";
        case CHAR_STACK_ERROR_OVERFLOW:
            return "Stack overflow - cannot push to full stack";
        case CHAR_STACK_ERROR_UNDERFLOW:
            return "Stack underflow - cannot pop from empty stack";
        case CHAR_STACK_ERROR_INVALID_INPUT:
            return "Invalid input parameter";
        default:
            return "Unknown error";
    }
}

CharStackResult char_stack_reverse_string(const char* input, char* output, size_t max_length) {
    /* Validate input parameters */
    if (!input || !output || max_length == 0) {
        return CHAR_STACK_ERROR_INVALID_INPUT;
    }
    
    /* Clear the stack before use */
    char_stack_clear();
    
    /* Calculate input length */
    size_t input_length = strlen(input);
    
    /* Check if output buffer is large enough */
    if (input_length >= max_length) {
        return CHAR_STACK_ERROR_INVALID_INPUT;
    }
    
    /* Check if input fits in stack */
    if (input_length > CHAR_STACK_MAX_SIZE) {
        return CHAR_STACK_ERROR_OVERFLOW;
    }
    
    /* Push all characters onto the stack */
    for (size_t i = 0; i < input_length; i++) {
        CharStackResult result = char_stack_push(input[i]);
        if (result != CHAR_STACK_SUCCESS) {
            char_stack_clear();  /* Clean up on error */
            return result;
        }
    }
    
    /* Pop all characters to create reversed string */
    size_t output_index = 0;
    char c;
    
    while (!char_stack_is_empty() && output_index < max_length - 1) {
        CharStackResult result = char_stack_pop(&c);
        if (result != CHAR_STACK_SUCCESS) {
            char_stack_clear();  /* Clean up on error */
            return result;
        }
        output[output_index++] = c;
    }
    
    /* Null-terminate the output string */
    output[output_index] = '\0';
    
    /* Clear the stack after use */
    char_stack_clear();
    
    return CHAR_STACK_SUCCESS;
}
