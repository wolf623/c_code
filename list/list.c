/*
 * =====================================================================================
 *
 *       Filename:  list.c
 *
 *    Description:  list 
 *
 *        Version:  1.0
 *        Created:  12/09/14 09:18:58
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

typedef struct _LinkList
{
	int data;
	struct _LinkList *next;
}*LinkList1, LNode;

typedef struct _LinkList * LinkList;

void PrintList_L(LinkList List);

void CreateList_L(LinkList *L, int n)
{
	//LinkList L = (*List);
	*L = (LinkList)malloc(sizeof(LinkList));
	if(*L == NULL) return;

	(*L)->next = NULL; //设置带头结点的单链表
	int i = 0;
	LinkList p = NULL;
	for(i=n; i>0; --i)
	{
		p = (LinkList)malloc(sizeof(LinkList)); //生成新结点
		if(p == NULL) return;
		
		p->data = i;
		p->next = (*L)->next; //插入到表头
		(*L)->next = p;
	}

	PrintList_L(*L);
}

void PrintList_L(LinkList List)
{
	LinkList L = (List);
	if(L == NULL)
	{
		printf("oh, It is NULL...why not???\n");
		return;
	}
	
	LinkList p = L->next;
	int i = 0;
	if(p == NULL)
	{
		printf("sorry, the first one is NULL...but why?\n");
		return;
	}
	
	while(p)
	{
		i++;
		printf("%d -- data: %d\n", i, p->data);
		p = p->next;
	}
}

void MergeList_L(LinkList La, LinkList Lb, LinkList Lc)
{
	LinkList pa;
	LinkList pb;
	LinkList pc;
	if(La == NULL || Lb == NULL || Lc == NULL)
		return;

	pa = (La)->next;
	pb = (Lb)->next;
	pc = (Lc) = pa;

	while(pa && pb)
	{
		if(pa->data <= pb->data)
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}

	pc->next = pa?pa:pb;
	free(pb);
}

void test_value(int *value)
{
	*value = 23;
}

void print_value(int value)
{
	printf("value: %d\n", value);
}

void test_string(char **p)
{
	*p = (char *)malloc(128);
	if(*p == NULL) return;
	strncpy(*p, "Hello String", 128);
}

void test_string1(char *p)
{
	p = (char *)malloc(128);
	if(p == NULL) return;
	strncpy(p, "Hello World", 128);
	printf("put string: %s\n", p);
}

void print_string(char *p)
{
	if(p == NULL)
	{
		printf("sorry, it is NULL...\n");
		return;
	}
	printf("String: %s\n", p);
}

int main(int argc, char *argv[])
{
	LinkList head = NULL;
	LinkList head2 = NULL;
	LinkList head3 = (LinkList)malloc(128);
	//CreateList_L(&head, 10);
	//CreateList_L(&head2, 3);
	//MergeList_L(head, head2, head3);

	LNode la, lb, lc;
	LinkList p_la = NULL;
	CreateList_L(&p_la, 10);
	PrintList_L(p_la);
	//printf("%0x\n", &&head);

	//PrintList_L(&head);
	//printf("%0x\n", &&head);

	#if 0
	int value = 1;
	test_value(&value);
	print_value(value);
	#endif

	#if 0
	char *p = NULL;
	test_string(&p);
	print_string(p);

	char *ptr = NULL;
	test_string1(ptr);
	print_string(ptr);
	#endif 
	
	return 0;
}
