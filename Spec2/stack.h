//jaden mardini - prog71990 - sec1 - student#8762993 
//all the work from <main.c>

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef STACK_H
#define STACK_H

//function declarations for stack operations
int full(void);        //checks if the stack is full
int empty(void);       //checks if the stack is empty
void push(char);       //pushes a character onto the stack
char pop(void);        //pops a character off the stack

#endif
