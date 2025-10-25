/**
 * @file test_stacks.c
 * @brief Unit Tests for Stack Implementations
 * @author Jaden Mardini
 * 
 * Comprehensive unit tests for both dynamic and static stack implementations
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dynamic_stack.h"
#include "static_stack.h"

/* Test result tracking */
static int tests_run = 0;
static int tests_passed = 0;

/* Test macros */
#define TEST_ASSERT(condition, message) do { \
    tests_run++; \
    if (condition) { \
        tests_passed++; \
        printf("PASS: %s\n", message); \
    } else { \
        printf("FAIL: %s\n", message); \
    } \
} while(0)

#define TEST_SECTION(name) printf("\n=== %s ===\n", name)

/**
 * @brief Tests dynamic stack creation and destruction
 */
static void test_dynamic_stack_creation(void) {
    TEST_SECTION("Dynamic Stack Creation Tests");
    
    /* Test valid creation */
    Stack* stack = stack_create(100);
    TEST_ASSERT(stack != NULL, "Create stack with valid capacity");
    TEST_ASSERT(stack_capacity(stack) == 100, "Stack capacity is correct");
    TEST_ASSERT(stack_size(stack) == 0, "New stack is empty");
    TEST_ASSERT(stack_is_empty(stack), "New stack reports as empty");
    TEST_ASSERT(!stack_is_full(stack), "New stack is not full");
    
    stack_destroy(stack);
    
    /* Test invalid creation */
    Stack* invalid_stack = stack_create(0);
    TEST_ASSERT(invalid_stack == NULL, "Create stack with invalid capacity fails");
    
    invalid_stack = stack_create(STACK_MAX_CAPACITY + 1);
    TEST_ASSERT(invalid_stack == NULL, "Create stack with too large capacity fails");
}

/**
 * @brief Tests dynamic stack push operations
 */
static void test_dynamic_stack_push(void) {
    TEST_SECTION("Dynamic Stack Push Tests");
    
    Stack* stack = stack_create(3);
    TEST_ASSERT(stack != NULL, "Create test stack");
    
    /* Test normal push operations */
    StackResult result = stack_push(stack, 10);
    TEST_ASSERT(result == STACK_SUCCESS, "Push first element");
    TEST_ASSERT(stack_size(stack) == 1, "Stack size after first push");
    
    result = stack_push(stack, 20);
    TEST_ASSERT(result == STACK_SUCCESS, "Push second element");
    TEST_ASSERT(stack_size(stack) == 2, "Stack size after second push");
    
    result = stack_push(stack, 30);
    TEST_ASSERT(result == STACK_SUCCESS, "Push third element");
    TEST_ASSERT(stack_size(stack) == 3, "Stack size after third push");
    TEST_ASSERT(stack_is_full(stack), "Stack is full after filling");
    
    /* Test overflow */
    result = stack_push(stack, 40);
    TEST_ASSERT(result == STACK_ERROR_OVERFLOW, "Push to full stack fails");
    TEST_ASSERT(stack_size(stack) == 3, "Stack size unchanged after overflow");
    
    /* Test null pointer */
    result = stack_push(NULL, 50);
    TEST_ASSERT(result == STACK_ERROR_NULL_POINTER, "Push to null stack fails");
    
    stack_destroy(stack);
}

/**
 * @brief Tests dynamic stack pop operations
 */
static void test_dynamic_stack_pop(void) {
    TEST_SECTION("Dynamic Stack Pop Tests");
    
    Stack* stack = stack_create(3);
    TEST_ASSERT(stack != NULL, "Create test stack");
    
    /* Fill stack */
    stack_push(stack, 10);
    stack_push(stack, 20);
    stack_push(stack, 30);
    
    /* Test normal pop operations */
    int value;
    StackResult result = stack_pop(stack, &value);
    TEST_ASSERT(result == STACK_SUCCESS, "Pop from full stack");
    TEST_ASSERT(value == 30, "Popped value is correct (LIFO)");
    TEST_ASSERT(stack_size(stack) == 2, "Stack size after pop");
    
    result = stack_pop(stack, &value);
    TEST_ASSERT(result == STACK_SUCCESS, "Pop second element");
    TEST_ASSERT(value == 20, "Second popped value is correct");
    
    result = stack_pop(stack, &value);
    TEST_ASSERT(result == STACK_SUCCESS, "Pop last element");
    TEST_ASSERT(value == 10, "Last popped value is correct");
    TEST_ASSERT(stack_is_empty(stack), "Stack is empty after popping all");
    
    /* Test underflow */
    result = stack_pop(stack, &value);
    TEST_ASSERT(result == STACK_ERROR_UNDERFLOW, "Pop from empty stack fails");
    
    /* Test null pointers */
    result = stack_pop(NULL, &value);
    TEST_ASSERT(result == STACK_ERROR_NULL_POINTER, "Pop from null stack fails");
    
    stack_push(stack, 100);
    result = stack_pop(stack, NULL);
    TEST_ASSERT(result == STACK_ERROR_NULL_POINTER, "Pop with null value pointer fails");
    
    stack_destroy(stack);
}

/**
 * @brief Tests dynamic stack peek operations
 */
static void test_dynamic_stack_peek(void) {
    TEST_SECTION("Dynamic Stack Peek Tests");
    
    Stack* stack = stack_create(5);
    TEST_ASSERT(stack != NULL, "Create test stack");
    
    /* Test peek on empty stack */
    int value;
    StackResult result = stack_peek(stack, &value);
    TEST_ASSERT(result == STACK_ERROR_UNDERFLOW, "Peek empty stack fails");
    
    /* Test peek with values */
    stack_push(stack, 42);
    result = stack_peek(stack, &value);
    TEST_ASSERT(result == STACK_SUCCESS, "Peek with one element");
    TEST_ASSERT(value == 42, "Peek returns correct value");
    TEST_ASSERT(stack_size(stack) == 1, "Peek doesn't change stack size");
    
    stack_push(stack, 84);
    result = stack_peek(stack, &value);
    TEST_ASSERT(result == STACK_SUCCESS, "Peek with two elements");
    TEST_ASSERT(value == 84, "Peek returns top value");
    TEST_ASSERT(stack_size(stack) == 2, "Peek doesn't change stack size");
    
    stack_destroy(stack);
}

/**
 * @brief Tests static character stack operations
 */
static void test_static_stack_operations(void) {
    TEST_SECTION("Static Character Stack Tests");
    
    /* Clear stack */
    char_stack_clear();
    TEST_ASSERT(char_stack_is_empty(), "Stack is empty after clear");
    TEST_ASSERT(char_stack_size() == 0, "Stack size is zero after clear");
    
    /* Test push operations */
    CharStackResult result = char_stack_push('A');
    TEST_ASSERT(result == CHAR_STACK_SUCCESS, "Push first character");
    TEST_ASSERT(char_stack_size() == 1, "Stack size after first push");
    TEST_ASSERT(!char_stack_is_empty(), "Stack not empty after push");
    
    result = char_stack_push('B');
    TEST_ASSERT(result == CHAR_STACK_SUCCESS, "Push second character");
    
    /* Test peek */
    char c;
    result = char_stack_peek(&c);
    TEST_ASSERT(result == CHAR_STACK_SUCCESS, "Peek operation");
    TEST_ASSERT(c == 'B', "Peek returns correct character");
    TEST_ASSERT(char_stack_size() == 2, "Peek doesn't change size");
    
    /* Test pop operations */
    result = char_stack_pop(&c);
    TEST_ASSERT(result == CHAR_STACK_SUCCESS, "Pop operation");
    TEST_ASSERT(c == 'B', "Pop returns correct character (LIFO)");
    TEST_ASSERT(char_stack_size() == 1, "Stack size after pop");
    
    result = char_stack_pop(&c);
    TEST_ASSERT(result == CHAR_STACK_SUCCESS, "Pop last character");
    TEST_ASSERT(c == 'A', "Pop returns correct character");
    TEST_ASSERT(char_stack_is_empty(), "Stack empty after popping all");
    
    /* Test underflow */
    result = char_stack_pop(&c);
    TEST_ASSERT(result == CHAR_STACK_ERROR_UNDERFLOW, "Pop from empty stack fails");
}

/**
 * @brief Tests string reversal functionality
 */
static void test_string_reversal(void) {
    TEST_SECTION("String Reversal Tests");
    
    char output[256];
    CharStackResult result;
    
    /* Test simple string */
    result = char_stack_reverse_string("Hello", output, sizeof(output));
    TEST_ASSERT(result == CHAR_STACK_SUCCESS, "Reverse simple string");
    TEST_ASSERT(strcmp(output, "olleH") == 0, "Simple string reversed correctly");
    
    /* Test empty string */
    result = char_stack_reverse_string("", output, sizeof(output));
    TEST_ASSERT(result == CHAR_STACK_SUCCESS, "Reverse empty string");
    TEST_ASSERT(strcmp(output, "") == 0, "Empty string handled correctly");
    
    /* Test single character */
    result = char_stack_reverse_string("X", output, sizeof(output));
    TEST_ASSERT(result == CHAR_STACK_SUCCESS, "Reverse single character");
    TEST_ASSERT(strcmp(output, "X") == 0, "Single character handled correctly");
    
    /* Test palindrome */
    result = char_stack_reverse_string("racecar", output, sizeof(output));
    TEST_ASSERT(result == CHAR_STACK_SUCCESS, "Reverse palindrome");
    TEST_ASSERT(strcmp(output, "racecar") == 0, "Palindrome handled correctly");
    
    /* Test with numbers and symbols */
    result = char_stack_reverse_string("123!@#", output, sizeof(output));
    TEST_ASSERT(result == CHAR_STACK_SUCCESS, "Reverse mixed characters");
    TEST_ASSERT(strcmp(output, "#@!321") == 0, "Mixed characters reversed correctly");
    
    /* Test buffer too small */
    char small_buffer[3];
    result = char_stack_reverse_string("Hello", small_buffer, sizeof(small_buffer));
    TEST_ASSERT(result == CHAR_STACK_ERROR_INVALID_INPUT, "Small buffer handled correctly");
    
    /* Test null pointers */
    result = char_stack_reverse_string(NULL, output, sizeof(output));
    TEST_ASSERT(result == CHAR_STACK_ERROR_INVALID_INPUT, "Null input handled correctly");
    
    result = char_stack_reverse_string("Hello", NULL, sizeof(output));
    TEST_ASSERT(result == CHAR_STACK_ERROR_INVALID_INPUT, "Null output handled correctly");
}

/**
 * @brief Tests error handling and edge cases
 */
static void test_error_handling(void) {
    TEST_SECTION("Error Handling Tests");
    
    /* Test error string functions */
    const char* error_msg = stack_error_string(STACK_SUCCESS);
    TEST_ASSERT(error_msg != NULL, "Stack error string not null");
    TEST_ASSERT(strlen(error_msg) > 0, "Stack error string not empty");
    
    error_msg = char_stack_error_string(CHAR_STACK_SUCCESS);
    TEST_ASSERT(error_msg != NULL, "Char stack error string not null");
    TEST_ASSERT(strlen(error_msg) > 0, "Char stack error string not empty");
    
    /* Test stack operations with null pointers */
    TEST_ASSERT(stack_size(NULL) == 0, "Size of null stack is zero");
    TEST_ASSERT(stack_capacity(NULL) == 0, "Capacity of null stack is zero");
    TEST_ASSERT(stack_is_empty(NULL), "Null stack is considered empty");
    TEST_ASSERT(!stack_is_full(NULL), "Null stack is not considered full");
    
    StackResult result = stack_clear(NULL);
    TEST_ASSERT(result == STACK_ERROR_NULL_POINTER, "Clear null stack fails appropriately");
}

/**
 * @brief Main test runner
 */
int main(void) {
    printf("=== Stack ADT Unit Tests ===\n");
    printf("Author: Jaden Mardini\n");
    printf("Running comprehensive tests for stack implementations...\n");
    
    /* Run all test suites */
    test_dynamic_stack_creation();
    test_dynamic_stack_push();
    test_dynamic_stack_pop();
    test_dynamic_stack_peek();
    test_static_stack_operations();
    test_string_reversal();
    test_error_handling();
    
    /* Print test summary */
    printf("\n=== Test Summary ===\n");
    printf("Tests run: %d\n", tests_run);
    printf("Tests passed: %d\n", tests_passed);
    printf("Tests failed: %d\n", tests_run - tests_passed);
    printf("Success rate: %.1f%%\n", 
           tests_run > 0 ? (100.0 * tests_passed / tests_run) : 0.0);
    
    if (tests_passed == tests_run) {
        printf("\nAll tests PASSED! ✓\n");
        return EXIT_SUCCESS;
    } else {
        printf("\nSome tests FAILED! ✗\n");
        return EXIT_FAILURE;
    }
}
