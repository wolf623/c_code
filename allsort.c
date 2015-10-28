#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void shell_sort1(int *array,int n);
void shell_sort2(int *array,int n);

void bubble_sort(int *array, int num);

void select_sort(int *array, int len);

void insert_sort1(int *array, int num);
void insert_sort2(int *array, int num);

void quick_sort1(int *array, int num);
void quick_sort2(int *array, int num);

void merge_sort(int *array, int num);

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
	
  	//shell_sort1(brray,num);
	//shell_sort2(brray, num);
  	//bubble_sort(array, num);
  	//select_sort(brray,num);
  	//insert_sort1(brray, num);
	//insert_sort2(brray, num);
	//quick_sort1(brray, num);
	quick_sort2(brray, num);
	//merge_sort(brray, num);

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




void shell_sort1(int *array,int n)
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

//other wrinting for shell sort
void shell_sort2(int *a, int n)
{
	int d = n;
	int temp;
	int i;
	while(d > 1)
	{
		d = (d + 1) / 2;
		for(i=0; i<n-d; i++)
		{
			if(a[i] > a[i+d])
			{
				temp = a[i];
				a[i] = a[i+d];
				a[i+d] = temp;
			}
		}
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

/* quick_sort1() */ 
int partition1(int *array, int low, int high)
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

void _quick_sort(int *array, int low, int high)
{
	int mid;
	if(low < high)
	{
		mid = partition1(array, low, high);
		_quick_sort(array, low, mid-1);
		_quick_sort(array, mid+1, high);
	}
}

void quick_sort1(int *array, int num)
{
	_quick_sort(array, 0, num-1);
}
/* end of quick_sort1() */

/*start of quick_sort2() */
void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int partition2(int a[], int p, int r)
{
	int i = p;
	int j = r + 1;
	int x = a[p];
	while(1)
	{
		while(a[++i]<x && i<r);
		while(a[--j] > x);
		if(i >= j)
			break;
		swap(&a[j], &a[i]);
	}

	a[p] = a[i];
	a[j] = x;
	return j;
}

void _quick_sort2(int a[], int p, int r)
{
	if(p < r)
	{
		int q = partition2(a, p, r);
		_quick_sort2(a, p, q-1);
		_quick_sort2(a, q+1, r);
	}
}

//something is wrong, how to call the _quick_sort2() func????
void quick_sort2(int a[], int num)
{
	_quick_sort2(a, 0, num-1);
}
/* end of quick_sort2() */

/* merge_sort() */
void mergearray(int *array, int first, int last)
{
	int i, j, k, mid, l;
	int *temp;

	temp = (int *)malloc(sizeof(int) * (last + 1));
	if(temp == NULL)
	{
		printf("malloc error\n");
		return;
	}

	i = first;
	mid = (first + last) / 2;
	j = mid + 1;
	l = last;
	k = 0;

	while(i <= mid && j <= l)
	{
		if(array[i] <= array[j])
			temp[k++] = array[i++];
		else
			temp[k++] = array[j++];
	}

	while(i <= mid)
		temp[k++] = array[i++];
	
	while(j <= l)
		temp[k++] = array[j++];

	for(i=0; i<k; i++)
		array[first+i] = temp[i];

	free(temp);
}

void _merge_sort(int *array, int first, int last)
{
	if(first < last)
	{
		int mid = (first + last) / 2;
		_merge_sort(array, first, mid);
		_merge_sort(array, mid+1, last);
		mergearray(array, first, last);
	}
}

void merge_sort(int *array, int num)
{
	int *temp = (int *)malloc(sizeof(int) * num);
	if(temp == NULL)
		printf("malloc error\n");

	_merge_sort(array, 0, num-1);

	free(temp);
}
/* end of merge_sort() */

