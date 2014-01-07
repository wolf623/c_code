#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This double list has no head
 * and it is circle list
 * 2013-11-21
*/

//define double list structure
typedef int dataType;
typedef struct _list_t
{
	struct _list_t *prev;
	struct _list_t *next;
	dataType data;
}list_t, *plist_t;

//initial double list
void initList(plist_t list)
{
	//list = (list_t *)malloc(sizeof(list_t));
	if(list != NULL)
		list->prev = list->next = list; //circle list
	else
		printf("%s: malloc failed\n", __FUNCTION__);
}

//create a list node
plist_t createNode(dataType data)
{
	plist_t node = (plist_t)malloc(sizeof(list_t));
	if(node != NULL)
	{
		node->data = data;
		//node->prev = node->next = node;
		node->prev = node->next = NULL;
		return node;
	}
	else
	{
		printf("%s: malloc failed\n", __FUNCTION__);
		return NULL;
	}
}


void destroyList(plist_t *list)
{
	if(*list == NULL)
		return;

	plist_t node = (*list)->next;
	plist_t temp;
	while(node != *list)
	{
		temp = node->next;
		free(node);
		node = temp;
	}
	free(*list);
	*list = NULL;
}

void isEmptyList(plist_t *list)
{
	if((*list != NULL) && (*list)->next == *list)
		printf("It is  an empty list\n");
	else if(*list == NULL)
		printf("The list is not exist\n");
	else
		printf("It is not an empty list\n");
}

int listLength(plist_t list)
{
	int length = 0;
	plist_t temp = list->next;
	while(temp != list)
	{
		length++;
		temp = temp->next;
	}

	return length;
}

void printList(plist_t list)
{
	plist_t temp = list->next;
	while(temp != list)
	{
		printf("data: %d\n", temp->data);
		temp = temp->next;
	}
}

//get element from the list
void getElem(plist_t list, int i, dataType *val)
{
	plist_t temp = list->next;
	int n = 1;
	if(i > listLength(list))
	{
		printf("The index is out of the list length\n");
		return;
	}

	while(n++ != i && temp != list)
		temp = temp->next;
	
	if(val != NULL)
		*val = temp->data;
	else
		printf("Get the data: %d\n", temp->data);
}	

//delete the element from the list
void deleteElem(plist_t list, dataType data)
{
	plist_t temp = list->next;
	while(temp != list)
	{
		if(data == temp->data)
			break;
		else
			temp = temp->next;
	}

	//find the node of the delete data
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	free(temp);
}

plist_t getElemNode(plist_t list, dataType data)
{
	plist_t temp = list->next;
	while(temp != list)
	{
		if(data == temp->data)
			return temp;
		else
			temp = temp->next;
	}
	return NULL;
}

//insert the data at the next node
void insertNodeNext(plist_t list, dataType data)
{
	plist_t node = createNode(data);
	if(node != NULL)
	{
		plist_t temp = list->next;
		while(temp->next != list)
		{
			temp = temp->next;
		}

		//find the positon to insert(last item)
		if(temp->next == list)
			list->prev = node;
		else
			(temp->next)->prev = node;

		node->prev = temp;
		node->next = temp->next;
		temp->next = node;
	}
	else
	{
		printf("%s: createNode failed\n", __FUNCTION__);
	}
}

//insert the data at the first node
void insertNodePrev(plist_t list, dataType data)
{
	plist_t node = createNode(data);
	if(node != NULL)
	{
		plist_t temp = list->next;

		//find the head of the list
		while(temp->prev != list)
			temp = temp->prev;

		node->prev = temp->prev;
		list->prev = node;
		node->next = temp;
		temp->prev->next = node;	
	}
	else
	{
		printf("%s: crateNode failed\n", __FUNCTION__);
	}
}


	
		
