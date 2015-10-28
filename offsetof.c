#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _data_t
{
	int i;
	char ch;
	double d;
	unsigned int li;
	short s;
	char str[23];
	int data[23];
}data_t;

#define OFFSETOF(str, filed)	((unsigned int)&(filed) - (unsigned int)&(str))

int main(void)
{
	data_t d;
	printf("offsetof int: %d\n", OFFSETOF(d, d.i));
	printf("offsetof char: %d\n", OFFSETOF(d, d.ch));
	printf("offsetof double: %d\n", OFFSETOF(d, d.d));
	printf("offsetof unsigned int: %d\n", OFFSETOF(d, d.li));
	printf("offsetof short int: %d\n", OFFSETOF(d, d.s));
	printf("offsetof char[23]: %d\n", OFFSETOF(d, d.str));
	printf("offsetof int[23]: %d\n", OFFSETOF(d, d.data));

	return 0;
}
