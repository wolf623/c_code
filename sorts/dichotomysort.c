/*
 * =====================================================================================
 *
 *       Filename:  dichotomysort.c
 *
 *    Description:  dichotomy sort way
 *
 *        Version:  1.0
 *        Created:  07/11/15 15:49:36
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

int dichotomysort(int array[], int len)
{
	int i, j;
	for(i=0; i<len; i++)
	{
		int start = 0, end = i-1, mid = 0;
		int temp = array[i];
		while(start <= end)
		{
			mid = (start+end)/2;
			if(array[mid] > temp)
			{
				end = mid-1;
			}
			else
			{
				start = mid + 1;
			}
		}
		printf("i=%d, start=%d,end=%d,mid=%d, temp=%d,", i, start, end, mid, temp);	
		for(j=i-1; j>end; j--)
		{
			array[j+1] = array[j];
		}
		array[end+1] = temp;
		printf("array[%d]=%d\n",end+1, temp);
	}
}


int main(void)
{
	int a[] = {23, 20, 4, 2};
	int len = sizeof(a)/sizeof(a[0]);
	dichotomysort(a, len);
	int i=0;
	for(i=0; i<len; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	return 0;
}
