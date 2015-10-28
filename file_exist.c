#include <stdio.h>
#include <stdlib.h>

int file_exist(const char *file)
{
	if(access(file, 0) == 0)
		return 1;
	else
		return 0;
}


int main(int argc, char *argv[])
{
	if(file_exist(argv[1]) == 1)
		printf("file %s is exist\n", argv[1]);
	else
		printf("file %s is not exist\n", argv[1]);
	
	return 0;
}
		
