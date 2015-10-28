/*
 * =====================================================================================
 *
 *       Filename:  static_link.c
 *
 *    Description:  static link 
 *
 *        Version:  1.0
 *        Created:  12/15/14 10:29:49
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

#define MAXSIZE 20
typedef int ElemType;

typedef struct {
	ElemType data;
	int cur;
}component, SLinkList[MAXSIZE], p_SLinkList;

void InitSpace_SL(SLinkList space)
{
	int i = 0;
	for(i=0; i<MAXSIZE-1; ++i)
		space[i].cur = i+1;
	
	space[MAXSIZE-1].cur = 0;
	printf("%s(): Initial successfully!\n", __FUNCTION__);
}

void PrintSpace_SL(SLinkList space)
{
	int i;
	for(i=0; i<MAXSIZE; i++)
	{
		printf("i: cur %d, data %d\n", i, space[i].cur, space[i].data);
	}
}

int Malloc_SL(SLinkList space)
{
	int i = space[0].cur;
	if(space[0].cur)
		space[0].cur = space[i].cur;
	
	return i;
}

void Free_SL(SLinkList space, int k)
{
	space[k].cur = space[0].cur;
	space[0].cur = k;
}

int LocateElem_SL(SLinkList S, ElemType e)
{
	int i = S[0].cur;
	while(i && S[i].data != e)
		i = S[i].cur;
	
	return i;
}

void difference(SLinkList space, int s)
{
	InitSpace_SL(space);
	s = Malloc_SL(space);
	
	int r = s;
	int m = 5;
	int n = 3;

	int i, j, b, p, k;
	for(j=1; j<=m; ++j)
	{
		i = Malloc_SL(space);
		space[i].data = j;
		space[r].cur = i;
		r = i;
	}
	space[r].cur = 0;

	for(j=1; j<=n; ++j)
	{
		b = j;
		p = s;
		k = space[s].cur;
		while(k != space[r].cur && space[k].data != b)
		{
			p = k;
			k = space[k].cur;
		}

		if(k == space[r].cur)
		{
			i = Malloc_SL(space);
			space[i].data = b;
			space[i].cur = space[r].cur;
			space[r].cur = i;
		}
		else
		{
			space[p].cur = space[k].cur;
			Free_SL(space, k);
			if(r == k)
				r = p;
		}
	}
}

int main(int argc, char *argv[])
{
	SLinkList space;
	InitSpace_SL(space);
	
	//PrintSpace_SL(space);

	difference(space, 20);

	PrintSpace_SL(space);

	return 0;
}


