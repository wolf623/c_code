/* VAL16 is get the 16bit of number */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//return max value: (2^32-1)/2
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

//return max value: 2^16
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
	int abc = 65535;
	long long int def = 4294967295/2+1;
	printf("val16: %d\n", VAL16((char *)&abc));	
	printf("val32: %d\n", VAL32((char *)&def));	

	return 0;
}

