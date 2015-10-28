#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	FILE *fp = fopen("file.txt", "a+");
	if(fp == NULL)
	{
		printf("fopen file failed\n");
	}
	else
	{
		fprintf(fp, "hello abc\n");
		fprintf(fp, "hello wolf\n");
	}

	fclose(fp);

	return 0;
}
