#include <stdio.h>
#include "stack.h"

// contains all the funtion definitions for basic operations on the stack when the dataype is a pointer.

// authors: Prakhar Suryavansh	  	2017B4A71017H
//          Aman Badjate      	  	2017B3A70559H
//          Vinay Agarwal     	  	2017B3A70661H

// date: 08/11/2019

// stack : Array of pointers(to node).
// max : integer variable denoting maximum size of array.
// stackPointer : Integer variable which denotes the top index of the stack, -1 when the stack is empty.  
// (*stackPointer) = Pointer to the integer variable denoting top index.  
// Pointers have been used as the function will update the top index of the stack.
// value : Pointer to node dataype - root of the subtree to be pushed.

// used to insert a value into the stack.
// return : void
void push(node* stack[], int max, int *stackPointer, node* value)
{
    // Before pushing a value, checks if the stack is already full.
    if(isFull(stack, max, *stackPointer))
        printf("The stack is full. Character cannot be added.\n");
    else
    {
        *stackPointer -= -1; //Increments the stackPointer by 1.
        stack[*stackPointer] = value; //pushes the value to the top of the stack.
    }
}
 
// deletes the top value from stack and updates *stackPointer.
// return : void.
void pop(node* stack[], int max, int *stackPointer)
{
    // Before popping a value, checks if the stack is empty.
    if(isEmpty(stack, max, *stackPointer))
        printf("The stack is empty. Cannot pop character.\n");
    else
    {
        stack[*stackPointer] = NULL; // removes the element from the top of the stack.
        *stackPointer += -1; // decrements the stackPointer by 1.
    }
}
 
// to check whether stack is empty or not by the value of *stackPointer. 
// return : 1 when stack is empty and 0 when it isn't
int isEmpty(node* stack[], int max, int stackPointer)
{
    if(stackPointer == -1)
        return 1; // if the value of *stackPointer is -1, then stack is empty and hence returns 1.
    else
        return 0;
}
 
// checks whether stack is full or not. 
// return : 1 when stack is full and 0 when it isn't.
int isFull(node* stack[], int max, int stackPointer)
{
    if(stackPointer == max - 1)
        return 1; // if the value of *stackPointer is max - 1, then stack is full and hence returns 1.
    else
        return 0;
}
 
// gives the top element of the stack.
// return : Pointer to root of the subtree at the top of the stack.
node* top(node* stack[], int max, int stackPointer)
{
    // Before returning the top value, checks if the stack is empty.
    if(isEmpty(stack, max, stackPointer))
    {
        printf("The stack is empty.");
        return NULL;
    }
    else
        return stack[stackPointer]; // returns the pointer to root of the subtree of the stack.
}
