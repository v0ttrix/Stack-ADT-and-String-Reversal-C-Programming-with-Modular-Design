//jaden mardini - prog71990 - sec1 - student#8762993 
//all the work for <stack.h>

#include "stack.h"
#define _CRT_SECURE_NO_WARNINGS
#define FULL_STACK 20
#define EMPTY_STACK -1

typedef struct
{
    int top;            //current top position of the stack
    char stack[FULL_STACK]; //array to store stack elements
} Stack;

//initialize a stack instance
static Stack myStack = { EMPTY_STACK, {0} };

//check if the stack is empty
int empty(void)
{
    return myStack.top == EMPTY_STACK;
}

//check if the stack is full
int full(void)
{
    return myStack.top + 1 == FULL_STACK;
}

//push a character onto the stack
void push(char c)
{
    if (!full())
    {
        myStack.stack[++myStack.top] = c;
    }
}

//pop a character off the stack
char pop(void)
{
    if (!empty())
    {
        return myStack.stack[myStack.top--];
    }
    return '\0'; //return a null character if the stack is empty
}
