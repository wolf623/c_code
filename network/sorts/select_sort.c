/*
 * =====================================================================================
 *
 *       Filename:  select_sort.c
 *
 *    Description:  select sort way
 *
 *        Version:  1.0
 *        Created:  12/05/14 10:31:28
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

//基本思想：设所排序序列的记录个数为n。i取1,2,…,n-1,从所有n-i+1个记录（Ri,Ri+1,…,Rn）中找出排序码最小的记录，与第i个记录交换。执行n-1趟
// 后就完成了记录序列的排序。
void SelectSort(int array[], int len)
{
	int i, j, index;
	for(i=0; i<len-1; i++)
	{
		index = i;
		for(j=i+1; j<len; j++)
		{
			if(array[j] < array[index])
				index = j;

			if(index != i)
			{
				int tmp = array[i];
				array[i] = array[index];
				array[index] = tmp;
			}
		}
	}
}

int main(int argc, char *argv[])
{
	int array[] = {23, 25, 12, 9, 2};
	SelectSort(array, sizeof(array)/sizeof(array[0]));

	int i;
	for(i=0; i<sizeof(array)/sizeof(array[0]); i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");

	return 0;
}

