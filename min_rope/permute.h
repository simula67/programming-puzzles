#ifndef _PERMUT_H
#define _PERMUT_H
struct Node;
typedef struct Child {
  struct Node *next_node;
  struct Child *next;
}child;
typedef struct Node {
  int data;
  int num_children;
  child *childlist;
}node;
node *fill_permutTree(int *elements,int num_elements);
void permut_fill(node *root,int **space,int num_elements);
#endif
