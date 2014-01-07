#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>

jmp_buf zero_jmp_buf;
double division(int a, int b)
{
	double result = 0.0;
	if(b == 0)
	{
		printf("Error, b==0, throw exception\n");
		longjmp(zero_jmp_buf, 1);
		printf("Never go to this\n");
	}

	result = a/b;
	printf("result: %.2f\n", result);
}

int main(void)
{
	if(0 == setjmp(zero_jmp_buf))
	{
		printf("it is normal\n");
		division(20, 5);
		division(10, 0);
		division(30, 2);
	}
	else
	{
		printf("catch the exception, the b is zero\n");
	}

	return 0;
}
