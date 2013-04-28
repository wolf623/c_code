#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void shellsort(int array[],int n);

void BubbleSort(int array[], int num);

int SelectSort(int array[], int len);


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
	
  	//shellsort(array,num);
  	//BubbleSort(array, num);
  	SelectSort(brray,num);
  
	printf("After: num = %d\n",num);
	
	for(i=0; i<num; i++)
		printf("%d ",brray[i]);
		
  	printf("\n");

  	return 0;
}


void BubbleSort(int array[], int num)
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




void shellsort(int array[],int n)
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


int SelectSort(int array[], int len)
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

	return 0;
}
