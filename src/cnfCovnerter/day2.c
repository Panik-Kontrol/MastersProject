#include <stdio.h>
#include<stdlib.h>
#include "stack.h"
#include "day2.h"

// contains the function definition to convert any implication free formula into an equivalent one in negation normal form.

// authors: Prakhar Suryavansh	  	2017B4A71017H
//          Aman Badjate      	  	2017B3A70559H
//          Vinay Agarwal     	  	2017B3A70661H

// date: 08/11/2019


// Computes Negation normal form.   
// root : Pointer to root of the parse tree(dataype : node *)
// node dataype is defined as
// typedef struct node
// {
//		char ch;  	
//   	struct node *left;
//		struct node *right;
// }node;
// return : root of the parse tree in Negation normal form(dataype : node *)
node *nnf(node *root)
{
	if(root->ch == '~')
	{
		if(root->right->ch == '~')
		{
			// nnf(~~phi): nnf(phi)
			return nnf(root->right->right);
		}
		else if((root->right->ch == '^') || (root->right->ch == 'V'))
		{
			node *temp1; // pointer to a node.
			temp1 = (node *)malloc(sizeof(node)); // dynamic memory allocation.
			temp1->ch = '~';
			temp1->left = NULL;
			temp1->right = root->right->left;

			node *temp2; // pointer to a node.
			temp2 = (node *)malloc(sizeof(node)); // dynamic memory allocation.
			temp2->ch = '~';
			temp2->left = NULL;
			temp2->right = root->right->right;

			if(root->right->ch == '^')
			{
				// nnf(~(phi1 ^ phi2)): nnf(~phi1) V nnf(~phi2)
				root->ch = 'V';
			}
			else
			{
				// nnf(~(phi1 V phi2)): nnf(~phi1) ^ nnf(~phi2)
				root->ch = '^';
			}

			root->left = nnf(temp1);
			root->right = nnf(temp2);
			
			return root;
		}
		else
		{
			// nnf(~p): ~p
			return root;
		}
	}
	else if((root->ch == '^') || (root->ch == 'V'))
	{
		// nnf(phi1 ^ phi2): nnf(phi1) ^ nnf(phi2)
		// nnf(phi1 V phi2): nnf(phi1) V nnf(phi2)
		root->left = nnf(root->left);
		root->right = nnf(root->right);
		return root;
	}
	else
	{
		// nnf(p): p
		return root;
	}
}
