#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*
 * When pass on a NULL pointer, it will core dump?
*/

void passNULL(void *flag)
{
	if(flag)
		*(int *)flag = 1;
	else
		printf("Error: the flag should not NULL\n");
}

int main(int argc, char *argv[])
{
	int flag = 0;

	//passNULL(&flag);
	passNULL(NULL);

	printf("flag: %d\n", flag);

	return 0;
}
