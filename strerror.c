#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int i = 0;
	char *str = NULL;

	printf("%m\n");
	printf("%s\n", strerror(errno));
	
	for(i = 0; i < 128; i++)
	{
		if((str = strerror(i)) != NULL)
			printf("%s\n", str);
			//can not use it here,because it is get the current value of strerror(errno) 
			//printf("%m\n");
	}


	return 0;
}
