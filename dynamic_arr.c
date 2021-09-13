//动态数组的设计和实现
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//动态数组结构体
struct dynamic_arr
{
    void **pArry;
    int maxsize; //数组容量
    int size; //数组大小
};

//初始化动态数组
struct dynamic_arr * init_arr(int maxsize){
    if (maxsize<=0)
    {
        return  NULL;
    }
    //给数组分配空间
    struct dynamic_arr *arry=malloc(sizeof(struct dynamic_arr)); //arry是指向结构体的指针

    //给数组初始化
    arry->pArry=malloc(sizeof(void *) *maxsize);//把真实的数据开辟到堆区（之所以是void*，是因为不知道存放在数组中的元素类型是什么。）
    arry->maxsize=maxsize;
    arry->size=0;
    return arry;
}

//数组的插入
void insert(struct dynamic_arr *pArr,int pos,void *data){ //pos是插入位置，data是插入的数据
    if (pArr==NULL)
    {
        return;
    }
    if (data==NULL)
    {
        return;
    }
    //插入位置非法就尾插
    if (pos<0||pos>pArr->size)
    {
        pos=pArr->maxsize;
    }
    
    //当前数组满了之后扩容
    if (pArr->size==pArr->maxsize)
    {
        //1.计算新空间大小
        int newMaxsize=pArr->maxsize*2;

        //2.为新数据开辟新空间
        void **newParr=malloc(sizeof(void *)*newMaxsize);

        //3.将原来数据拷贝至新空间
        memcpy(newParr,pArr->pArry,sizeof(void*)*pArr->maxsize);

        //4.释放原有内存空间
        free(pArr->pArry);

        //5.更新新空间指向
        pArr->pArry=newParr;

        //6.更新新容量
        pArr->maxsize=newMaxsize;
        
    }
    //插入新元素
    for (int i = pArr->size-1; i >=pos; i--)
    {
        //数据向后移动
        pArr->pArry[i+1]=pArr->pArry[i];
    }
    pArr->pArry[pos]=data; //插入新元素
    pArr->size++; //更新数组中元素的个数
}

//遍历数组
void foreach(struct dynamic_arr *pArr,void(*myPrint)(void *)){ //第二个参数是回调函数
    for (int i = 0; i < pArr->size; i++)
    {
       myPrint(pArr->pArry[i]);
    }
    
}
int main()
{   
    //初始化动态数组
    struct dynamic_arr *arry=init_arr(5);
    printf("容量：%d 大小：%d\n",arry->maxsize,arry->size);
    //printf("%d",sizeof(struct dynamic_arr));
    return 0;
}