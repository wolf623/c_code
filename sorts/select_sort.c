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

//����˼�룺�����������еļ�¼����Ϊn��iȡ1,2,��,n-1,������n-i+1����¼��Ri,Ri+1,��,Rn�����ҳ���������С�ļ�¼�����i����¼������ִ��n-1��
// �������˼�¼���е�����
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

