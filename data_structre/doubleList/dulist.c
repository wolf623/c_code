/*
 * =====================================================================================
 *
 *       Filename:  dulist.c
 *
 *    Description:  double list
 *
 *        Version:  1.0
 *        Created:  12/17/14 16:33:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "dulist.h"

int main(int argc, char *argv[])
{
	LinkList *p = NULL;
	InitList(&p);

	DestoryList(&p);
	//ClearList(&p);

	return 0;	
}

int MakeNode(Link p, ElemType e)
{
	if((p = (Link)malloc(sizeof(LNode))) == NULL)
		return -1;

	p->data = e;
	p->next = NULL;
	
	return 0;
}

void FreeNode(Link p)
{
	if(p != NULL)
	{
		if(p->next != NULL)
		{
			free(p->next);
		}
		free(p);
	}
}

status InitList(p_LinkList *L)
{
	if((*L = (LinkList *)malloc(sizeof(LinkList))) == NULL)
		return -1;
	
	(*L)->head = NULL;
	(*L)->tail = NULL;
	(*L)->len = 0;

	return 0;
}

status DestoryList(p_LinkList *L)
{
	if(*L == NULL)
	{
		printf("%s(): it is NULL, can not destory\n", __FUNCTION__);
		return 0;
	}

	if((*L)->head) free((*L)->head);
	if((*L)->tail) free((*L)->tail);
	free(*L);


	return 0;
}

status ClearList(p_LinkList *L)
{
	if(*L == NULL)
		return 0;

	(*L)->head = NULL;
	(*L)->tail = NULL;

	return 0;
}

status InsFirst(Link h, Link s)
{
	s->next = h->next;
	h->next = s;
}

status DelFirst(Link h, Link q)
{
	h->next->next = h->next;	
	q = h->next;
}

status Append(p_LinkList *L, Link s)
{
	//to be done	
	return 0;
}

status Remove(p_LinkList *L, Link q)
{
	//to be done
	return 0;
}


