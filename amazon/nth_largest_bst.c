#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int element;
	struct Node *left;
	struct Node *right;
} node;
int the_n;
void preorder( node *root)
{
	if( root == NULL) {
		return;
	}
	preorder(root->left);
	if(the_n==1) {
		printf("nth largest is : %d\n", root->element);
		exit(0);
	}
	the_n--;
	preorder(root->right);
}

void nthLargestBst( node *root, int n )
{
	the_n = n;
	preorder( root );
}

int main()
{
	node *root =  malloc( sizeof(node) );
	root->element = 5;
        node *child1 =  malloc( sizeof(node) );
	child1->element = 3;
	child1->left = NULL;
	child1->right = NULL;
	root->left = child1;
	root->right = NULL;
	nthLargestBst( root , 2 );
	return 0;	
}
