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
	int left = parent*2 + 1; ////parentµÄ×óº¢×Ó½áµã£¬ÕâÀï+1ÊÇÒò´ËÍ·½áµã´Ó0¿ªÊ¼
	while(left < len) //Èç¹û×óº¢×ÓĞ¡ÓÚ¶Ñ³¤¶È
	{
		//Èç¹ûÓÒº¢×ÓĞ¡ÓÚ¶Ô³¤¶È²¢ÇÒÓÒº¢×Ó´óÓÚ×óº¢×Ó£¬Ôò»ñÈ¡ÓÒº¢×ÓµÄ×ø±ê
		if(left+1 < len && array[left] < array[left+1])
			left++;

		//Èç¹û¸¸½Úµã±Èº¢×Ó½áµã´óÔòÍË³öÑ­»·
		if(array[parent] >= array[left])
		{
			break;
		}
		else
		{
			//Èç¹ûº¢×Ó½áµã±È¸¸½Úµã´ó£¬Ôò½»»»
			swap(array, parent, left);
			//ÒòÎªº¢×Ó½áµãÒ²¿ÉÄÜÊÇ¸¸½áµã£¬ËùÒÔ½ÓÏÂÀ´¼ÌĞøµ÷Õûº¢×Ó½áµã£¬Ö±µ½¸¸½Úµã´óÓÚÁ½¸öº¢×Ó½áµã»òÕßÃ»ÓĞº¢×Ó½áµãÎªÖ¹
			parent = left;
			left = parent*2 + 1;
		}
	}
}

//³õÊ¼»¯¶Ñ
void BuildHeap(int array[], int len)
{
	int begin = len/2 - 1; //´ÓµÚÒ»¸ö·ÇÒ¶×Ó½áµã¿ªÊ¼µ÷Õû£¬Ö±µ½×îºóµÄ¸ù½áµã£¬¸ù½áµãÊÇarry[0]
	int i;
	for(i=begin; i>=0; i--)
	{
		AdjustHeap(array, i, len);
	}
}

void HeapSort(int array[], int len)
{
	//´´½¨³õÊ¼»¯¶Ñ£¬ÓÃÊı×éÊµÏÖ¶ÑµÄ½á¹¹
	BuildHeap(array, len);

	//ÔÚ³õÊ¼»¯¶ÑÒÔºóÊı×éÊ×ÔªËØarray[0]ÊÇ×î´óµÄ£¬½»»¥Ê×ÔªËØÓë¶ÑµÄÄ©ÔªËØ
	//ÕâÑù¾ÍÍê³ÉÁË¶ÔÒ»¸öÊıµÄÅÅĞò
	int i;
	for(i=0; i<len; i++)
	{
		swap(array, 0, len-1-i); //×¢ÒâÕâÀïÊÇparentµÄÖµÒ»Ö±ÊÇ0£¬È»ºó¸úÃ¿´ÎµÄ×îºóÒ»¸öÖÖµ½»»»
		AdjustHeap(array, 0, len-1-i); //½»»»ÒÔºó¼ÌĞøµ÷ÕûÕû¸ö¶ÑµÄ½á¹¹
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
