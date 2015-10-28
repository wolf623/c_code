#include "myavl.h"

avlnode *singleRightRotate(avlnode *anode)
{
	avlnode *bnode = anode->left;
	anode->left = bnode->right;
	bnode->right = anode;

	//adjust the height
	anode->height = maxh(height(anode->right), height(anode->left)) + 1;
	bnode->height = maxh(height(bnode->right), height(bnode->left)) + 1;
	
	return bnode;
}

avlnode *singleLeftRotate(avlnode *anode)
{
	avlnode *bnode = anode->right;
	anode->right = bnode->left;
	bnode->left = anode;

	//adjust height
	anode->height = maxh(height(anode->right), height(anode->left)) + 1;
	bnode->height = maxh(height(bnode->right), height(bnode->left)) + 1;

	printf("bnode->height: %d\n", bnode->height);
	return bnode;
}

avlnode *leftRightRotate(avlnode *anode)
{
	anode->left = singleLeftRotate(anode->left);
	return singleRightRotate(anode);
}

avlnode *rightLeftRotate(avlnode *anode)
{
	anode->right = singleRightRotate(anode->right);
	return singleLeftRotate(anode);
}

// insert a key to AVL (*tree).
avlnode* avl_insert(avltree **tree, keyType key) 
{
	if(NULL == (*tree)) 
	{
		(*tree) = (avlnode*) malloc(sizeof(avlnode));
		(*tree)->key = key;
		(*tree)->height = 1;
		(*tree)->left = (*tree)->right = NULL;
		printf("First insert, value: %d\n", key);
	} 
	else if(key > (*tree)->key) 
	{ // insert into the right subtree
		printf("insert right value(parent->key %d): %d\n", (*tree)->key, key);
		(*tree)->right = avl_insert(&(*tree)->right, key);
		int balanceFactor = height((*tree)->right) - height((*tree)->left);
		if (balanceFactor == 2) 
		{
			if(key > (*tree)->right->key) 
			{ // RR 型 , 右侧单旋
				printf("it is RR\n");
				(*tree) = singleLeftRotate((*tree));
			} 
			else 
			{ // RL型 , 右侧双旋
				printf("it is RL\n");
				(*tree) = rightLeftRotate((*tree));
			}
		}
	} 
	else if (key < (*tree)->key) 
	{ // insert into the left subtree
		printf("insert left value(parent->key %d): %d\n", (*tree)->key, key);
		(*tree)->left = avl_insert(&(*tree)->left, key);
		int balanceFactor = height((*tree)->left) - height((*tree)->right);
		if (balanceFactor == 2) 
		{
			if (key < (*tree)->left->key)
			{ // LL型 , 左侧单旋
				printf("it is LL\n");
				(*tree) = singleRightRotate((*tree));
			} 
			else 
			{ // LR型 ， 左侧双旋
				printf("it is LR\n");
				(*tree) = rightLeftRotate((*tree));
			}
		}
	} 
	else 
	{ // if the key is already exists, nothing to do....
	}


	// 重新计算树的高度
	(*tree)->height = maxh(height((*tree)->left), height((*tree)->right)) + 1;

	return (*tree);
}


// delete the given key from AVL (*tree).
avlnode* avl_delete(avltree **tree, keyType key) 
{
	if (NULL == (*tree)) 
	{
		return NULL;
	}
	// delete the node with the given key
	if (key > (*tree)->key) 
	{ // key exists in the right subtree
		(*tree)->right = avl_delete(&(*tree)->right, key);
	} 
	else if (key < (*tree)->key) 
	{ // key exists in the left subtree
		(*tree)->left = avl_delete(&(*tree)->left, key);
	} else 
	{
		if (NULL != (*tree)->left) 
		{ // when left is not NULL
			// find max node if left (*tree)
			avlnode* dn = NULL;
			for (dn = (*tree)->left; NULL != dn->right; dn = dn->right) 
			{
			}
			// change the value
			(*tree)->key = dn->key;
			// delete the max node
			(*tree)->left = avl_delete(&(*tree)->left, dn->key);
		} 
		else if (NULL != (*tree)->right) 
		{ // when the right (*tree) is not NULL
			// find the minimal node
			avlnode* dn = NULL;
			for (dn = (*tree)->right; NULL != dn->left; dn = dn->left)
			{
			}
			// change the value
			(*tree)->key = dn->key;
			// delete the minimal node
			(*tree)->right = avl_delete(&(*tree)->right, dn->key);
		} 
		else 
		{			// when the node has no child
			free((*tree));
			// the (*tree) is Empty now, no need to do any operation
			return NULL;
		}
	}
	// adjust the (*tree) to balance state after deletion
	if (height((*tree)->left) - height((*tree)->right) == 2) { // when the left subtree is too high
		if (height((*tree)->left->right) - height((*tree)->left->left) == 1) { // LR model
			(*tree) = leftRightRotate((*tree));
		} else { // LL model
			(*tree) = singleRightRotate((*tree));
		}
	} else if (height((*tree)->left) - height((*tree)->right) == -2) { // when the right subtree is too high
		if (height((*tree)->right->left) - height((*tree)->right->right) == 1) { // RL model
			(*tree) = rightLeftRotate((*tree));
		} else { // RR model
			(*tree) = singleLeftRotate((*tree));
		}
	} else {
		// the (*tree) is already balanced, nothing to do ...
	}

	// recalculate the height of the (*tree).
	(*tree)->height = maxh(height((*tree)->right), height((*tree)->left)) + 1;

	return (*tree);
}

void print_avl_height(avlnode **tree)
{
	if(*tree == NULL)
	{
		printf("The tree is empty...\n");
	}

	printf("Tree Height: %d\n", (*tree)->height);
}

int search_avl_1(avlnode **tree, keyType value, avlnode **parent, avlnode **p)
{
	*p = *tree;
	while(*p)
	{
		if((*p)->key == value)
		{
			printf("find it\n");
			return 1; //find it
		}
		else if((*p)->key > value)
		{
			*parent = *p;
			*p = ((*p)->left);
		}
		else
		{
			*parent = *p;
			*p = ((*p)->right);
		}
	}

	return 0; //not found
}

int search_avl_by_key(avlnode **tree, keyType value)
{
	avlnode *p = *tree;
	while(p)
	{
		if(p->key == value)
		{
			printf("find %d in the tree\n", value);
			return 1;
		}
		else if(p->key > value)
		{
			p = p->left;
		}
		else
		{
			p = p->right;
		}
	}

	printf("oh, no, can not find %d in the tree\n", value);
	return 0; //nod found it
}

int counter_avl_tree(avlnode *tree)
{
	if(tree == NULL)
		return 0;
	return counter_avl_tree(tree->left) + counter_avl_tree(tree->right) + 1;
}

int GetDepth(avlnode *tree)
{
	if(tree == NULL)
		return 0;
	
	int depthLeft = GetDepth(tree->left);
	int depthRight = GetDepth(tree->right);
	return (depthLeft > depthRight)?(depthLeft + 1):(depthRight + 1);
}

int GetNodeNumKthLevel(avlnode * pRoot, int k)
{
	if(pRoot == NULL || k < 1)
		return 0;
	if(k == 1)
		return 1;
	int numLeft = GetNodeNumKthLevel(pRoot->left, k-1); // 左子树中k-1层的节点个数
	int numRight = GetNodeNumKthLevel(pRoot->right, k-1); // 右子树中k-1层的节点个数
	return (numLeft + numRight);
}

typedef int (*visit)(keyType e);

int PrintElement(keyType e)
{
	printf("%d ", e);
	return 1;
}


int PreOrderTraverse(avlnode *tree, visit visit_func)
{
	if(tree)
	{
		if(visit_func(tree->key))
		{
			if(PreOrderTraverse(tree->left, visit_func))
			{
				if(PreOrderTraverse(tree->right, visit_func)) 
				{
					return 1;
				}
				
			}
		}
		
		return 0;
	}
	else
	{
		return 1;
	}
}

int GetLeafNodeNum(avlnode * pRoot)
{
	if(pRoot == NULL)
		return 0;
	if(pRoot->left == NULL && pRoot->right == NULL)
		return 1;
	int numLeft = GetLeafNodeNum(pRoot->left); // 左子树中叶节点的个数
	int numRight = GetLeafNodeNum(pRoot->right); // 右子树中叶节点的个数
	return (numLeft + numRight);
}

int InOrderTraverse(avlnode *tree, visit visit_func)
{
	if(tree)
	{
		if(InOrderTraverse(tree->left, visit_func))
		{
			if(visit_func(tree->key))
			{
				if(InOrderTraverse(tree->right, visit_func)) 
				{
					return 1;
				}
			}
		}
		
		return 0;
	}
	else
	{
		return 1;
	}
}

int NextOrderTraverse(avlnode *tree, visit visit_func)
{
	if(tree)
	{
		if(NextOrderTraverse(tree->left, visit_func))
		{
			if(NextOrderTraverse(tree->right, visit_func)) 
			{
				if(visit_func(tree->key))
				{
					return 1;
				}
			}
		}
		
		return 0;
	}
	else
	{
		return 1;
	}
}

int ISAVl(avlnode *root, int *height)
{
	if(root == NULL)
	{
		*height = 0;
		return 1;
	}
	
	int heightLeft;
	int resultLeft = ISAVl(root->left, &heightLeft);
	int heightRight;
	int resultRight = ISAVl(root->right, &heightRight);
	
	*height = maxh(heightLeft, heightRight) + 1;
	if(resultLeft && resultRight && abs(heightLeft - heightRight) <= 1)
		return 1;
	else 	
		return 0;
}

int GetMaxDistance(avlnode *pRoot, int *maxLeft, int *maxRight)
{
	// *maxLeft, 左子树中的节点距离根节点的最远距离
	// *maxRight, 右子树中的节点距离根节点的最远距离
	if(pRoot == NULL)
	{
		*maxLeft = 0;
		*maxRight = 0;
		return 0;
	}
	int maxLL, maxLR, maxRL, maxRR;
	int maxDistLeft, maxDistRight;
	if(pRoot->left != NULL)
	{
		maxDistLeft = GetMaxDistance(pRoot->left, &maxLL, &maxLR);
		*maxLeft = maxh(maxLL, maxLR) + 1;
	}
	else
	{
		maxDistLeft = 0;
		*maxLeft = 0;
	}
	if(pRoot->right != NULL)
	{
		maxDistRight = GetMaxDistance(pRoot->right, &maxRL, &maxRR);
		*maxRight = maxh(maxRL, maxRR) + 1;
	}
	else
	{
		maxDistRight = 0;
		*maxRight = 0;
	}
	return maxh(maxh(maxDistLeft, maxDistRight), *maxLeft+*maxRight);
}
	
int main(int argc, char *argv[])
{
	avlnode *ptr = NULL;
	//avl_insert(&ptr, 1);
	//avl_insert(&ptr, 2);
	//avl_insert(&ptr, 3);
	//avl_insert(&ptr, 4);
	//avl_insert(&ptr, 5);

	int i;
	for(i=0; i<15; i++)
	{
		avl_insert(&ptr, i);
	}
	
	print_avl_height(&ptr);

	avl_delete(&ptr, 0);
	avl_delete(&ptr, 3);
	avl_delete(&ptr, 6);
	avl_delete(&ptr, 10);
	avl_delete(&ptr, 15);
	
	
	//search_avl_by_key(&ptr, 3);
	//search_avl_by_key(&ptr, 1);

	printf("node number: %d\n", counter_avl_tree(ptr));
	printf("tree depth: %d\n", GetDepth(ptr));
	printf("k level node number: %d\n", GetNodeNumKthLevel(ptr, 1));
	printf("leaf number: %d\n", GetLeafNodeNum(ptr));
	int height = 0;
	int rc = ISAVl(ptr, &height);
	printf("Is it a avl tree? %s\n", (rc == 1)?"yes":"no");
	
	PreOrderTraverse(ptr, PrintElement);
	
	
	printf("\n---------------\n");
	InOrderTraverse(ptr, PrintElement);
	
	printf("\n---------------\n");
	NextOrderTraverse(ptr, PrintElement);
	
	return 0;
}

