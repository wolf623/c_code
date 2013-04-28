#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PRESENT_BIT(SHIFT)		((unsigned long)((unsigned long)1<<(SHIFT)))
#define SET_BIT(A, SHIFT)		((A) |= PRESENT_BIT(SHIFT))
#define CLR_BIT(A, SHIFT)		((A) &= ~PRESENT_BIT(SHIFT))
#define BIT_ON(A, FLAG) 		(((A) & PRESENT_BIT(FLAG)) != 0)

int main(int argc, char *argv[])
{
	int flag = 0;

	SET_BIT(flag, 4);
	if(BIT_ON(flag, 4))
		printf("The flag was set\n");
	
	CLR_BIT(flag, 4);
	if(!BIT_ON(flag, 4))
		printf("The flag was clear\n");

	return 0;
}
