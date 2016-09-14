/*
 * =====================================================================================
 *
 *       Filename:  bubbling_sort.c
 *
 *    Description:  bubbling sort way
 *
 *        Version:  1.0
 *        Created:  12/03/14 13:46:42
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

void bubbling_sort(int *array, int n)
{
	int i, j;
	int flag = 1;

	for(i=0; i<n-1; i++)
	{
		if(flag == 1)
		{
			flag = 0;
			for(j=0; j<n-1-i; j++)
			{
				if(array[j]>array[j+1])
				{
					flag = 1;
					int tmp = array[j];
					array[j] = array[j+1];
					array[j+1] = tmp;		
				}
			}
		}
		else
		{
			//sorted all
			break;
		}
	}
}

int main(int argc, char *argv[])
{
	int arr[] = {1, 4, 2, 34, 23};
	bubbling_sort(arr, sizeof(arr)/sizeof(arr[0]));

	int i;
	for(i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");

	return 0;
}
