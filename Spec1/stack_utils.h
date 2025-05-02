//jaden mardini - prog71990 - sec1 - student#8762993 
//all the work from <main.c>

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//data structure for a stack
struct Stack
{
    int topIndex;         //tracks the current top element
    int* elements;        //array to store stack data
    unsigned maxSize;     //maximum number of elements allowed
};

//function to initialize a stack with a specific size
struct Stack* initializeStack(unsigned maxSize)
{
    struct Stack* newStack = (struct Stack*)malloc(sizeof(struct Stack));
    if (newStack == NULL) 
    { //check if malloc failed for the stack structure
        printf("error: memory allocation failed for the stack structure.\n");
        return NULL;
    }

    newStack->elements = (int*)malloc(maxSize * sizeof(int));
    if (newStack->elements == NULL) 
    { //check if malloc failed for the stack array
        printf("error: memory allocation failed for stack elements.\n");
        free(newStack); //free previously allocated memory
        return NULL;
    }

    newStack->maxSize = maxSize;
    newStack->topIndex = -1; //stack starts empty
    return newStack;
}

//function to determine if the stack is empty
int isStackEmpty(struct Stack* stack) 
{
    return stack->topIndex == -1;
}

//function to determine if the stack is full
int isStackFull(struct Stack* stack) 
{
    return stack->topIndex == (int)(stack->maxSize - 1);
}

//function to push an item onto the stack
void pushToStack(struct Stack* stack, int value)
{
    if (stack == NULL) 
    { //check for null stack
        printf("error: stack is null. cannot push %d.\n", value);
        return;
    }
    if (isStackFull(stack)) 
    {
        printf("error: stack overflow. cannot push %d.\n", value);
        return;
    }
    stack->elements[++stack->topIndex] = value;
    printf("pushed %d onto the stack\n", value);
}

//function to pop an item from the stack
int popFromStack(struct Stack* stack) {
    if (stack == NULL) 
    { //check for null stack
        printf("error: stack is null. cannot pop.\n");
        return INT_MIN;
    }
    if (isStackEmpty(stack))
    {
        printf("error: stack underflow. cannot pop.\n");
        return INT_MIN;
    }
    return stack->elements[stack->topIndex--];
}

//cleanup function to free stack memory
void freeStack(struct Stack* stack)
{
    if (stack != NULL) 
    {
        free(stack->elements); //free array
        free(stack);           //free stack structure
    }
}
