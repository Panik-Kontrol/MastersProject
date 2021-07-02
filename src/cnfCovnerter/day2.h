// contains function to convert any implication free formula into an equivalent one in negation normal form. 

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
node *nnf(node *root);
