/*
 * =====================================================================================
 *
 *       Filename:  quick_sort.c
 *
 *    Description:  quick sort way
 *
 *        Version:  1.0
 *        Created:  12/03/14 15:23:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int swap(int array[], int a, int b)
{
	int tmp = array[a];
	array[a] = array[b];
	array[b] = tmp;
}

int partition(int array[], int start, int end)
{
	int pivot = array[start];
	while(start<end)
	{
		while(start<end && array[end] >= pivot)
			end--;
		//swap(array, start, end);
		array[start] = array[end];

		while(start<end && array[start] <= pivot)
			start++;
		//swap(array, start, end);
		array[end] = array[start];
	}

	array[start] = pivot;
	return start;
}

void quicksort(int array[], int start, int end)
{
	if(start < end)
	{
		int pivot = partition(array, start, end);
		quicksort(array, start, pivot-1);
		quicksort(array, pivot+1, end);
	}
}

void QuickSort(int array[], int len)
{
	quicksort(array, 0, len-1);
}

int main(int argc, char *argv[])
{
	int array[] = {2, 2, 2, 2, 2, 2};
	QuickSort(array, sizeof(array)/sizeof(array[0]));

	int i;
	for(i=0; i<sizeof(array)/sizeof(array[0]); i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");

	return 0;
}
