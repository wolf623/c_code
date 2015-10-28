#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	int data;
	struct Node *leftchild;
	struct Node *rightchild;
}Node;


//initial a bindary tree
void InitBinaryTree(Node **root, int element)
{
	*root = (Node *)malloc(sizeof(Node));
	if(*root == NULL)
	{
		printf("Memory allocation for root failed!\n");
		return;
	}

	(*root)->data = element;
	(*root)->leftchild = NULL;
	(*root)->rightchild = NULL;
}

//insert a value into binary tree
void InsertNode(Node *root, int element)
{
	Node *newnode = NULL;
	Node *p = root, *last_node = NULL;

	newnode = (Node *)malloc(sizeof(Node));
	if(newnode == NULL)
	{
		printf("Memory allocation for newnode failed!\n");
		return;
	}

	newnode->data = element;
	newnode->leftchild = newnode->rightchild = NULL;

	while(p != NULL)
	{
		last_node = p;
		if(newnode->data < p->data) 
		{
			p = p->leftchild; 
		}
		else if(newnode->data > p->data)
		{
			p = p->rightchild; 
		}
		else
		{
			printf("The Node(%d) is existed!\n", element);
			free(newnode);
			return;
		}
	}

	//link the new node
	p = last_node;
	if(newnode->data < p->data)
	{
		p->leftchild = newnode; //inset on left side
	}
	else
	{
		p->rightchild = newnode; //inset on right side
	}
}

//create a binary tree
void CreateBinaryTree(Node **root, int data[], int num)
{
	int i;
	
	for(i=0; i<num; i++)
	{
		if(NULL == *root)
			InitBinaryTree(root, data[i]);
		else
			InsertNode(*root, data[i]);
	}
}

//PreOrder
void PreOrderRec(Node *root)
{
	if(NULL != root)
	{
		printf("%d ", root->data);
		PreOrderRec(root->leftchild);
		PreOrderRec(root->rightchild);
	}
}

void PreOrderNotRec(Node *root)
{
	Node *p = root;
	Node *stack[30]; //how big this array?
	int num = 0;
	
	while(p != NULL || num > 0)
	{
		while(p != NULL)
		{
			printf("%d ", p->data);
			stack[num++] = p;
			p = p->leftchild;
		}

		num--;
		p = stack[num];
		p = p->rightchild;
	}
	printf("\n");
}

//InOrder
void InOrderRec(Node *root)
{
	if(NULL != root)
	{
		InOrderRec(root->leftchild);
		printf("%d ", root->data);
		InOrderRec(root->rightchild);
	}
}

void InOrderNotRec(Node *root)
{
	Node *p = root;
	Node *stack[30]; //how big this array?
	int num = 0;
	
	while(p != NULL || num > 0)
	{
		while(p != NULL)
		{
			stack[num++] = p;
			p = p->leftchild;
		}

		num--;
		p = stack[num];
		printf("%d ", p->data);
		p = p->rightchild;
	}
	printf("\n");
}

//PreOrder
void PostOrderRec(Node *root)
{
	if(NULL != root)
	{
		PostOrderRec(root->leftchild);
		PostOrderRec(root->rightchild);
		printf("%d ", root->data);
	}
}

void PostOrderNotRec(Node *root)
{
	int num = 0;
	Node *p = root;
	Node *stack[30];
	Node *have_visited = NULL;

	while(NULL != p || num > 0)
	{
		while(NULL != p)
		{
			stack[num++] = p;
			p = p->leftchild;
		}

		p = stack[num-1];
		if(NULL == p->rightchild || have_visited == p->rightchild)
		{
			printf("%d ", p->data);
			num--;
			have_visited = p;
			p = NULL;
		}
		else
		{
			p = p->rightchild;
		}
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	int data[] = {10, 2, 3, 15, 5};
	Node *root = NULL;
	CreateBinaryTree(&root, data, sizeof(data)/sizeof(data[0]));

	PreOrderRec(root);
	printf("\n---------\n");
	PreOrderNotRec(root);
	printf("\n---------\n");
	InOrderRec(root);
	printf("\n---------\n");
	InOrderNotRec(root);
	printf("\n---------\n");
	PostOrderRec(root);
	printf("\n---------\n");
	PostOrderNotRec(root);

	return 0;
}
