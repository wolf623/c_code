#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* define double list */
typedef struct _Node_t
{
	struct _Node_t *prev;
	struct _Node_t *next;
	int val;
}Node_t;

//global 
Node_t *list;

int createList(int value)
{
	//Node_t *list; 
	list = (Node_t *)malloc(sizeof(Node_t));
	if(list == NULL)
		printf("malloc failed\n");
	
	list->prev = list->next = NULL;
	list->val = value;
}

int isEmpty()
{
	if(list == NULL)
		printf("it is an empty list\n");
}

void clearList()
{	
	Node_t *temp = list;
	while(list != NULL)
	{
		list = list->next;
		free(temp);
		temp = list;;
	}
}

/* insert the value at the last item  */
void insertListAtLast(int value)
{
	if(list == NULL)
	{
		//return createList(value);
		printf("The list is empty\n");
		return;
	}

	Node_t *p = (Node_t *)malloc(sizeof(Node_t));
	if(p == NULL)
	{
		printf("malloc failed\n");
		return;
	}

	p->val = value;
	p->next = NULL;

	Node_t *temp = list;
	while(temp->next != NULL)
	{
		temp = temp->next; //find the last item
	}

	temp->next = p;
	p->prev = temp;
}

/* insert the value at the first item */
void insertListAtFirst(int value)
{
	if(list == NULL)
	{
		//return createList(value);
		printf("The list is empty\n");
		return;
	}
	
	Node_t *p = (Node_t *)malloc(sizeof(Node_t));
	if(p == NULL)
	{
		printf("malloc failed\n");
		return;
	}
	
	p->val = value;
	p->prev = NULL;

	//list the first item of the double list
	p->next = list;
	list->prev = p;
	list = p;
}

void printList()
{
	Node_t *p = list;
	printf("\n---------------\n");
	while(p != NULL)
	{
		printf("value: %d\n", p->val);
		p = p->next;
	}
	printf("---------------\n");
}

Node_t *searchList(int value)
{	
	Node_t *p = list;
	while(p != NULL)
	{
		if(p->val == value)
		{
			printf("find it, the value is: %d\n", p->val);
			return p; //find it
		}
		p = p->next;
	}
	
	printf("not find the value: %d\n", value);
	return NULL;
}

void deleteFirstList()
{
	if(list != NULL)
	{
		//list is the head of the double list
		Node_t *head = list;
		if(list->next != NULL)
		{
			list->next->prev = NULL;
			list = list->next;
			free(head);
		}
		else
		{
			free(list);
			list = NULL;
		}
	}
	else
	{
		printf("The list is empty\n");
	}
}

void deleteLastList()
{
	if(list != NULL)
	{
		Node_t *head = list;
		while(list->next != NULL)
		{
			list = list->next;
		}

		list->prev->next = NULL;
		free(list);
		list = head;
	}
}

void deleteList(int value)
{
	Node_t *p = searchList(value);
	if(p == NULL)
	{
		printf("Can not find the value %d\n", value);
	}
	else if(p == list )
	{
		//it is first item
		deleteFirstList();
	}
	else if(p->next == NULL)
	{
		//it is last item
		p->prev->next = NULL;
		p->prev = NULL;
		free(p);
	}	
	else
	{
		p->prev->next = p->next;
		p->next->prev = p->prev;
		free(p);
	}
}


