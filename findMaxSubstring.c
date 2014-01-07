#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int bool;

int findMaxSubstring(char* str)
{
    int maxLength = 0;
	int maxStartIndex = 0;
	int curLength = 0;
	int curStartIndex = 0;
	bool isFind = 0;
	unsigned int i = 0;
	for(i = 0;i<strlen(str);i++)
	{
		if(str[i] >= 'a' && str[i] <= 'z')
		{
			if(isFind == 0)
			{
				isFind = 1;
				curLength = 1;
				curStartIndex = i;
			}
			else
			{
				curLength++;
			}
		}
		else if (str[i] < 'a' || str[i] > 'z')
		{
			isFind = 0;
			if(curLength > maxLength)
			{
				maxLength = curLength;
				maxStartIndex = curStartIndex;
				curLength = 0;
			}
		}
	}
	char *p = NULL;
	p = &str[maxStartIndex];
	while(*p >= 'a' && *p <= 'z')
	{
		putchar(*p);
		p++;
	}
	return maxLength;
}


int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Usage: findMaxSubstring <str>\n");
		return -1;
	}

	int maxLen = findMaxSubstring(argv[1]);
	printf("\nmaxLength: %d\n", maxLen);
	return 0;
}

