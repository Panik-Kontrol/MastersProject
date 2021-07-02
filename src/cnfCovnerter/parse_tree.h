// contains functions to construct a parse tree and print the infix expression. 

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
void inorder(node *root);

// constructs the binary tree given a postfix expression. 
// post_exp : character array containing postfix expression.
// return : (node *) dataype - pointer to the root of the binary tree. 
node* parseTree(char post_exp[]);
