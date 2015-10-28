#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Get the size of the file
*/
int get_file_size(const char *file)
{
	if(file == NULL)
		return  -1;

	FILE *fp = fopen(file, "w+");
	if(fp == NULL)
		return -1;
	
	fprintf(fp, "Hello");
	fseek(fp, 0L, SEEK_END);

	int size = ftell(fp);

	return size;
}

int main(int argc, char *argv[])
{
	printf("File size : %d\n", get_file_size(argv[1]));

	return 0;
}
