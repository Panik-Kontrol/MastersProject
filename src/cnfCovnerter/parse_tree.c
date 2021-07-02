#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "parse_tree.h"

// contains the functions to construct a parse tree and print the infix expression. 

// authors: Prakhar Suryavansh	  	2017B4A71017H
//          Aman Badjate      	  	2017B3A70559H
//          Vinay Agarwal     	  	2017B3A70661H

// date: 08/11/2019

// prints the infix expression via inorder traversal. 
// root : Pointer to root of the binary tree. (dataype : node *)
// node dataype is defined as
// typedef struct node
// {
//		char ch;  	
//   	struct node *left;
//		struct node *right;
// }node;
// return : void
void inorder(node *root)
{
	if(root == NULL) // recurse until NULL is reached
		return;
	if(!(root->left == NULL && root->right == NULL))
		printf("(");
	inorder(root->left); // recurse left
	printf("%c", root->ch); // print node
	inorder(root->right); // recurse right
	if(!(root->left == NULL && root->right == NULL))
		printf(")");
}

// constructs the binary tree given a postfix expression. 
// post_exp : character array containing postfix expression.
// return : (node *) dataype - pointer to the root of the binary tree.
node* parseTree(char post_exp[])
{
	int max = 100;
	// Initialize stack to store pointers to a node.
	node* stack[max];
	//Initialize the pointer to point to -1 as it is empty.
	int stackPointer = -1;
	// loop to scan the postfix expression from left to right.
	for(int i = 0; i < strlen(post_exp); i++)
	{
		// if the scanned character is binary operator, 
		// pop two values from stack, make them its right & left child, respectively and push current node into the stack.
		if(post_exp[i] == 'V' || post_exp[i] == '^' || post_exp[i] == '>') 
		{
			node* r = top(stack, max, stackPointer);
			pop(stack, max, &stackPointer);
			node* l = top(stack, max, stackPointer);
			pop(stack, max, &stackPointer);
			node *value; // pointer to a node.
			value = (node *)malloc(sizeof(node)); // dynamic memory allocation.
			value->ch = post_exp[i];
			value->left = l;
			value->right = r;
			push(stack, max, &stackPointer, value);
		}
		// if the scanned character is unary operator, 
		// pop one value from stack, make it its right child and push current node into the stack.
		else if(post_exp[i] == '~')
		{
			node* r = top(stack, max, stackPointer);
			pop(stack, max, &stackPointer);
			node *value; // pointer to a node.
			value = (node *)malloc(sizeof(node)); // dynamic memory allocation.
			value->ch = post_exp[i];
			value->right = r;
			value->left = NULL;
			push(stack, max, &stackPointer, value);
		}
		// if the scanned character is an operand, push it into the stack.
		else 
		{
			node *value; // pointer to a node.
			value = (node *)malloc(sizeof(node)); // dynamic memory allocation.
			value->ch = post_exp[i];
			value->left = NULL;
			value->right = NULL;
			push(stack, max, &stackPointer, value);
		}
	}
	return stack[0]; // At the end only element of stack will be root of expression tree, return it.
}
