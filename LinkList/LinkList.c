#include "LinkList.h"
#include <stdlib.h>
#include <string.h>

enum STATUS_CODE
{
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,

};

/* 链表初始化 */
int LinkListInit(LinkList **pList)
{
    int ret = 0;
    LinkList *list = (LinkList *)malloc(sizeof(LinkList) * 1);
    if (list == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(list, 0, sizeof(LinkList) * 1);

    list->head = (LinkNode *)malloc(sizeof(LinkNode) * 1);
    if (list->head == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(list->head, 0, sizeof(LinkNode) * 1);
    list->head->data = 0;
    list->head->next = NULL;

    /* 初始化的时候， 尾指针 = 头指针 */
    list->tail = list->head;

    /* 链表的长度为0 */
    list->len = 0;

    /* 二级指针 */
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
    LinkNode *newNode = (LinkNode *)malloc(sizeof(LinkNode) * 1);
    if (newNode == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(newNode, 0, sizeof(LinkNode) * 1);
    newNode->data = 0;
    newNode->next = NULL;

    /* 赋值 */
    newNode->data = val;

#if 1
    /* 从虚拟头结点开始遍历 */
    LinkNode *travelNode = pList->head;
#else
    LinkNode *travelNode = pList->head->next;
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
   LinkNode * travelNode = pList->head;
#else
    LinkNode * travelNode = pList->tail;
#endif
   while (--pos)
   { 
     /* 向后移动位置 */
     travelNode = travelNode->next;
     
   }
   //跳出循环找到的是哪一个结点
   LinkNode * needDelNode = travelNode->next;
   travelNode->next = needDelNode->next;

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

/* 链表删除指定数据 */
int LinkListDelAppointData(LinkList *pList, ELEMENTTYPE val)
{
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
int LinkListForeach(LinkList *pList)
{
    int ret = 0;
    if (pList == NULL)
    {
        return NULL_PTR;
    }

#if 0
   /* travelNode指向虚拟头结点*/
   LinkNode * travelNode = pList->head;
   while (travelNode->next != NULL)
   {
      travelNode = travelNode->next;
      printf("travelNode->data:%d\n", travelNode->data);
   }
#else

    /* travelNode指向链表第一个元素 */
    LinkNode *travelNode = pList->head->next;
    while (travelNode->next != NULL)
    {
        printf("travelNode->data:%d\n", travelNode->data);
        travelNode = travelNode->next;
    }

#endif

    return ret;
}