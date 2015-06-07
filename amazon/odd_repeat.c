#include <stdio.h>
#include <stdlib.h>

int elementRepeatedOddTimes( int *input, int size ) 
{
	int i;
	int *repeats = malloc( sizeof( int ) * size );
	int *numbers = malloc( sizeof( int ) * size );
	int current = 0;
	for ( i =0 ;i<size; i++ ) {
		int index = listContains( numbers, current, input[i] );
		if( index != -1 ) {
			repeats[index]++;
		} else {
			numbers[current] = input[i];
			repeats[current] = 1;
			current++;
		}
	}
	for( i = 0; i <=current; i++ ) {
		if(repeats[i]%2 == 1)
			printf("%d\n", numbers[i]);
	}
	free( repeats );
	free( numbers );
}

int listContains( int * haystack, int size, int needle )
{
	int i;
	for( i = 0; i < size; i++) {
		if(haystack[i] == needle)
			return i;
	}
	return -1;
}
int main()
{
int input[] = { 4, 7, 2, 2, 5, 3, 5, 7, 7, 3, 4, 5 };
elementRepeatedOddTimes( input , 12 );
}
