/*
 * =====================================================================================
 *
 *       Filename:  VAL.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/07/15 17:34:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int VAL32(const void *_x)
{
	int y;
	char *p;
	const char *x;
	
	x = (char *)_x;
	p = (char *)&y;
	*p = *x;

	*(p+1) = *(x+1);
	*(p+2) = *(x+2);
	*(p+3) = *(x+3);

	return y;
}

int VAL16(const void *_x)
{
	int y;
	char *p;
	const char *x;
	
	x = (char *)_x;
	p = (char *)&y;
	*p = *x;

	*(p+1) = *(x+1);
	//*(p+2) = *(x+2);
	//*(p+3) = *(x+3);

	return y;
}

int main(int argc, char *argv[])
{
	int abc = 32;
	printf("val32: %d\n", VAL16((char *)&abc));	

	return 0;
}

