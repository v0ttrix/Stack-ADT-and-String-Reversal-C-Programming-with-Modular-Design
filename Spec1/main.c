//jaden mardini - prog71990 - sec1 - student#8762993 
//a C programming interface for a stack
//the list. Items are said to be “pushed onto” the top of the stack and to be “popped off” the stack.Therefore, the stack
//is a LIFO structure(that is, last in, first out)

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "stack_utils.h"
#include <limits.h>

//constants representing values to be pushed onto the stack
#define VALUE_ONE 25    //first value to push
#define VALUE_TWO 50    //second value to push
#define VALUE_THREE 125 //third value to push

int main(void)
{
    //create a stack with a maximum size of 500 elements
    struct Stack* myStack = initializeStack(500);

    //push predefined values onto the stack
    pushToStack(myStack, VALUE_ONE);
    pushToStack(myStack, VALUE_TWO);
    pushToStack(myStack, VALUE_THREE);

    //retrieve and display the top value after popping
    int poppedValue = popFromStack(myStack);
    printf("popped value: %d\n", poppedValue);

    return 0;
}

