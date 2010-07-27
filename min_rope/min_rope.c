#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "permute.h"
int fact(int num)
{
  if(num==0)
    return 1;
  else
    return ( num * fact(num-1) );
}
void fill_permut_ropes(int **permut_ropes,int *ropes,int num_ropes)
{
  node *permutTree=fill_permutTree(ropes,num_ropes);
  if(permutTree == NULL) {
    fprintf(stderr,"Cannot create permutation tree\n");
    exit(1);
  }
  permut_fill(permutTree,permut_ropes,num_ropes);
}
int *ropes,**permut_ropes,num_ropes;
void free_mem(void)
{
  int i,num_fact=fact(num_ropes);
  for(i=0;i<num_fact;i++) {
    free(permut_ropes[i]);
  }
  free(permut_ropes);
}
int main()
{
  int i,j,permut,rope_len,curr_length=0,totalcost,min_totalcost=INT_MAX,index=0;
  printf("Enter the number of ropes(MIN 2) : ");
  scanf("%d",&num_ropes);
  if ( num_ropes < 2 ) {
    fprintf(stderr,"Number of ropes cannot be less than 2");
    exit(1);
  }
  if ( (ropes = malloc( num_ropes * sizeof(int) )) ==NULL ) {
    fprintf(stderr,"Not enough memory\n");
    exit(1);
  }
  for(i=0;i<num_ropes;i++) {
    printf("Enter value for rope %d : ",i+1);
    scanf("%d",ropes+i);
  }
  permut = fact(num_ropes);
  if ( (permut_ropes = (int **)malloc( permut * sizeof(int *) )) == NULL ) {
    fprintf(stderr,"Not enough memory\n");
    free(ropes);
    exit(1);
  }
  for(i=0;i<permut;i++) {
    if ( (permut_ropes[i] = malloc(sizeof(int))) == NULL ) {
      for(j=0;j<i;j++)
	free(permut_ropes[i]);
      free(permut_ropes);
      fprintf(stderr,"Not enough memory\n");
      exit(1);
    }
  }
  atexit(free_mem);
  fill_permut_ropes(permut_ropes,ropes,num_ropes);
  for(i=0;i<permut;i++) {
    curr_length = permut_ropes[i][0]+permut_ropes[i][1];
    totalcost = curr_length;
    for(j=2;j<num_ropes;j++) {
      curr_length += permut_ropes[i][j];
      totalcost += curr_length;
    }
    if(totalcost<=min_totalcost) {
      min_totalcost = totalcost;
      index=i;
    }
  }
  printf("All possible permutations are : ");
  for(i=0;i<permut;i++) {
    printf("\n");
    for(j=0;j<num_ropes;j++) {
      printf("%d ",permut_ropes[i][j]);
    }
  }
  printf("\nThe sequence with minimum cost is : \n");
  for(i=0;i<num_ropes;i++) {
    printf("%d ",permut_ropes[index][i]);
  }
  printf("\nMinimum total cost is : %d\n",min_totalcost);
  return 0;
}






