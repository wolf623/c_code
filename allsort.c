#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void shell_sort(int *array,int n);

void bubble_sort(int *array, int num);

void select_sort(int *array, int len);

void insert_sort1(int *array, int num);

void insert_sort2(int *array, int num);

void quick_sort(int *array, int low, int high);

int main()
{
	int array[] = { 1,3,4,0,0,8,5,6};
  	int num = sizeof(array)/sizeof(array[0]);
  	int brray[num];
  
 	 int i = 0;
 
	memcpy(brray,array,num*sizeof(int));
 
	printf("before: num = %d\n",num);
  
  	for(i=0; i<num; i++)
		printf("%d ",brray[i]);
		
	printf("\n");
	
  	//shell_sort(array,num);
  	//bubble_sort(array, num);
  	//select_sort(brray,num);
  	//insert_sort1(brray, num);
	//insert_sort2(brray, num);
	quick_sort(brray, 0, num-1);

	printf("After: num = %d\n",num);
	
	for(i=0; i<num; i++)
		printf("%d ",brray[i]);
		
  	printf("\n");

  	return 0;
}


void bubble_sort(int *array, int num)
{
	int i, j, temp, flag;
	for(i=0; i<num; i++)
	{
		for(j=0; j<num-i-1; j++)
		{
			flag = 1;
			if(array[j] > array[j+1])
			{
				temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
				flag = 0;
			}
		}
		
		if(1 == flag)
			break;
	}
}




void shell_sort(int *array,int n)
{
	int i, j, k, temp;
	
	for(k=n/2; k>0; k/=2)
		for(i=k; i<n; i++)
		{
			temp = array[i];
			for(j=i; j>=k; j-=k)
				if(temp < array[j-k])
					array[j] = array[j-k];
				else
					break;
				
			array[j] = temp;
		}
		
}


void select_sort(int *array, int len)
{
	int i, j, temp;
	for(i=0; i<len-1; i++)
	{
		for(j=i+1; j<len; j++)
		{
			if(array[i] > array[j])
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
}

void insert_sort1(int *array, int num)
{
	int i, j, temp;

	for(i=1; i<num; i++)
	{
		temp = array[i];
		j = i;
		
		//while((j > 0) && (array[j-1] < temp))
		while((j > 0) && (array[j-1] > temp))
		{
			array[j] = array[j-1];
			--j;
		}

		array[j] = temp; //array[0] = temp
	}
}

void insert_sort2(int *array, int num)
{
	int i, j, low, high, mid;
	int temp;

	for(i=1; i<num; i++)
	{
		temp = array[i];

		low = 0;
		high = i - 1;

		while(low <= high)
		{
			mid = (low + high) / 2;
			if(temp < array[mid])
				high = mid - 1;
			else
				low = mid + 1;
		}

		for(j = i-1; j >= high+1; --j)
		{
			array[j+1] = array[j];
		}

		array[high+1] = temp;
	}
}

int partition(int *array, int low, int high)
{
	int mid = array[low];
	
	while(low < high)
	{
		while((low < high) && (array[high] >= mid))
		{
			--high;
		}

		array[low] = array[high];

		while((low < high) && (array[low] < mid))
		{
			++low;
		}

		array[high] = array[low];
	}

	array[low] = mid;

	return low;
}

void quick_sort(int *array, int low, int high)
{
	int mid;
	if(low < high)
	{
		mid = partition(array, low, high);
		quick_sort(array, low, mid-1);
		quick_sort(array, mid+1, high);
	}
}
