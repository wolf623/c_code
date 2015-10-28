#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int keyType;

struct BinaryTreeNode {
	keyType key;
	int height; //记录以该节点为root的树高度
	struct BinaryTreeNode *left; // left child
	struct BinaryTreeNode *right; // right child
};

// define AVL node
typedef struct BinaryTreeNode avlnode;

// define AVL tree
typedef struct BinaryTreeNode avltree;

// 比较左右子树高度，取最大的
int maxh(int ha, int hb) {
	return ha > hb ? ha : hb;
}

// 计算树的高度
int height(avltree* tree) 
{
	if (NULL == tree) 
		return 0;
	else
		return tree->height;
}
