#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void multiplication(void)
{
	int i, j;
	for(i=1; i<10; i++)
	{
		for(j=1; j<=i; j++)
		{
			printf("%1d*%2d = %-4d", i, j, i*j);
		}
		printf("\n");
	}
}

int main(void)
{
	multiplication();

	return 0;
}
