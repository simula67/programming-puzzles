#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <limits.h>
#include "permute.h"
#include <string.h>
node * create_node(void)
{
  node *new_node;
  if( (new_node = (node *)malloc(sizeof(node))) == NULL ) {
    fprintf(stderr,"Not enough memmory\n");
    return NULL;
  }
  bzero(new_node,sizeof(node));
  return new_node;
}
child * create_childptr(void)
{
  child *new_child;
  if( (new_child = (child *)malloc(sizeof(child))) == NULL ) {
    fprintf(stderr,"Not enough memmory\n");
    return NULL;
  }
  bzero(new_child,sizeof(node));
  return new_child;
}


void insert_child(node *root,int *used,int value,int num_children,int *elements,int num_elements)
{
  int i;
  node *new_node;
  child *new_childptr;
  if( (new_node=create_node()) == NULL ) {
    fprintf(stderr,"Ran out of memory\n");
    exit(1);
  }
  if( (new_childptr=create_childptr()) == NULL ) {
    fprintf(stderr,"Ran out of memory\n");
    exit(1);
  }
  new_node->data=value;
  new_node->num_children=num_children;
  new_childptr->next_node=new_node;
  if(root->childlist==NULL) {
    root->childlist=new_childptr;
  }
  else {
    new_childptr->next=root->childlist;
    root->childlist=new_childptr;
  }
  for(i=0;i<num_elements;i++) {
    if(!used[i]) {
      used[i]=1;
      insert_child(root->childlist->next_node,used,elements[i],num_children-1,elements,num_elements);
      used[i]=0;
    }
  }
}
node *fill_permutTree(int *elements,int num_elements)
{
	int i;
	int *used;
	if( (used=malloc(num_elements*sizeof(int))) == NULL ) {
		fprintf(stderr,"Not enough memmory\n");
		return NULL;
	}
	bzero(used,num_elements*sizeof(int));
	node *root;
	if( (root=create_node()) == NULL ) {
		fprintf(stderr,"Ran out of memory\n");
		return NULL;
	}
	root->data=INT_MIN;
	root->num_children=num_elements;
	for(i=0;i<num_elements;i++) {
		used[i]=1;
		insert_child(root,used,elements[i],num_elements-1,elements,num_elements);
		used[i]=0;
	}
	return root;
}


void do_permute(node *root,int **space,int num_elements,int *level,int *top,int *stack)
{
  if(root->num_children>0) {
    child *childptr;
    for(childptr=root->childlist;childptr!=NULL;childptr=childptr->next) {
      stack[(*top)++]=childptr->next_node->data;
      do_permute(childptr->next_node,space,num_elements,level,top,stack);
    }
    (*top)--;
    //stack[*top]=0;
  }
  else {
    memcpy(space[*level],stack,num_elements*sizeof(int));
    (*top)--;
    //stack[*top]=0;
    (*level)++;
  }
}

void permut_fill(node *root,int **space,int num_elements)
{
  int i=0;
  int *stack;
  if( (stack = malloc(num_elements*sizeof(int))) == NULL ) {
    fprintf(stderr,"Ran out of memmory\n");
    exit(1);
  }
  int top=0;
  do_permute(root,space,num_elements,&i,&top,stack);
}
