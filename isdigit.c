#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int len = strlen(argv[1]);
	int i = 0;
	char mask[64];
	int index = 0;
	char string[64];

	if(len > 32)
	{
		printf("error, the max length is 32\n");
		return -1;
	}

	for(index=0; index<len; index++)
	{
		if(isxdigit(argv[1][index]) == 0)
		{
			printf("error: '%c' is not a hex character\n", argv[1][index]);
			return -1;
		}
		
		if(index == len-1)
		{
			string[i] = 0x30;
			i++;
		}

		string[i] = argv[1][index];
		if(index % 2 == 1 && index != len-1)
		{	
			i++;
			string[i] = ':';
		}
		
		i++;
	}

	string[i] = '\0';
	memcpy(mask, string, i+1);

	printf("mask: %s\n", mask);

	return 0;
}
