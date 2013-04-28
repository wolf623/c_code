#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *mystrstr(const char *str1, const char *str2)
{
	int len = strlen(str2);
	if(len == 0)
	{
		fprintf(stderr, "Error: the str2 should not be NULL\n");
		return NULL;
	}

	for(; *str1 != '\0'; ++str1)
	{
		if(*str1 == *str2 &&
			strncmp(str1, str2, len) == 0)
		{
			return (char *)str1;
		}
	}

	return NULL;
}

int strstr_next(const char *str1, const char *str2, int next, int *num, char **ptr)
{
	int number = 0;
	int len = strlen(str2);
	if(len == 0)
	{
		fprintf(stderr, "%s():The second string should not be NULL\n", __FUNCTION__);
		return -1;
	}
	
	for(; *str1 != '\0'; ++str1)
	{
		if(*str1 == *str2 &&
			strncmp(str1, str2, len) == 0)
		{
			if(next == 0) //find at least one
			{
				number = 1;
				*num = number;
				*ptr = (char *)str1;
				return 0;
			}
			
			*ptr++ = (char *)str1;
			number++;	//find next, and increate the num
		}
	}
	
	if(number == 0)
	{
		printf("Find none, return NULL\n");
		return 0;
	}

	return 0;
}

int main(int argc,char *argv[])
{
	int num = 0, i = 0;
	char temp[128] = { 0 };
	char *str = temp;
	char buff[10][128] = { 0 };
	char **ptr = (char **)buff;
	if((str = mystrstr("Hello Wolf Wolf", "Wolf")) != NULL)
	{
		printf("Find it\n");
		printf("%s\n", str);
	}

	if((strstr_next("Hello Wolf Hello Wolf", "Wolf", 0, &num, ptr)) != -1)
	{
		printf("Find %d numbers\n", num);

		for(i = 0; i < num; i++)
			printf("%s\n", *ptr++);
	}
	
	return 0;
}

