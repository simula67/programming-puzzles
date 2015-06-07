#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char *sum_binary( char *num1, char *num2 )
{
	int num1_len = strlen(num1);
	int num2_len = strlen(num2);
	int result_len;
	if( num1_len > num2_len ) {
		result_len = num1_len + 1;
	} else {
		result_len = num2_len + 1;
	}
	char *result = ( char * )malloc( result_len );
	int i;
	for( i = 0;i < result_len - 1; i++ ) {
		result[i] = '0';
	}
	result[i] = '\0';
	int carry = 0;
	while(num1_len != 0 && num2_len != 0 ) {
		printf("num1 : %c num2 : %c carry : %d ", num1[num1_len-1], num2[num2_len-1], carry);
		if( num1[num1_len - 1] == '1' && num2[num2_len - 1] == '1' ) {
			if( carry == 1 ) {
				result[ i - 1 ] = '1';
			} else {
				carry = 1;
			}
		} else if (num1[num1_len - 1] == '1' || num2[num2_len - 1] == '1') {
			if( carry == 1 ) {
				carry = 0;
			}
			result [ i - 1 ] = '1';	
		} else {
			if( carry == 1 ) {
				carry = 0;
				result[ i - 1 ] = '1';
			}
		}
		printf(" result : %c\n", result[i-1]);
		i--;
		num1_len--;
		num2_len--;
	}
	while( num2_len > 0 ) {
		printf("num1 : %c num2 : %c carry : %d ", num1[num1_len-1], num2[num2_len-1], carry);
		if( carry == 0 )
			result[i -1] = num2[num2_len-1];
		else {
			if(num2[num2_len-1] == '0') {
				result[i-1] = '1';
				carry = 0;
			} else {
				result[i-1] = '0';
			}
		}
		printf(" result : %c\n", result[i-1]);
		i--;
		num2_len--;
	}
	while( num1_len > 0 ) {
		printf("Entering num1_loop\n");
		printf("num1 : %c num2 : %c carry : %d ", num1[num1_len-1], num2[num2_len-1], carry);
		if( carry == 0 )
			result[i -1] = num1[num1_len-1];
		else {
			if(num1[num1_len-1] == '0') {
				result[i-1] = '1';
				carry = 0;
			} else {
				result[i-1] = '0';
			}
		}
		printf(" result : %c\n", result[i-1]);
		i--;
		num1_len--;
	}
	if( carry == 1 )
		result [ i - 1 ] = '1';
	return result;	
}

int main()
{
	char *result = sum_binary( "0111101", "1101" );
	if(!strcmp( result, "1001010") )  {
		printf("PASSED\n");
	} else {
		printf("FAILED: %s\n", result);
	}
	free(result);
}
