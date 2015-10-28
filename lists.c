#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int len = strlen(argv[1]);
	printf("len: %d\n", len);

	int index = 0;
	int i = 0;
	char strings[15];
	char view_mask[15];

	if(len > 10)
	{
		printf("Error: the length should not bigger than 10\n");
		return -1;
	}

	if(len % 2 == 0)
	{
		for(index=0; index<len; index++)
		{
			if(isxdigit(argv[1][index]) == 0)
			{
				printf("Error: '%c' is not a hex character\n", argv[1][index]);
				return -1;
			}

			strings[i] = argv[1][index];
			if(index % 2 == 1 && index != len-1)
			{
				i++;
				strings[i] = ':';
			}

			i++;
		}
	}
	else
	{
		for(index=0; index<len; index++)
		{
			if(isxdigit(argv[1][index]) == 0)
			{
				printf("Error: '%c' is not a hex character\n", argv[1][index]);
				return -1;
			}
			
			if(index == len-1)
			{
				strings[i] = 0x30; //we set it to 0, but not character 0, it should be number 0
				i++;
			}
			
			strings[i] = argv[1][index];
			if(index % 2 == 1)
			{
				i++;
				strings[i] = ':';
			}
	
			i++;
		}
	}
	
	printf("i: %d\n", i);
	strings[i] = '\0';
	printf("strings: %s\n", strings);
	
	memcpy(view_mask, strings, i+1);
	
	printf("mask: %s\n", view_mask);
	printf("length: %d\n", strlen(view_mask));

	return 0;
}

