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
