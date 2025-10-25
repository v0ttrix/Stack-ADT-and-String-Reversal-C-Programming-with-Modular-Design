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
