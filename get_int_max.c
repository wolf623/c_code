/*
 * Get max int value and unsigned value
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int get_int_max(void)
{
	//int int_max = ~(1<<(8*sizeof(int))-1); 
	//int int_max = INT_MAX;
	int int_max = (int)((~(unsigned int)0) >>1);
	return int_max;
}

int get_int_min(void)
{
	//int int_min = ~((int)(~((unsigned int)0)>>1));
	int int_min = ~get_int_max();
	//int int_min = INT_MIN;
	return int_min;
}

unsigned int get_uint_max(void)
{
	unsigned int uint_max = ~(0U);
	return uint_max;
}

int main(void)
{
	printf("max int value: %d\n", get_int_max());
	printf("min int value: %d\n", get_int_min());
	printf("max unsigned int value: %u\n", get_uint_max());

	return 0;
}
