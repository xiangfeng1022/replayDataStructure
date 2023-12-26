#include "binarySearchTree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* 状态码 */
enum STATUS_CODE
{
    NOT_FIND = -1,
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,

};

/* 二叉搜索树的初始化 */
int binarySearchTreeInit(BinarySearchTree **pBstree)
{
    int ret = 0;
    BinarySearchTree * bstree = (BinarySearchTree *)malloc(sizeof(BinarySearchTree) * 1);
    if (bstree == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清除脏数据 */
    memset(bstree, 0, sizeof(BinarySearchTree) * 1);
    /* 初始化树 */
    {
       bstree->root = NULL;
       bstree->size = 0;
    }
    
    #if 1
    /* 分配根结点 */
    bstree->root = (BSTreeNode *)malloc(sizeof(BSTreeNode) * 1);
    if (bstree->root == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(bstree->root, 0, sizeof(BSTreeNode) * 1);
    
    {
        bstree->root->data = 0;
        bstree->root->left = NULL;
        bstree->root->right = NULL;
        bstree->root->parent = NULL;
    }
    #endif
    
    *pBstree = bstree;
    return ret;
}

static int compareFunc(ELEMENTTYPE val1, ELEMENTTYPE val2)
{
    return val1 - val2;
}
/* 二叉搜索树的插入 */
int binarySearchTreeInsert(BinarySearchTree *pBstree, ELEMENTTYPE val)
{
    int ret = 0;
    /* 空树 */
    if (pBstree->size == 0)
    {
        /* 更新树的结点 */
        (pBstree->size)++;

        pBstree->root->data = val;
        return ret;
    }
    
    /* travelNode 指向根结点 */
    BSTreeNode * travelNode = pBstree->root;

    BSTreeNode * parentNode = pBstree->root;

    /* 确定符号 */
    int cmp = 0;
    while (travelNode != NULL)
    {   
        /* 标记父结点 */
        parentNode = travelNode;
        cmp = compareFunc(val, travelNode->data);
        /* 插入元素 < 遍历到的结点 */
        if (cmp < 0)
        {
            travelNode = travelNode->left;
        }
        else if (cmp > 0)
        {
            travelNode = travelNode->right;
        }
        else
        {   
            /* 插入元素 = 遍历到的结点 */
            return ret;
        }
    }
    
    /* 分配新结点 */
    BSTreeNode * newBstNode = (BSTreeNode *)malloc(sizeof(BSTreeNode) * 1);
    if (newBstNode == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(newBstNode, 0, sizeof(BSTreeNode) * 1);
    
    {
        newBstNode->data = 0;
        newBstNode->left = NULL;
        newBstNode->right = NULL;
        newBstNode->parent = NULL;
    }
    /* 新结点赋值 */
    newBstNode->data = val;

    /* 挂在左子树 */
    if (cmp < 0)
    {
        parentNode->left = newBstNode;
    }
    else
    {   
        /* 挂在右子树 */
        parentNode->right = newBstNode;
    }
    /* 新结点的parent指针赋值 */
    newBstNode->parent = parentNode;
    /* 更新树的结点 */
    (pBstree->size)++;
    return ret;
}