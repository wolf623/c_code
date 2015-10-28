#include <stdio.h>

int main(int argc, char *argv[])
{
	int abc = atoi(argv[1]);

	//Notice: if atoi() failed, then it return 0, 
	//so must check this situation
	if(abc && abc < 3)
		printf("right input\n");
	else
		printf("input error\n");

	return 0;
}
