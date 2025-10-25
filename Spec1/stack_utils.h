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
