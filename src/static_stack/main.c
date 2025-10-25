/**
 * @file main.c
 * @brief String Reversal Demonstration Program
 * @author Jaden Mardini
 * 
 * Professional demonstration of string reversal using a static character stack
 * with comprehensive input validation and error handling.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "static_stack.h"

/* Constants */
#define INPUT_BUFFER_SIZE 512
#define OUTPUT_BUFFER_SIZE 512
#define MAX_LINE_LENGTH 80

/**
 * @brief Safely reads a line of input from the user
 * @param buffer Buffer to store the input
 * @param buffer_size Size of the buffer
 * @param prompt Message to display to user
 * @return true if input was read successfully, false otherwise
 */
static bool read_line(char* buffer, size_t buffer_size, const char* prompt) {
    printf("%s", prompt);
    
    if (!fgets(buffer, (int)buffer_size, stdin)) {
        return false;
    }
    
    /* Remove trailing newline if present */
    size_t length = strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
    }
    
    return true;
}

/**
 * @brief Validates input string for stack operations
 * @param input String to validate
 * @return true if valid, false otherwise
 */
static bool validate_input(const char* input) {
    if (!input) {
        return false;
    }
    
    size_t length = strlen(input);
    
    /* Check length constraints */
    if (length == 0) {
        printf("Error: Empty string provided.\n");
        return false;
    }
    
    if (length > char_stack_capacity()) {
        printf("Error: String too long (max %zu characters).\n", 
               char_stack_capacity());
        return false;
    }
    
    return true;
}

/**
 * @brief Demonstrates manual character-by-character reversal
 * @param input Input string to reverse
 */
static void demonstrate_manual_reversal(const char* input) {
    printf("\n=== Manual Character-by-Character Reversal ===\n");
    printf("Original string: \"%s\"\n", input);
    
    /* Clear the stack */
    char_stack_clear();
    
    /* Push characters one by one */
    printf("\nPushing characters onto stack:\n");
    size_t length = strlen(input);
    
    for (size_t i = 0; i < length; i++) {
        CharStackResult result = char_stack_push(input[i]);
        if (result == CHAR_STACK_SUCCESS) {
            printf("  Pushed: '%c' (Stack size: %zu)\n", 
                   input[i], char_stack_size());
        } else {
            printf("  Failed to push '%c': %s\n", 
                   input[i], char_stack_error_string(result));
            return;
        }
    }
    
    /* Pop characters to create reversed string */
    printf("\nPopping characters from stack:\n");
    printf("Reversed string: \"");
    
    char c;
    while (!char_stack_is_empty()) {
        CharStackResult result = char_stack_pop(&c);
        if (result == CHAR_STACK_SUCCESS) {
            printf("%c", c);
        } else {
            printf("\nError popping character: %s\n", 
                   char_stack_error_string(result));
            return;
        }
    }
    
    printf("\"\n");
}

/**
 * @brief Demonstrates automatic string reversal function
 * @param input Input string to reverse
 */
static void demonstrate_automatic_reversal(const char* input) {
    printf("\n=== Automatic String Reversal Function ===\n");
    printf("Original string: \"%s\"\n", input);
    
    char output[OUTPUT_BUFFER_SIZE];
    CharStackResult result = char_stack_reverse_string(input, output, sizeof(output));
    
    if (result == CHAR_STACK_SUCCESS) {
        printf("Reversed string: \"%s\"\n", output);
    } else {
        printf("Error reversing string: %s\n", char_stack_error_string(result));
    }
}

/**
 * @brief Displays stack statistics and information
 */
static void display_stack_info(void) {
    printf("\n=== Stack Information ===\n");
    printf("Stack capacity: %zu characters\n", char_stack_capacity());
    printf("Current size: %zu characters\n", char_stack_size());
    printf("Empty: %s\n", char_stack_is_empty() ? "Yes" : "No");
    printf("Full: %s\n", char_stack_is_full() ? "Yes" : "No");
    
    if (!char_stack_is_empty()) {
        char top_char;
        CharStackResult result = char_stack_peek(&top_char);
        if (result == CHAR_STACK_SUCCESS) {
            printf("Top character: '%c'\n", top_char);
        }
    }
}

/**
 * @brief Interactive mode for string reversal
 */
static void interactive_mode(void) {
    printf("\n=== Interactive String Reversal Mode ===\n");
    printf("Enter strings to reverse (type 'quit' to exit)\n");
    
    char input[INPUT_BUFFER_SIZE];
    
    while (true) {
        if (!read_line(input, sizeof(input), "\nEnter string: ")) {
            break;
        }
        
        /* Check for quit command */
        if (strcmp(input, "quit") == 0) {
            break;
        }
        
        /* Validate and process input */
        if (validate_input(input)) {
            demonstrate_automatic_reversal(input);
            display_stack_info();
        }
    }
}

/**
 * @brief Demonstrates various test cases
 */
static void run_test_cases(void) {
    printf("\n=== Test Cases ===\n");
    
    const char* test_strings[] = {
        "Hello",
        "World!",
        "12345",
        "A man a plan a canal Panama",
        "racecar",
        "The quick brown fox"
    };
    
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        printf("\nTest %zu:\n", i + 1);
        demonstrate_automatic_reversal(test_strings[i]);
    }
}

/**
 * @brief Main program entry point
 */
int main(void) {
    printf("=== String Reversal Using Character Stack ===\n");
    printf("Author: Jaden Mardini\n");
    printf("A professional C implementation demonstrating stack-based string reversal\n");
    
    /* Display initial stack information */
    display_stack_info();
    
    /* Run predefined test cases */
    run_test_cases();
    
    /* Get user input for demonstration */
    char input[INPUT_BUFFER_SIZE];
    
    if (read_line(input, sizeof(input), 
                  "\nEnter a string to reverse (or press Enter for interactive mode): ")) {
        
        if (strlen(input) > 0) {
            /* Single string demonstration */
            if (validate_input(input)) {
                demonstrate_manual_reversal(input);
                demonstrate_automatic_reversal(input);
            }
        } else {
            /* Interactive mode */
            interactive_mode();
        }
    }
    
    /* Final cleanup and display */
    char_stack_clear();
    printf("\nFinal stack state:\n");
    display_stack_info();
    
    printf("\nThank you for using the String Reversal Demo!\n");
    return EXIT_SUCCESS;
}
