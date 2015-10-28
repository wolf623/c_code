/*
 * =====================================================================================
 *
 *       Filename:  merge_sort.c
 *
 *    Description:  merge sort way
 *
 *        Version:  1.0
 *        Created:  12/04/14 09:13:16
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

//归并两段相邻的有序数组
void MergeArray(int array[], int start, int mid, int end, int *p_tmp)
{
	if(p_tmp == NULL)
		return;
	
	int i = start; //第一段有序数组的起始位置
	int j = mid+1; //第二段有序数组的起始位置
	int k = 0; //临时数组的坐标
	while(i<=mid && j<= end) //两个起始指针都没有走到数组末尾
	{
		if(array[i] < array[j]) //如果第一段中的元素比第二段中的元素小
			p_tmp[k++] = array[i++]; //将第一段中的元素赋值给临时数组
		else
			p_tmp[k++] = array[j++];
	}
	
	////有一段数组没有遍历到末尾，进行赋值
	while(i<=mid)
		p_tmp[k++] = array[i++];
	
	while(j<=end)
		p_tmp[k++] = array[j++];

	//将临时数组中的元素重新赋值给原始数组的指定位置
	for(i=0; i<k; i++)
		array[start+i] = p_tmp[i];
}

//归并排序，传入原始数组，排序的起始与末尾位置以及临时数组
void merge(int array[], int start, int end, int *p_tmp)
{
	if(start < end)
	{
		int mid = (start + end) / 2; //数组重点
		merge(array, start, mid, p_tmp); //递归调用，排序前半段arry[start...mid]
		merge(array, mid+1, end, p_tmp); //递归调用，排序后半段arry[mid+1,end]
		MergeArray(array, start, mid, end, p_tmp); //归并上述两段有序数组
	}
}

//归并排序，传入参数为数组与数组长度
void MergeSort(int array[], int len)
{
	// //创建临时数组，在这里创建临时数组比在后面创建临时数组的开销要小，后面所有递归调用用的都是同一个临时数组
	int *p_tmp = (int *)malloc(len * sizeof(int));
	if(p_tmp == NULL)
		return;

	merge(array, 0, len-1, p_tmp);
}

int main(int argc, char *argv[])
{
	int array[] = {3, 34, 23, 8, 1};
	MergeSort(array, sizeof(array)/sizeof(array[0]));

	int i;
	for(i=0; i<sizeof(array)/sizeof(array[0]); i++)
	{
		printf("%d ", array[i]);
	}

	printf("\n");
	return 0;
}
