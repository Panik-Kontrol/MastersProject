#include <stdio.h>
#include<stdlib.h>
#include "stack.h"
#include "day3.h"

// contains the function definition to convert an expression into equivalent formula in CNF.

// authors: Prakhar Suryavansh	  	2017B4A71017H
//          Aman Badjate      	  	2017B3A70559H
//          Vinay Agarwal     	  	2017B3A70661H

// date: 08/11/2019

// Computes CNF for 'n1 V n2' where n1 and n2 should be in CNF.  
// n1 : Pointer to left operand (dataype : node *)
// n2 : Pointer to right operand (dataype : node *)
// node dataype is defined as
// typedef struct node
// {
//		char ch;  	
//   	struct node *left;
//		struct node *right;
// }node;
// return : root of the parse tree (dataype : node *)
node *distr(node *n1, node *n2)
{
	if(n1->ch == '^')
	{
		node *temp; // pointer to a node.
		temp = (node *)malloc(sizeof(node)); // dynamic memory allocation.
		
		temp->ch = '^';
		temp->left = distr(n1->left, n2);
		temp->right = distr(n1->right, n2);

		return temp;
	}
	else if(n2->ch == '^')
	{
		node *temp; // pointer to a node.
		temp = (node *)malloc(sizeof(node)); // dynamic memory allocation.
		
		temp->ch = '^';
		temp->left = distr(n1, n2->left);
		temp->right = distr(n1, n2->right);

		return temp;
	}
	else
	{
		node *temp; // pointer to a node.
		temp = (node *)malloc(sizeof(node)); // dynamic memory allocation.
		temp->ch = 'V';
		temp->left = n1;
		temp->right = n2;

		return temp;
	}
}

// Computes CNF.  
// root : Pointer to root of the parse tree (dataype : node *)
// return : root of the parse tree in CNF (dataype : node *)
node *cnf(node *root)
{
	if(root->ch == '^')
	{
		// cnf(phi1 ^ phi2): cnf(phi1) ^ cnf(phi2)
		root->left = cnf(root->left);
		root->right = cnf(root->right);
		return root;
	}
	else if(root->ch == 'V')
	{
		// cnf(phi1 V phi2): distr(cnf(phi1), cnf(phi2))
		return distr(cnf(root->left), cnf(root->right));
	}
	else
	{
		// cnf(phi): phi, phi is a literal
		return root;
	}
}
