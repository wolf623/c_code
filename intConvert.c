#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void intConvert(int digit)
{
	char str[5][11] = {" thousand ", " hundred ", " ten ", " ", " zero "};
	char num[11][20] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};
	char result[50] ={'\0'};
	int i = 0;
	int rc[4] = {};

	for(i=3; i>=0; i--)
	{
		rc[i] = digit % 10;
		digit = (digit/10);
	}
	printf("Num: %d,%d,%d,%d\n", rc[0], rc[1], rc[2], rc[3]);

	int foundZero = 0, flag = 0;
	for(i=0; i<4; i++)
	{
		if(rc[i] != 0)
		{
			strcat(result, num[rc[i]]);
			strcat(result, str[i]);
			flag = 1;
		}

		if(rc[i] == 0 && foundZero == 0)
		{
			if(i != 3 && flag != 0 && (rc[3] != 0 || (rc[3] == 0 && rc[2] != 0)))
			{
				foundZero = 1;
				strcat(result, str[4]);
			}
		}
	}
	//printf("result: %s\n", result);
	puts(result);

}

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Usage: intConvert <digit num>\n");
		return -1;
	}

	intConvert(atoi(argv[1]));
	return 0;
}
