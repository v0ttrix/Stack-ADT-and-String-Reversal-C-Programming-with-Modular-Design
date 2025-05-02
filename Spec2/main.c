//jaden mardini - prog71990 - sec1 - student#8762993 

//a program that asks the user to input a string.The program then should
//push the characters of the string onto a stack(of characters), one by one, and
//then pop the characters from the stack and display them.This results in
//displaying the string in reverse order

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "stack.h"

int main(void)
{
    char inputChar;

    printf("enter a string (press enter to reverse):\n");

    //push characters onto the stack
    while ((inputChar = getchar()) != '\n')
    {
        if (!full()) {
            push(inputChar);
        }
        else {
            printf("error: stack is full. cannot push '%c'.\n", inputChar);
            break;
        }
    }

    printf("reversed string:\n");

    //pop and print characters from the stack
    while (!empty())
    {
        printf("%c", pop());
    }

    printf("\n");
    return 0;
}
