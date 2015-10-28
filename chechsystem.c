#include <stdio.h>

/*
 * This API used for judge if the system is big_endian or small_endian
 * 0: small_endian, 1: big_endian
*/
int checksystem(void)
{
	union check
	{
		int i;
		char ch;
	}c;

	c.i = 1;

	return (c.ch == 1);
}

int main(int argc, char *argv[])
{
	if(checksystem)
		printf("It is big endian\n");
	else	
		printf("It is small endian\n");

	return 0;
}
