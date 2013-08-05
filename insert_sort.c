#include <stdio.h>

void insert_sort(int array[])
{
	int i, j, temp;
	
	printf("%d----\n", sizeof(array)/sizeof(int));

	for(i=1; i<sizeof(array)/sizeof(int); i++)
	{
		temp = array[i];
		j = i;
		while((j > 0) && (array[j-1] > temp))
		{
			array[j] = array[j-1];
			--j;
		}
		array[j] = temp;
	}

	for(i=0; i<(sizeof(array)/sizeof(int)); i++)
		printf("--%d", array[i]);
}


int main(int argc, char *argv[])
{
	int arr[5] = { 1, 2, 4, 5, 3};
	int i;

	insert_sort(arr);

	printf("====%d\n", sizeof(arr)/sizeof(int));

	for(i=0; i<sizeof(arr)/sizeof(int); i++)
		printf("%d", arr[i]);

	return 0;
}


