#include <stdio.h>

void sequence_search(int *array, int num, int x);

void half_search(int *array, int num, int x);

int main(int argc, char *argv[])
{
	int arr[] = {1, 5, 3, 4, 2};
	int abc = 3;

	sequence_search(arr, sizeof(arr)/sizeof(arr[0]), abc);
	half_search(arr, sizeof(arr)/sizeof(arr[0]), abc);
	
	return 0;
}

void sequence_search(int *array, int num, int x)
{
	int i, findflag;
	
	findflag = 0;

	while(i < num)
	{
		if(array[i] == x)
		{
			findflag = 1;
			printf("Find: %d, int is array[%d]\n", x, i);
		}
		
		i++;
	}
}

void half_search(int *array, int num, int x)
{
	int mid, low, high;
	int findflag = 0;

	low = 0;
	high = num - 1;

	do
	{
		mid = (low + high) / 2;
		if(x == array[mid])
			findflag = 1;
		else if(x > array[mid])
			low = mid + 1;
		else
			high = mid - 1;
	}while((low < high) && (findflag == 0));

	if(findflag == 0)
		printf("Not find %d\n", x);
	else
		printf("Find: %d, it is array[%d]\n", x, mid);
}
