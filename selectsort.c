#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void selectsort(int array[], int len)
{
	int i, j, temp;

	for(i = 0; i < len-1; i++)
	{
		for(j = i + 1; j < len; j++)
		{
			if(array[i] > array[j])
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
}

int main(int argc, char *argv[])
{
	int array[] = { 3, 5, 9, 2 };
	int i = 0;

	printf("num=%d\n", sizeof(array)/sizeof(int));

	selectsort(array, sizeof(array)/sizeof(int));

	for(i=0; i<sizeof(array)/sizeof(int); i++)
		printf("%d ", array[i]);
	
	return 0;
}
	
