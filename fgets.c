#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	FILE *fp = fopen("data.txt", "r");
	
	char buf[12];
	if(fgets(buf, sizeof(buf), fp) == NULL)
	{
		printf("fgets failed\n");
		fclose(fp);
		return -1;
	}

	printf("first line: %d\n", atoi(buf));
	if(fgets(buf, sizeof(buf), fp) == NULL)
	{
		printf("fgets failed\n");
		fclose(fp);
		return -1;
	}

	return  0;
}

