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

//�鲢�������ڵ���������
void MergeArray(int array[], int start, int mid, int end, int *p_tmp)
{
	if(p_tmp == NULL)
		return;
	
	int i = start; //��һ�������������ʼλ��
	int j = mid+1; //�ڶ��������������ʼλ��
	int k = 0; //��ʱ���������
	while(i<=mid && j<= end) //������ʼָ�붼û���ߵ�����ĩβ
	{
		if(array[i] < array[j]) //�����һ���е�Ԫ�رȵڶ����е�Ԫ��С
			p_tmp[k++] = array[i++]; //����һ���е�Ԫ�ظ�ֵ����ʱ����
		else
			p_tmp[k++] = array[j++];
	}
	
	////��һ������û�б�����ĩβ�����и�ֵ
	while(i<=mid)
		p_tmp[k++] = array[i++];
	
	while(j<=end)
		p_tmp[k++] = array[j++];

	//����ʱ�����е�Ԫ�����¸�ֵ��ԭʼ�����ָ��λ��
	for(i=0; i<k; i++)
		array[start+i] = p_tmp[i];
}

//�鲢���򣬴���ԭʼ���飬�������ʼ��ĩβλ���Լ���ʱ����
void merge(int array[], int start, int end, int *p_tmp)
{
	if(start < end)
	{
		int mid = (start + end) / 2; //�����ص�
		merge(array, start, mid, p_tmp); //�ݹ���ã�����ǰ���arry[start...mid]
		merge(array, mid+1, end, p_tmp); //�ݹ���ã��������arry[mid+1,end]
		MergeArray(array, start, mid, end, p_tmp); //�鲢����������������
	}
}

//�鲢���򣬴������Ϊ���������鳤��
void MergeSort(int array[], int len)
{
	// //������ʱ���飬�����ﴴ����ʱ������ں��洴����ʱ����Ŀ���ҪС���������еݹ�����õĶ���ͬһ����ʱ����
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
