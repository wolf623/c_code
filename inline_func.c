#include <stdio.h>

static inline char *printstr(int abc)
{
	return (abc%2 > 0) ? "abc" : "123";
}

int main(int argc, char *argv[])
{
	int i;

	for(i=0; i<100; i++)
		fprintf(stdout, "%s\n", printstr(i));

	return 0;
}
	
