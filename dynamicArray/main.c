#include <stdio.h>
#include "dynamicArray.h"
#include <string.h>


#define BUFFER_SIZE 20
#define DEFAULT_NUM 5
int main()
{   
    /* 静态数组: 不够灵活，可能会浪费空间 */
    
    dynamicArray array;
    /* 初始化 */
    dynamicArrayInit(&array, BUFFER_SIZE);

#if 0

{
    /* 插入数据 */
    dynamicArrayInsertData(&array, 3);
    for (int idx = 1; idx <= DEFAULT_NUM; idx++)
    {
        dynamicArrayInsertData(&array, 21);
    }
}  
    
   
{
    /* 获取动态数组的大小 */
    int size = 0;
    dynamicArrayGetSize(&array, &size);
    printf("arrayLen = %d\n", size);
}
    
{   
    /* 获取动态数组的大小 */
    int size = 0;
    dynamicArrayGetSize(&array, &size);
    /* 获取指定位置的元素数据 */
    int val = 0;
    for (int idx = 0; idx < size; idx++)
    {
       dynamicArrayGetAppointPosVal(&array, idx, &val);
       printf("val:%d\t", val);
    }
    printf("\n");
}  
    
{   
    int size = 0;
    /* 删除最后一个位置的元素 */
    dynamicArrayDeleteData(&array);
    /* 获取动态数组的大小 */
    dynamicArrayGetSize(&array, &size);
    printf("arrayLen = %d\n", size);

    int val = 0;
    for (int idx = 0; idx < size; idx++)
    {
       dynamicArrayGetAppointPosVal(&array, idx, &val);
       printf("val:%d\t", val);
    }
    printf("\n");
}


{   
    int size = 0;
    /* 删除指定位置的元素 */
    int pos = 1;
    dynamicArrayDeleteAppointPosData(&array, pos);
    /* 获取动态数组的大小 */
    dynamicArrayGetSize(&array, &size);
    printf("arrayLen = %d\n", size);

    int val = 0;
    for (int idx = 0; idx < size; idx++)
    {
       dynamicArrayGetAppointPosVal(&array, idx, &val);
       printf("val:%d\t", val);
    }
    printf("\n");
}
    
{
    /* 删除指定元素 */
    dynamicArrayDeleteAppointData(&array, 21);
    /* 获取动态数组的大小 */
    int size = 0;
    dynamicArrayGetSize(&array, &size);
    printf("arrayLen = %d\n", size);

    int val = 0;
    for (int idx = 0; idx < size; idx++)
    {
       dynamicArrayGetAppointPosVal(&array, idx, &val);
       printf("val:%d\t", val);
    }
    printf("\n");
}

#endif
    
    
    return 0;
}