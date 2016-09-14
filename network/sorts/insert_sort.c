/*
 * =====================================================================================
 *
 *       Filename:  insert_sort.c
 *
 *    Description:  insert sort way
 *
 *        Version:  1.0
 *        Created:  12/05/14 11:09:54
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

//从后往前查找排序
void InsertSort(int array[], int len)
{
	int i, j, key;
	for(i=1; i<len; i++)
	{
		key = array[i];
		j = i-1;
		while(j >=0 && array[j] > key)
		{
			array[j+1] = array[j];
			j--;
		}
		array[j+1] = key;
	}
}

//这个好像是冒泡法了。。。。
void InsertSort1(int array[], int len)
{
	int i, j;
	for(i=1; i<len; i++)
	{
		for(j=0; j<i; j++)
		{
			if(array[j] > array[i])
			{
				int tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
		}
	}
}

void insertsort3(int array[], int len)
{
	int i, j, k;
	for(i=1; i<len; i++)
	{
		j = 0;
		while(j<i && array[j]<=array[i])
			j++;

		if(j < i)
		{
			k = i;
			int temp = array[i];
			while(k > j)
			{
				array[k] = array[k-1];
				k--;
			}
			array[k] = temp;
		}
	}
}

int main(int argc, char *argv[])
{
	int array[] = {12, 8, 2, 24, 18};
	//InsertSort1(array, sizeof(array)/sizeof(array[0]));
	insertsort3(array, sizeof(array)/sizeof(array[0]));

	int i;
	for(i=0; i<sizeof(array)/sizeof(array[0]); i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");

	return 0;
}
