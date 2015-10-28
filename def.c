#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 	1000
#define A_CHAR 		'A'
#define LEFT_CHAR 	'('
#define RIGHT_CHAR	')'

int main(int argc, char *argv[])
{
	int i, len, num, index=0;
	char buff[MAX_LEN] = {0};
	int array[100] = {0};

	while(1)
	{
		fgets(buff, MAX_LEN, stdin);

		if(buff[0] == '\n')
			break;

		len = strlen(buff);

		for(i=0; i<len; i++)
		{
			if(buff[i] == RIGHT_CHAR)
				num++;

			if(buff[i] == A_CHAR)
				break;
		}

		array[index++] = i-num*2;
		memset(buff, 0, sizeof(buff));
	}

	for(i=0; i<sizeof(array)/sizeof(array[0]); i++)
	{
		if(array[i] != 0)
			printf("%d\n", array[i]);	
	}
			
	return 0;
}

