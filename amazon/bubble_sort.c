#include <stdio.h>

void bubble_sort( int *input, int size )
{
	int i, j, temp;
	for( i = 0; i < size; i++ ) {
		for( j = 1; j < (size - i); j++ ) {
			if( input[j-1] > input [j] ) {
				temp = input[j];
				input[j] = input[j-1];
				input[j-1] = temp;
			}
		}
	}
}
int main()
{
	int input[] = { 1, 12, 2, 7, 87 };
	bubble_sort(input, 5 );
	int i;
	for( i = 0; i < 5; i++ ) {
		printf("%d ", input[i] );
	}
	printf("\n");
}
