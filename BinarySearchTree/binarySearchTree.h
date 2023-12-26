#ifndef __BINARY_SEARCH_TREE_H_
#define __BINARY_SEARCH_TREE_H_

#define ELEMENTTYPE int

typedef struct BSTreeNode
{ 
  ELEMENTTYPE data;
  BSTreeNode * left;   /* 左子树 */
  BSTreeNode * right;  /* 右子树 */
  BSTreeNode * parent; /* 父结点 */

}BSTreeNode;

typedef struct BinarySearchTree
{
   BSTreeNode * root;  /* 根结点 */
   int size;           /* 树的结点个数 */
   int height;         /* 树的高度 */
}BinarySearchTree;


/* 二叉搜索树的初始化 */
int binarySearchTreeInit(BinarySearchTree **pBstree);

/* 二叉搜索树的插入 */
int binarySearchTreeInsert(BinarySearchTree *pBstree, ELEMENTTYPE val, int (*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2));

/* 二叉搜索树的前序遍历 */
int binarySearchTreePreOrderTravel(BinarySearchTree *pBstree);

/* 二叉搜索树的中序遍历 */
int binarySearchTreeInOrderTravel(BinarySearchTree *pBstree);

/* 二叉搜索树的后序遍历 */
int binarySearchTreePostOrderTravel(BinarySearchTree *pBstree);

/* 二叉搜索树的层序遍历 */
int binarySearchTreeLeveOrderTravel(BinarySearchTree *pBstree);

#endif