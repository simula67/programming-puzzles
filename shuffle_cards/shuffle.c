#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#define NUM_CARDS 52
#define SEED 30
static int *shuffle_cards(int *source,unsigned int seed,unsigned int  num_cards)
{
	int *dest = (int *)malloc(num_cards*sizeof(int));
	if(dest==NULL) {
		errno = ENOMEM;
		return NULL;
	}
	srand(seed);
	unsigned int i,to_shuffle,skip_empty;
	for(i=0;i<num_cards;i++) {
		dest[i]=INT_MIN;
	}
	for(to_shuffle=num_cards;to_shuffle!=0;to_shuffle--) {
		skip_empty = (rand()%to_shuffle); //Number of empty blocks that need to be skipped
		i=0;
		while(skip_empty!=0) {
			i++;
			if(dest[i-1]==INT_MIN)
				skip_empty--;
		}
		//Now skip until we find a free block to put the card
		while(dest[i]!=INT_MIN){
			i++;
		}
		//Now insert the card
		dest[i] = source[(to_shuffle-1)];
	}
	return dest;
}
int main(int argc,char *argv[])
{
	int cards[NUM_CARDS],i;
	int *shuffled;
	for(i=0;i<NUM_CARDS;i++) {
		cards[i] = i+1;
	}
	if( (shuffled = shuffle_cards(cards,SEED,NUM_CARDS)) == NULL ) {
		fprintf(stderr,"Failed to sort cards");
		exit(1);
	}
	printf("Sorted cards are : \n");
	for(i=0;i<NUM_CARDS;i++) {
		printf("%d\n",shuffled[i]);
	}
	free(shuffled);
	return 0;
}
