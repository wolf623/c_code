#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER	1
#define NUMBER_OR_NAME	2
#define NAME	3
#define OTHER	4

int main(void)
{
	char str[32] = "0312f";
	char *p_str = str;
	int i;
	char rc[32];
	int c;
	int token = NUMBER;

	for(i=1; i<sizeof(str); i++)
	{
		c = str[i];

		if(c == 0)
		{
			break;
		}

		switch(isascii(c) ? token : OTHER)
		{
			case NUMBER:
			if(isdigit(c))
			{	
				printf("it is a digit\n");
				break;
			}
			case NUMBER_OR_NAME:
				if(isxdigit(c))
				{
					printf("it is a xdigit\n");
					token = NUMBER_OR_NAME;
					break;
				}
			case NAME:
				if((i == 2) && isxdigit(c) &&
					str[0] == '0' &&
					(str[1] == 'x' && str[1] == 'X'))
					{
						printf("it is a name???\n");
						token = NUMBER_OR_NAME;
						break;
					}
				else if(((c == '-') || (c == '_') || isalnum(c))) 
				{
					printf("it is ???\n");
					token = NAME;
					break;
				
				}
			case OTHER:
				printf("it is other???\n");
				break;
		}

		printf("it is %c\n", c);
	}


	return 0;
}
