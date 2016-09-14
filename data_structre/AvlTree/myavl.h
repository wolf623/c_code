#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int keyType;

struct BinaryTreeNode {
	keyType key;
	int height; //��¼�Ըýڵ�Ϊroot�����߶�
	struct BinaryTreeNode *left; // left child
	struct BinaryTreeNode *right; // right child
};

// define AVL node
typedef struct BinaryTreeNode avlnode;

// define AVL tree
typedef struct BinaryTreeNode avltree;

// �Ƚ����������߶ȣ�ȡ����
int maxh(int ha, int hb) {
	return ha > hb ? ha : hb;
}

// �������ĸ߶�
int height(avltree* tree) 
{
	if (NULL == tree) 
		return 0;
	else
		return tree->height;
}
