#ifndef __BINARY_SEARCH_TREE_H_
#define __BINARY_SEARCH_TREE_H_

#include "common.h"
//#define ELEMENTTYPE int

typedef struct AVLTreeNode
{ 
  ELEMENTTYPE data;
  struct AVLTreeNode * left;   /* 左子树 */
  struct AVLTreeNode * right;  /* 右子树 */
  struct AVLTreeNode * parent; /* 父结点 */

}AVLTreeNode;

typedef struct BalanceBinarySearchTree
{
   AVLTreeNode * root;  /* 根结点 */
   int size;           /* 树的结点个数 */
   int height;         /* 树的高度 */
  /* 钩子函数比较器 放到结构体内部 */
   int (*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2);

   /* 钩子函数 包装器实现自定义打印函数接口 */
   int (*printFunc)(ELEMENTTYPE val);
   

}BalanceBinarySearchTree;


/* 二叉搜索树的初始化 */
int balanceBinarySearchTreeInit(BalanceBinarySearchTree **pBstree, int (*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2), int (*printFunc)(ELEMENTTYPE val));

/* 二叉搜索树的插入 */
int balanceBinarySearchTreeInsert(BalanceBinarySearchTree *pBstree, ELEMENTTYPE val);

/* 二叉搜索树是否包含指定的元素 */
int balanceBinarySearchTreeIsContainAppointVal(BalanceBinarySearchTree *pBstree, ELEMENTTYPE val);

/* 二叉搜索树的前序遍历 */
int balanceBinarySearchTreePreOrderTravel(BalanceBinarySearchTree *pBstree);

/* 二叉搜索树的中序遍历 */
int balanceBinarySearchTreeInOrderTravel(BalanceBinarySearchTree *pBstree);

/* 二叉搜索树的后序遍历 */
int balanceBinarySearchTreePostOrderTravel(BalanceBinarySearchTree *pBstree);

/* 二叉搜索树的层序遍历 */
int balanceBinarySearchTreeLeveOrderTravel(BalanceBinarySearchTree *pBstree);

/* 获取二叉搜索树的结点个数 */
int balanceBinarySearchTreeGetNodeSize(BalanceBinarySearchTree *pBstree, int *pSize);

/* 获取二叉搜索树的高度 */
int balanceBinarySearchTreeGetHeight(BalanceBinarySearchTree *pBstree, int *pHeight);

/* 二叉搜索树的删除 */
int balanceBinarySearchTreeDelete(BalanceBinarySearchTree *pBstree, ELEMENTTYPE val);

/* 二叉搜索树的销毁 */
int balanceBinarySearchTreeDestroy(BalanceBinarySearchTree *pBstree);

/* 判断二叉搜索树是否为完全二叉搜索树 */
int balanceBinarySearchTreeIsComplete(BalanceBinarySearchTree *pBSTree);


#endif