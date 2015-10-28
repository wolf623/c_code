/*
 * =====================================================================================
 *
 *       Filename:  dulist.h
 *
 *    Description:  double list
 *
 *        Version:  1.0
 *        Created:  12/17/14 16:29:27
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

typedef int ElemType;
typedef int status;

typedef struct _LNode {
	ElemType data;
	struct _LNode *next;
}*Link, *Position, LNode;

typedef struct {
	Link head, tail; //分别指向线性链表的头尾指针
	int len; //指示线性链表中数据元素的个数
}LinkList, *p_LinkList;

status MakeNode(Link p, ElemType e); //make a node for data e
void FreeNode(Link p); //free the node

//init a null link list
status InitList(p_LinkList *L);
//destroy a link list, then do not exist L
status DestroyList(p_LinkList *L);
//set link list to NULL, and free the memory
status ClearList(p_LinkList *L);
//h is the head of link list, insert s to before the first list
status InsFirst(Link h, Link s);
//h is the head of link list, delete the first item then return back
status DelFirst(Link h, Link q);
//let s to 
status Append(p_LinkList *L, Link s);

status Remove(p_LinkList *L, Link q);

status InsBefore(p_LinkList *L, Link p, Link s);

status InsAfter(p_LinkList *L, Link p, Link s);

status SetCurElem(Link p, ElemType e);

ElemType GetCurElem(Link p);

status ListEmpty(p_LinkList *L);

status ListLength(p_LinkList *L);

Position GetHead(p_LinkList *L);

Position GetLast(p_LinkList *L);

Position PriorPos(p_LinkList *L, Link p);

Position NextPos(p_LinkList *L, Link p);

status LocatePos(p_LinkList *L, int i, Link p);

Position LocateElem(p_LinkList *L, ElemType e, status (*compare)(ElemType, ElemType));

status ListTraverse(p_LinkList *L, status (*visit)());


//to be done
