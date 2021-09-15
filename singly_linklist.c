//单向链表(结点的数据域可以是任何类型的)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//结点结构体
struct linkNode
{
    //数据域
    void *data; //因为不确定数据是什么类型的
    //指针域
    struct linkNode *next;
};

//链表的结构体(这个结构体是不能给用户操作的)
struct llist
{
    struct linkNode pHeader; //头结点
    int size; //链表长度
};

typedef void * linklist; //将void *类型定义为linklist

//初始化链表
linklist init_list(){ //把返回的链表结构体指针转换成了void指针，以防用户操作链表结构体
    struct llist *myList=malloc(sizeof(struct linkNode));
    if (myList==NULL)
    {
        return NULL; //初始化失败返回空值
    }
    
    //初始化链表结构体中的内容
    myList->pHeader.data=NULL;
    myList->pHeader.next=NULL;
    myList->size=0;

    return myList;
}

//插入链表
void insert_list(linklist list,int pos,void *data){
    if (list==NULL)
    {
        return;
    }
    if (data==NULL)
    {
        return;
    }
    //将list还原成 struct LList数据类型
    struct llist *myList=list;
    //pos是无效位置，就尾插
    if (pos<0||pos>myList->size)
    {
        pos=myList->size;
    }
    
    //循环找被插入位置结点的前驱结点
    struct linkNode *pCurrent=&myList->pHeader;
    for (int i = 0; i < pos; i++)
    {
        pCurrent=pCurrent->next;
    }
    
    //创建新结点
    struct linkNode *pNewnode=malloc(sizeof(struct linkNode));
    pNewnode->data=data;
    pNewnode->next=NULL;

    //建立结点关系
    pNewnode->next=pCurrent->next;
    pCurrent->next=pNewnode;

    //更新链表长度
    myList->size++;
}

//删除 按位置
void remove_list(linklist list,int pos){
    if (list==NULL)
    {
        return;
    }
    struct llist *myList=list;

    if (pos<0||pos>myList->size)
    {
        return;
    }
    struct linkNode *pCurrent=&myList->pHeader;

    //遍历链表寻找删除位置的前驱
    for (int i = 0; i < pos; i++)
    {
        pCurrent=pCurrent->next;
    }
    
    struct linkNode *pDlnode=pCurrent->next; //记录要删除的结点

    //更改指针
     pCurrent->next=pDlnode->next;

     free(pDlnode);
     pDlnode=NULL;
     myList->size--;

}

//按照值删除链表
void removeByValue_LinkList(linklist list , void * data,int(*myCompare)(void * ,void *))
{
	if (list == NULL)
	{
		return;
	}
	if ( data == NULL)
	{
		return;
	}

	struct llist * mylist = list;
	//创建两个辅助指针
	struct linkNode * pPrev = &mylist->pHeader;
	struct linkNode * pCurrent = pPrev->next;

	for (int i = 0; i < mylist->size;i++)
	{
		//pCurrent->data  data 将两个指针比较利用回调 交给用户
		if (myCompare (pCurrent->data,data))
		{
			pPrev->next = pCurrent->next;

			free(pCurrent);
			pCurrent = NULL;

			mylist->size--;
			break;
		}

		//辅助指针后移
		pPrev = pCurrent;
		pCurrent = pCurrent->next;
	}
}
//遍历链表
void foreach_list(linklist list,void(*myPrint)(void *)){
    if (list==NULL)
    {
        return;
    }
    struct llist *myList=list;
    struct linkNode *pCurrent=myList->pHeader.next; //pCurrent作为遍历节点指向当前第一个结点

    for (int i = 0; i < myList->size; i++)
    {   
        myPrint(pCurrent->data);
        pCurrent=pCurrent->next;
    }
    
}

//返回链表长度
void size_list(linklist list){
    if (list==NULL)
    {
        return;
    }
    struct llist *mylist=list;
    return mylist->size;
}

//清空链表
void clear_list(linklist list){
    if (list==NULL)
    {
        return;
    }
    struct llist *mylist=list;
    struct linkNode *pCurrent=mylist->pHeader.next;
    for (int i = 0; i < mylist->size; i++)
    {
        struct linkNode *pNext=pCurrent->next;
        free(pCurrent);
        pCurrent=pNext;
    }
    mylist->pHeader.next=NULL; 
    mylist->size=0;
}

//销毁链表
void destroy_list(linklist list){
    if (list==NULL)
    {
        return;
    }
    
    //清空链表
    clear_list(list);

    free(list);
    list=NULL;
}

//回调函数
int myComparePerson(void * data1, void *data2)
{
	struct Person * p1 = data1;
	struct Person * p2 = data2;

	return strcmp(p1->name, p2->name) == 0 && p1->age == p2->age;
}






//测试 
struct Person
{
	char name[64];
	int age;
};

void myPrintPerson(void * data)
{
	struct Person * p = data;
	printf("姓名：%s  年龄：%d\n", p->name, p->age);
}

void test01()
{
	//准备数据
	struct Person p1 = { "亚瑟", 18 };
	struct Person p2 = { "妲己", 20 };
	struct Person p3 = { "安琪拉", 19 };
	struct Person p4 = { "凯", 21 };
	struct Person p5 = { "孙悟空", 999 };
	struct Person p6 = { "李白", 999 };

	//初始化链表
	linklist mylist = init_list();

	//printf("链表长度为：%d\n", size_LinkList(mylist));

	//插入数据
	insert_list(mylist, 0, &p1);
	insert_list(mylist, 0, &p2);
	insert_list(mylist, -1, &p3);
	insert_list(mylist, 0, &p4);
	insert_list(mylist, 1, &p5);
	insert_list(mylist, 0, &p6);


	// 李白 凯 孙悟空 妲己 亚瑟 安琪拉

	//遍历
	foreach_list(mylist, myPrintPerson);

    printf("-------------\n");
    //删除结点
    remove_list(mylist,2);

    //struct Person p = { "孙悟空", 999 };
    //removeByValue_LinkList(mylist,&p);

    //foreach_list(mylist, myPrintPerson);
    //clear_list(mylist);
    foreach_list(mylist, myPrintPerson);
}

int main()
{   
    test01();
    return 0;
}