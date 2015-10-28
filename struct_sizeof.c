#include <stdio.h>

typedef struct{
	int num1;
	int num2;
	double num3;
}A;

typedef struct{
	int num1;
	double num3;
	int num2;
}B;

int main(void)
{
	printf("A: %d\n", sizeof(A));
	printf("B: %d\n", sizeof(B));
	return 0;
}

