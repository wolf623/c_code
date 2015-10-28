/*  POWER ALGORITHM */

#include <stdio.h>

unsigned int Power_1(unsigned int n, unsigned int p)
{
	unsigned int i, rc = 1;
	for(i=0; i<p; i++)
		rc *= n;

	return rc;
}

unsigned int Power_2(unsigned int n, unsigned int p)
{
	unsigned int rc = n;
	unsigned odd = 1; 
	
	while(p>1)
	{
		if((p%2) != 0)
			odd *= rc;

		rc *= rc;
		p /= 2;
	}

	return rc * odd;
}

unsigned int Power(unsigned int n, unsigned int p)
{
	unsigned int odd = 1; 
	
	while(p>1)
	{
		if((p%2) != 0)
			odd *= n;

		n *= n;
		p /= 2;
	}

	return n * odd;
}


int main(int argc, char *argv[])
{
	printf("%d\n", Power(2, 13));	

	return 0;
}
