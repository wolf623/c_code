#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf("Usage: ./crypt <passwd> <salt>\n");
		return -1;
	}

	char *ptr = (char *)crypt(argv[1], argv[2]);

	printf("encrypt passwd: %s\n", ptr);
	
	ptr = (char *)crypt("", "bM");
	printf("abc encrypt passwd: %s\n", ptr);


	return 0;
}
