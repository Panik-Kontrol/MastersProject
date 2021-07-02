#include <stdio.h>
#include<stdlib.h>
#include "stack.h"
#include "day1.h"

// contains the function definition to make any propositional logic formula implication-free.

// authors: Prakhar Suryavansh	  	2017B4A71017H
//          Aman Badjate      	  	2017B3A70559H
//          Vinay Agarwal     	  	2017B3A70661H

// date: 08/11/2019

// Removes all implications from the parse tree.   
// root : Pointer to root of the parse tree(dataype : node *)
// node dataype is defined as
// typedef struct node
// {
//		char ch;  	
//   	struct node *left;
//		struct node *right;
// }node;
// return : root of the parse tree not containing any implication (dataype : node *)
node *impl_free(node *root)
{
	if(root->ch == '>')
	{
		// impl_free(a>b): impl_free(~a V b) 
		root->ch = 'V';
		
		node *temp; // pointer to a node.
		temp = (node *)malloc(sizeof(node)); // dynamic memory allocation.
		temp->ch = '~';
		temp->left = NULL;
		temp->right = root->left;

		root->left = temp;

		return impl_free(root);
	}

	else if(root->ch == '^')
	{
		// impl_free(a ^ b): impl_free(a) ^ impl_free(b)
		root->left = impl_free(root->left);
		root->right = impl_free(root->right);
		return root;
	}
	else if(root->ch == 'V')
	{
		// impl_free(a V b): impl_free(a) V impl_free(b)
		root->left = impl_free(root->left);
		root->right = impl_free(root->right);
		return root;
	}
	else if(root->ch == '~')
	{
		// impl_free(~a): ~impl_free(a)
		root->right = impl_free(root->right);
		return root;
	}
	else
	{
		// impl_free(a): a, a is an atom
		return root;
	}
}
