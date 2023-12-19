#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 结构体
   什么叫结构体:将不同类型的属性封装成一个类型
   怎么定义结构体？
   怎么使用结构体？
   结构体默认字节对齐:读取速度快，但是浪费空间
   结构的位域到网络编程的时候在研究
   变长结构体
   typedef取别名
   结构体做函数参数
*/
/*总结:
      1、字符串: 形参不加const就是传出参数（就是要被修改的值)
                加上const就是传入参数(不能被改变)
      2、 整数: 加上指针就是传出参数（就是要被修改的值)
               不加指针就是传入参数（能被修改 但不会影响实参)
*/
#define BUFFER_SIZE 16
#define DEFAULT_NUM 2

typedef struct stuInfo
{
    int age;
    int height;
    int weight;
    char sex;
    char name[BUFFER_SIZE];
    char *address;

} stuInfo;

#if 0
/* 函数: 结构体做函数参数 */
int printStruct(stuInfo stu)
{   
    /* 栈空间小的很，不允许超过8M*/
    stu.age = 100; /* 值传递 在这修改不影响实参的值 */
    printf("stu.age = %d\tstu.height = %d\tstu.weight = %d\tstu.sex = %c\tstu.name = %s\n",
            stu.age, stu.height, stu.weight, stu.sex, stu.name);
    return 0;
}

#else

/* 结构体数组做函数参数 */
int printStructBuffer(stuInfo *stu, int stuSize)
{   
    for (int idx = 0; idx < stuSize; idx++)
    {
       printf("stu.age = %d\tstu.height = %d\tstu.weight = %d\tstu.sex = %c\tstu.name = %s\n",
            stu[idx].age, stu[idx].height, stu[idx].weight, stu[idx].sex, stu[idx].name);
    }

    return 0;
}

int printStruct(const stuInfo *stu)  
{   
    /* int printStruct(stuInfo *stu) 是传出参数会修改实参值*/
    /* int printStruct(const stuInfo *stu) 是传入参数不会修改实参值*/
    /* 结构体必须用指针 */
    int ret = 0;
    int len = sizeof(stu);
    printf("len = %d\n", len);

    return 0;
}

#endif

int main()
{
    /* 怎么使用结构体 */
    stuInfo stu;
    memset(&stu, 0, sizeof(stu));

    /* 结构体的大小 字节对齐 */
    int len = sizeof(stu);
    printf("len = %d\n", len);
#if 0
    stu.age = 10;
    stu.height = 180;
    stu.weight = 120;
    stu.sex = 'm';
    //stu.name = "zhangsan";错误的 name数组名是指针常量 不可以修改
    strncpy(stu.name, "zhangsan", sizeof(stu.name) - 1);
    printf("stu.age = %d\tstu.height = %d\tstu.weight = %d\tstu.sex = %c\tstu.name = %s\n",
            stu.age, stu.height, stu.weight, stu.sex, stu.name);
#endif

#if 0
    /* 结构体数组 */
    stuInfo buffer[DEFAULT_NUM];
    printf("buffer = %ld\n", sizeof(buffer));  //64
    printf("buffer[0] = %ld\n", sizeof(buffer[0])); //32

    buffer[0].age = 10;
    buffer[0].height = 180;
    buffer[0].weight = 120;
    buffer[0].sex = 'm';
    strncpy(buffer[0].name, "xiangfeng", sizeof(buffer[0].name) - 1);
    printf("buffer[0].age = %d\tbuffer[0].height = %d\tbuffer[0].weight = %d\tbuffer[0].sex = %c\tbuffer[0].name = %s\n",
            buffer[0].age, buffer[0].height, buffer[0].weight, buffer[0].sex, buffer[0].name);
    

    buffer[1].age = 6;
    buffer[1].height = 160;
    buffer[1].weight = 20;
    buffer[1].sex = 'f';
    strncpy(buffer[1].name, "zhangsan", sizeof(buffer[1].name) - 1);
    printf("buffer[1].age = %d\tbuffer[1].height = %d\tbuffer[1].weight = %d\tbuffer[1].sex = %c\tbuffer[1].name = %s\n",
            buffer[1].age, buffer[1].height, buffer[1].weight, buffer[1].sex, buffer[1].name);
    
#endif

#if 0
    /* 结构体指针 */
    /* 结构体指针 读数据 写数据 都是-> */
    stuInfo * info = &stu;
    info->age = 30;
    printf("info->age = %d\n", info->age);
    printf("stu.age = %d\n", stu.age);
    
    /* 结构体里有指针， 必须分配空间 */
    stu.address = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    

#endif

#if 0
    
    /* 结构体做函数 */
    stu.age = 10;
    stu.height = 1;
    stu.weight = 1;
    stu.sex = 'm';
    //stu.name = "zhangsan";错误的 name数组名是指针常量 不可以修改
    strncpy(stu.name, "zhangsan", sizeof(stu.name) - 1);
    
    printStruct(&stu);
    

#endif

#if 0
    stuInfo buffer[DEFAULT_NUM];

    buffer[0].age = 10;
    buffer[0].height = 180;
    buffer[0].weight = 120;
    buffer[0].sex = 'm';
    strncpy(buffer[0].name, "xiangfeng", sizeof(buffer[0].name) - 1);
    
    buffer[1].age = 6;
    buffer[1].height = 160;
    buffer[1].weight = 20;
    buffer[1].sex = 'f';
    strncpy(buffer[1].name, "zhangsan", sizeof(buffer[1].name) - 1);

    printStructBuffer(buffer, sizeof(buffer) / sizeof(buffer[0]));

#endif

    return 0;
}