/*
 * =====================================================================================
 *
 *       Filename:  heap_sort.c
 *
 *    Description:  heap sort way
 *
 *        Version:  1.0
 *        Created:  12/04/14 15:42:40
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

void swap(int array[], int a, int b)
{
	int tmp = array[a];
	array[a] = array[b];
	array[b] = tmp;
}

void AdjustHeap(int array[], int parent, int len)
{
	int left = parent*2 + 1; ////parent�����ӽ�㣬����+1�����ͷ����0��ʼ
	while(left < len) //�������С�ڶѳ���
	{
		//����Һ���С�ڶԳ��Ȳ����Һ��Ӵ������ӣ����ȡ�Һ��ӵ�����
		if(left+1 < len && array[left] < array[left+1])
			left++;

		//������ڵ�Ⱥ��ӽ������˳�ѭ��
		if(array[parent] >= array[left])
		{
			break;
		}
		else
		{
			//������ӽ��ȸ��ڵ���򽻻�
			swap(array, parent, left);
			//��Ϊ���ӽ��Ҳ�����Ǹ���㣬���Խ����������������ӽ�㣬ֱ�����ڵ�����������ӽ�����û�к��ӽ��Ϊֹ
			parent = left;
			left = parent*2 + 1;
		}
	}
}

//��ʼ����
void BuildHeap(int array[], int len)
{
	int begin = len/2 - 1; //�ӵ�һ����Ҷ�ӽ�㿪ʼ������ֱ�����ĸ���㣬�������arry[0]
	int i;
	for(i=begin; i>=0; i--)
	{
		AdjustHeap(array, i, len);
	}
}

void HeapSort(int array[], int len)
{
	//������ʼ���ѣ�������ʵ�ֶѵĽṹ
	BuildHeap(array, len);

	//�ڳ�ʼ�����Ժ�������Ԫ��array[0]�����ģ�������Ԫ����ѵ�ĩԪ��
	//����������˶�һ����������
	int i;
	for(i=0; i<len; i++)
	{
		swap(array, 0, len-1-i); //ע��������parent��ֵһֱ��0��Ȼ���ÿ�ε����һ���ֵ����
		AdjustHeap(array, 0, len-1-i); //�����Ժ�������������ѵĽṹ
	}
}

int main(int argc, char *argv[])
{
	int array[] = {23, 28, 12, 4, 43};
	HeapSort(array, sizeof(array)/sizeof(array[0]));

	int i;
	for(i=0; i<sizeof(array)/sizeof(array[0]); i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");

	return 0;
}
