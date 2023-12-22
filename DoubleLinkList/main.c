#include <stdio.h>
#include "doubleLinkList.h"
#include <string.h>

/* 动态数组和链表的区别
    静态数组: 不够灵活，可能会浪费空间 在栈区开辟一块连续的内存
    动态数组：在堆区开辟一块连续的内存：
    好处：插到末尾的速度很快
    坏处: 在指定位置插入删除元素，会使得后面的元素全部后移前移，很浪费时间


    链表是不连续的内存空间
    每个结点在需要的时候才会分配空间：
    好处：节省空间 插入删除速度很快
    坏处：查找元素的时候会慢(效率低)

*/
#define BUFFER_SIZE 3

typedef struct stuInfo
{
    int age;
    char sex;

} stuInfo;

/* 自定义打印 */
int printStruct(void *arg)
{
   stuInfo *info = (stuInfo*)arg;
   printf("age:%d\t, sex:%c\n", info->age, info->sex);

}

int printBasicData(void *arg)
{
    int data = *(int *)arg;
    printf("data:%d\n", data);
}

int main()
{
    LinkList *list = NULL;
    /* 初始化链表 */
    LinkListInit(&list);
#if 0
    int buffer[BUFFER_SIZE] = {1, 2, 3};
    /* 插入数据 */
    for (int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        LinkListHeadInsert(list, (void *)&buffer[idx]);
    }

    /* 获取链表的长度 */
    int size = 0;
    LinkListGetLength(list, &size);
    printf("size:%d\n", size);
    
   LinkListForeach(list, printBasicData);
#else
          stuInfo stu1, stu2, stu3;
          memset(&stu1, 0, sizeof(stu1));
          memset(&stu2, 0, sizeof(stu2));
          memset(&stu3, 0, sizeof(stu3));

          stu1.age = 10;
          stu1.sex = 'm';

          stu2.age = 20;
          stu2.sex = 'f';

          stu3.age = 30;
          stu3.sex = 'm';

          stuInfo buffer[BUFFER_SIZE] = {stu1, stu2, stu3};
         
         for (int idx = 0; idx < BUFFER_SIZE; idx++)
         {
            LinkListHeadInsert(list, (void *)&buffer[idx]);
         }
         
         /* 获取链表的长度 */
        int size = 0;
        LinkListGetLength(list, &size);
        printf("size:%d\n", size);
        
        /* 遍历 */
        LinkListForeach(list, printStruct);
#endif

    return 0;
}