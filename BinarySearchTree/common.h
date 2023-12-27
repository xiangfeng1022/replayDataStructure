#ifndef __COMMON_H_
#define __COMMON_H_

#define ELEMENTTYPE void*

/* 链表结点取别名 */
typedef struct DoubleLinkNode
{
    ELEMENTTYPE data;
    /* 指向下一个结点的指针 */
    struct DoubleLinkNode *next; /* 指针的类型为什么是结点 */
    struct DoubleLinkNode *prev;  
} DoubleLinkNode;

/* 链表 */
typedef struct DoubleLinkList
{  
   /* 链表的虚拟头结点:数据域无意义 只使用指针域*/    
   DoubleLinkNode * head;
   DoubleLinkNode * tail;    /* 为什么尾指针不需要分配空间??? :*/
   int len;  /* 链表的长度 */

}DoubleLinkList;

#endif