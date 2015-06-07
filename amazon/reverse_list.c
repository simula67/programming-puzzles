#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
	int elem;
	struct Node *next;
} node;

node * reverse_list( node *head) {
	if( head == NULL)
		return NULL;
	else if (head->next == NULL){
		return head;
	} else {
		node *reversedHead = reverse_list(head->next);
		node *scan = reversedHead;
		while(scan->next !=NULL) {
			scan = scan->next;
		}
		scan->next = head;
		head->next = NULL;
		return reversedHead;
	}
}


int main() 
{
	node *first = malloc( sizeof(node) );
	first->elem = 1;
	node *second = malloc( sizeof(node) );
	second->elem = 2;
	first->next = second;
	node *third = malloc( sizeof(node) );
	third->elem = 3;
	second->next = third;
	third->next = NULL;
	node *reversed = reverse_list( first );
	while( reversed != NULL ) {
		printf("%d ", reversed->elem );
		reversed = reversed->next;
	}
	printf("\n");
	return 0;
}
