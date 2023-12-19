#include "dynamicArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_SIZE 10

/* 静态函数前置说明 */
static int expandDynamicCapacity(dynamicArray *pArray);
static int shrinkDynamicCapacity(dynamicArray *pArray);

enum STATUS_CODE
{
   ON_SUCCESS,
   NULL_PTR,
   MALLOC_ERROR,
   INVALID_ACCESS,

};

/* 动态数组的初始化 */
int dynamicArrayInit(dynamicArray *pArray, int capacity)
{
    if (pArray == NULL)
    {
        return NULL_PTR;
    }
    
    /* 避免传入非法值 */
    if (capacity < 0)
    {
        capacity = DEFAULT_SIZE;
    }
    
    /* 分配空间 */
    pArray->data = (ELEMENTTYPE *)malloc(sizeof(ELEMENTTYPE) * capacity);
    if (pArray->data == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清除脏数据 */
    memset(pArray->data, 0, sizeof(ELEMENTTYPE) * capacity);
    
    /* 初始化动态数组的参数属性 */
    pArray->len = 0;
    pArray->capacity = capacity;

    return ON_SUCCESS;
}

/* 动态数组插入数据(默认插到数组的末尾) */
int dynamicArrayInsertData(dynamicArray *pArray, ELEMENTTYPE val)
{
    return dynamicArrayAppointPosInsertData(pArray, pArray->len, val);
}

/* 动态数组扩容 */
static int expandDynamicCapacity(dynamicArray *pArray)
{
    int ret = 0;
    int needExpandCapacity = pArray->capacity + (pArray->capacity >> 1);
    
    /* 备份指针 */
    ELEMENTTYPE *tmpPtr = pArray->data;
    pArray->data = (ELEMENTTYPE *)malloc(sizeof(ELEMENTTYPE) * needExpandCapacity);
    if (pArray->data == NULL)
    {
        return MALLOC_ERROR;
    }

    /* 把之前的数据全部拷贝过来 */
    for (int idx =0; idx < pArray->len; idx++)
    {
        pArray->data[idx] = tmpPtr[idx];
    }

    /* 释放以前的内存 避免内存泄漏 */
    if (tmpPtr != NULL)
    {
        free(tmpPtr);
        tmpPtr = NULL;
    }
    
    /* 更新动态数组的容量 */
    pArray->capacity = needExpandCapacity;

    return ret;
}

/* 动态数组插入数据，在指定位置插入 */
int dynamicArrayAppointPosInsertData(dynamicArray *pArray, int pos, ELEMENTTYPE val)
{   
    /* 指针判空 */
    if (pArray == NULL)
    {
        return NULL_PTR;
    }
    
    /* 判断位置的合法性 */
    if (pos < 0 || pos > pArray->len)
    {
        return INVALID_ACCESS;
    }
    
    if ((pArray->len + (pArray->len >> 1)) >= pArray->capacity)
    {
       /* 开始扩容 */
       expandDynamicCapacity(pArray);
    }
    
    /* 数据后移 留出pos位置插入 */
    for (int idx = pArray->len; idx > pos; idx--)
    {
        pArray->data[idx] = pArray->data[idx - 1];
    }
    
    /* 找到对应的值 写入到数组中 */
    pArray->data[pos] = val;

    /* 数组的大小加一 */
    (pArray->len)++;

    return ON_SUCCESS;
}

/* 动态数组修改指定位置的数据 */
int dynamicArrayModifyAppointPosData(dynamicArray *pArray, int pos, ELEMENTTYPE val)
{   
    /* 指针判空 */
    if (pArray == NULL)
    {
        return NULL_PTR;
    }
    
    /* 判断位置的合法性 */
    if (pos < 0 || pos >= pArray->len)
    {
        return INVALID_ACCESS;
    }
   
    /* 更新位置的数据 */
    pArray->data[pos] = val;

    return ON_SUCCESS;
}

/* 动态数组删除数据(默认删除末尾的数据) */
int dynamicArrayDeleteData(dynamicArray *pArray)
{
    return dynamicArrayDeleteAppointPosData(pArray, pArray->len - 1);
}

static int shrinkDynamicCapacity(dynamicArray *pArray)
{
    // if (pArray == NULL)
    // {
    //     return NULL_PTR;
    // }  不需要判空 因为我这个接口不提供给外部使用

    int needShrinkCapacity = pArray->capacity - (pArray->capacity >> 1);

    ELEMENTTYPE *tmpPtr = pArray->data;
    pArray->data = (ELEMENTTYPE *)malloc(sizeof(ELEMENTTYPE) * needShrinkCapacity);
    if (pArray->data == NULL)
    {
        return MALLOC_ERROR;
    }
    
    /* 拷贝之前的数据到新的空间 */
    for (int idx = 0; idx < pArray->len; idx++)
    {
        pArray->data[idx] = tmpPtr[idx];
    }
    
    /* 释放内存空间 避免内存泄漏 */
    if (tmpPtr != NULL)
    {
        free(tmpPtr);
        tmpPtr = NULL;
    }
    /* 更新容量 */
    pArray->capacity = needShrinkCapacity;

    return ON_SUCCESS;

}

/* 动态数组删除指定位置数据 */
int dynamicArrayDeleteAppointPosData(dynamicArray *pArray, int pos)
{   
    /* 指针判空 */
    if (pArray == NULL)
    {
        return NULL_PTR;
    }
    
    /* 判断位置的合法性 */
    if (pos < 0 || pos >= pArray->len)
    {
        return INVALID_ACCESS;
    }
    
    /* 缩容*/
    if (pArray->len < (pArray->capacity >> 1)) //当容量减半还大于len
    {
        shrinkDynamicCapacity(pArray);
    }

    /* 数据前移 */
    for (int idx = pos; idx < pArray->len; idx++)
    {
         pArray->data[idx] = pArray->data[idx + 1];
    }
    
    /* 更新数组的大小 */
    (pArray->len)--;

    return ON_SUCCESS;
}

/* 动态数组删除指定的元素 */
int dynamicArrayDeleteAppointData(dynamicArray *pArray, ELEMENTTYPE val)
{
    if (pArray == NULL)
    {
        return NULL_PTR;
    }

    for (int idx = pArray->len - 1; idx >= 0; idx--)
    {
        if (val == pArray->data[idx])
        {
            dynamicArrayDeleteAppointPosData(pArray, idx);
        }
    }

    return ON_SUCCESS;
}

/* 动态数组的销毁 */
int dynamicArrayDestroy(dynamicArray *pArray)
{
    if (pArray == NULL)
    {
        return NULL_PTR;
    }

    if (pArray->data != NULL)
    {
        free(pArray->data);
        pArray->data = NULL;
    }
    return ON_SUCCESS;
}

/* 获取数组的大小 */
int dynamicArrayGetSize(dynamicArray *pArray, int *pSize)
{
    if (pArray == NULL || pSize == NULL)
    {
        return NULL_PTR;
    }

    /* 解引用 */
    if (pSize != NULL)
    {
        *pSize = pArray->len;
    }
    
    return ON_SUCCESS;
}

/* 获取数组的容量 */
int dynamicArrayGetCapacity(dynamicArray *pArray, int *pCapacity)
{
    if (pArray == NULL || pCapacity == NULL)
    {
        return NULL_PTR;
    }

    if (pCapacity != NULL)
    {
        *pCapacity = pArray->capacity;
    }
    
    return ON_SUCCESS;
}

