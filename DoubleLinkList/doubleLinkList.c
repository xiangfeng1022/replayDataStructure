#include "doubleLinkList.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

enum STATUS_CODE
{
    NOT_FIND = -1,
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,

};

/* 静态前置说明 */
/* 静态函数只在本源文件(.c)中使用 */
static int LinkListAccordAppointValGetPos(LinkList *pList, ELEMENTTYPE val, int *pPos);

/* 链表初始化 */
int LinkListInit(LinkList **pList)
{
    int ret = 0;

    /*  分配链表结构体的内存并进行初始化 
        list 是一个指向 LinkList 结构体的指针，它代表了一个链表的头指针。
    */
    LinkList *list = (LinkList *)malloc(sizeof(LinkList) * 1);
    if (list == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(list, 0, sizeof(LinkList) * 1);
    
    /* 分配链表头节点的内存并进行初始化 */
    list->head = (DoubleLinkNode *)malloc(sizeof(DoubleLinkNode) * 1);
    if (list->head == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(list->head, 0, sizeof(DoubleLinkNode) * 1);
    list->head->data = 0;
    list->head->next = NULL;

    /* 初始化的时候， 尾指针 = 头指针 */
    list->tail = list->head;

    /* 链表的长度为0 */
    list->len = 0;

    /* 二级指针 将链表的头指针赋值给二级指针 pList */
    *pList = list;

    return ret;
}

/* 链表头插 */
int LinkListHeadInsert(LinkList *pList, ELEMENTTYPE val)
{
    return LinkListAppointPosInsert(pList, 0, val);
}

/* 链表尾插 */
int LinkListTailInsert(LinkList *pList, ELEMENTTYPE val)
{
    return LinkListAppointPosInsert(pList, pList->len, val);
}

/* 链表指定位置插入 */
int LinkListAppointPosInsert(LinkList *pList, int pos, ELEMENTTYPE val)
{

    int ret = 0;
    if (pList == NULL)
    {
        return NULL_PTR;
    }

    if (pos < 0 || pos > pList->len)
    {
        return INVALID_ACCESS;
    }

    /* 把要插入的值封装成一个节点 */
    DoubleLinkNode *newNode = (DoubleLinkNode *)malloc(sizeof(DoubleLinkNode) * 1);
    if (newNode == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(newNode, 0, sizeof(DoubleLinkNode) * 1);
    newNode->data = 0;
    newNode->next = NULL;

    /* 赋值 */
    newNode->data = val;

#if 1
    /* 从虚拟头结点开始遍历 */
    DoubleLinkNode *travelNode = pList->head;
#else
    DoubleLinkNode *travelNode = pList->head->next;
#endif

    int flag = 0;
    /* 这种情况下需要更改尾指针 */
    if (pos == pList->len)
    {
        /* 修改结点指向 */
        travelNode = pList->tail;
        flag = 1;
    }
    else
    {
        while (pos)
        {
            travelNode = travelNode->next;
            pos--;
        }
    }

    newNode->next = travelNode->next;
    travelNode->next = newNode;

    if (flag)
    {
        /* 尾指针更新位置 */
        pList->tail = newNode;
    }

    /* 更新链表长度 */
    (pList->len)++;

    return ret;
}

/* 链表头删 */
int LinkListHeadDel(LinkList *pList)
{
    return LinkListDelAppointPos(pList, 1);
}

/* 链表尾删 */
int LinkListTailDel(LinkList *pList)
{
    return LinkListDelAppointPos(pList, pList->len);
}

/* 链表删除指定位置 */
int LinkListDelAppointPos(LinkList *pList, int pos)
{
    int ret = 0;
    if (pList == NULL)
    {
        return NULL_PTR;
    }

    if (pos <= 0 || pos > pList->len)
    {
        return INVALID_ACCESS;
    }

#if 1
    DoubleLinkNode *travelNode = pList->head;
#else
    DoubleLinkNode *travelNode = pList->tail;
#endif
    int flag = 0;
    /* 需要修改尾指针 */
    if (pos == pList->len)
    {
        flag = 1;
    }
    
    DoubleLinkNode *needDelNode = NULL;
    while (--pos)
    {
        /* 向后移动位置 */
        travelNode = travelNode->next;
    }
    // 跳出循环找到的是哪一个结点
    needDelNode = travelNode->next;
    travelNode->next = needDelNode->next;

    if (flag)
    {
        /* 调整尾指针 */
        pList->tail = travelNode;
    }

    /* 释放内存 */
    if (needDelNode != NULL)
    {
        free(needDelNode);
        needDelNode = NULL;
    }

    /* 链表长度减一 */
    (pList->len)--;

    return ret;
}


static int LinkListAccordAppointValGetPos(LinkList *pList, ELEMENTTYPE val, int *pPos)
{
    /* 静态函数只给本源文件的函数使用，不需要判断合法性 */
    int ret;
#if 0
    int pos = 0; 
    DoubleLinkNode * travelNode = pList->head;
#else
    int pos = 1;
    DoubleLinkNode *travelNode = pList->head->next;
#endif

    while (travelNode != NULL)
    {
        if (travelNode->data == val)
        {
            /* 解引用 */
            *pPos = pos;
            return pos;
        }
        travelNode = travelNode->next;
        pos++;
    }
    /* 解引用 */
    *pPos = NOT_FIND;
    return NOT_FIND;
}
/* 链表删除指定数据 */
int LinkListDelAppointData(LinkList *pList, ELEMENTTYPE val, int (*compareFunc)(ELEMENTTYPE, ELEMENTTYPE))
{
    int ret = 0;

    /* 元素链表中的位置 */
    int pos = 0;

    /* 链表的长度 */
    int size = 0;
    while (LinkListGetLength(pList, &size) && pos != NOT_FIND)
    {
        /* 根据指定的元素得到在链表中所在的位置 */
        int pos = 0;
        LinkListAccordAppointValGetPos(pList, val, &pos);
        LinkListDelAppointPos(pList, pos);
    }
    return ret;
}

/* 获取链表的长度 */
int LinkListGetLength(LinkList *pList, int *pSize)
{
    int ret = 0;
    if (pList == NULL)
    {
        return NULL_PTR;
    }

    if (pSize)
    {
        *pSize = pList->len;
    }
    /* 返回链表的长度 */
    return pList->len;
}

/* 链表的销毁 */
int LinkListDestroy(LinkList *pList)
{
    int ret = 0;
    /* 我们使用头删释放链表 */
    int size = 0;
    while (LinkListGetLength(pList, &size))
    {
        LinkListHeadDel(pList);
    }

    if (pList->head != NULL)
    {
        free(pList->head);
        /* 指针置为NULL */
        pList->head == NULL;
        pList->tail = NULL;
    }
    return ret;
}

/* 链表遍历接口 */
int LinkListForeach(LinkList *pList, int (*printFunc)(ELEMENTTYPE))
{
    int ret = 0;
    if (pList == NULL)
    {
        return NULL_PTR;
    }

#if 0
   /* travelNode指向虚拟头结点*/
   DoubleLinkNode * travelNode = pList->head;
   while (travelNode->next != NULL)
   {
      travelNode = travelNode->next;
      printf("travelNode->data:%d\n", travelNode->data);
   }
#else

    /* travelNode指向链表第一个元素 */
    DoubleLinkNode *travelNode = pList->head->next;
    while (travelNode != NULL)
    {   
#if 0
        printf("travelNode->data:%d\n", travelNode->data);
#else
        /* 包装器 钩子 回调函数 */
        printFunc(travelNode->data);
#endif
        travelNode = travelNode->next;
    }

#endif

    return ret;

}