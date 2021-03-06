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
	int left = parent*2 + 1; ////parent的左孩子结点，这里+1是因此头结点从0开始
	while(left < len) //如果左孩子小于堆长度
	{
		//如果右孩子小于对长度并且右孩子大于左孩子，则获取右孩子的坐标
		if(left+1 < len && array[left] < array[left+1])
			left++;

		//如果父节点比孩子结点大则退出循环
		if(array[parent] >= array[left])
		{
			break;
		}
		else
		{
			//如果孩子结点比父节点大，则交换
			swap(array, parent, left);
			//因为孩子结点也可能是父结点，所以接下来继续调整孩子结点，直到父节点大于两个孩子结点或者没有孩子结点为止
			parent = left;
			left = parent*2 + 1;
		}
	}
}

//初始化堆
void BuildHeap(int array[], int len)
{
	int begin = len/2 - 1; //从第一个非叶子结点开始调整，直到最后的根结点，根结点是arry[0]
	int i;
	for(i=begin; i>=0; i--)
	{
		AdjustHeap(array, i, len);
	}
}

void HeapSort(int array[], int len)
{
	//创建初始化堆，用数组实现堆的结构
	BuildHeap(array, len);

	//在初始化堆以后数组首元素array[0]是最大的，交互首元素与堆的末元素
	//这样就完成了对一个数的排序
	int i;
	for(i=0; i<len; i++)
	{
		swap(array, 0, len-1-i); //注意这里是parent的值一直是0，然后跟每次的最后一个种到换�
		AdjustHeap(array, 0, len-1-i); //交换以后继续调整整个堆的结构
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
