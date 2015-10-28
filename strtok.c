#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_number_list(char *str, int *list)
{
	if(str == NULL)
	{	
		printf("Error: the str should not be NULL\n");
		return -1;
	}

	char *token;
	int strLen = strlen(str);
	int i;

	for(i=0; i<strLen; i++)
	{
		if((str[i] != ',') && (str[i] < '0' || str[i] > '9'))
		{
			printf("Error: wrong input number list: str[%d] %d\n", i, str[i]);
			return -1;
		}
	}
	
	token = strtok(str, ",");
	while(token != NULL)
	{
		i = atoi(token);
		*list++ = i;
		
		token = strtok(NULL, ",");
	}

	return 0;
}

	
int main(int argc, char *argv[])
{
	char str[128] = { 0 };
	int list[128] = { 0 };
	printf("please input the number list: ");
	scanf("%s", str);
	printf("what you input is: %s\n", str);

	if(get_number_list(str, list) != 0)
		return -1;

	int i;
	int len = sizeof(list)/sizeof(list[0]);
	for(i=0; i<len; i++)
	{
		if(list[i] != 0)
			printf("%d: %d\n", i, list[i]);
	}

	return 0;
}



