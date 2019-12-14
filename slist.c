/*================================================================
*   Copyright (C) 2019 belonging to YangZhengQing. All rights reserved.
*   
*   文件名称：slist.c
*   创 建 者：YangZhengQing
*   创建日期：2019年12月01日
*   描    述：实现单项链表
*
*================================================================*/

#include "slist.h"
#include "malloc.h"
#include "errno.h"

/*定义节点*/
struct linked
{
    int val;
    struct linked *next;
};

int main(int argc,char **argv)
{
	struct linked *head = NULL;
	int               i =  0;
	
	while(i < 5)//创建链表
	{
		head = add_node(head,i);
		i++;
	}
	

	//head = front_add_node(head,5);

	printf("打印已创建的链表：\n");
	display_list(head);//打印创建好的链表
	
	//delete_node(head,2);//删除第二个节点

	//insert_node(head,2);//插入一个节点

	//display_list(head);//打印删除并插入一个节点后的链表

	head = reversed_order(head);//逆序

	printf("打印逆序之后的链表：\n");

	display_list(head);//打印逆序之后的链表

	delete_list(head);//释放链表所占内存
	
	return 0;

}

/*顺序添加节点*/
struct linked *add_node(struct linked *head, int val )
{
	struct linked *p,*pr = head;//pr、head都指向头节点
	
	p = (struct linked*)malloc(sizeof(struct linked));//分配节点内存

	if(p == NULL)//判断内存是否分配成功
	{
		printf("分配内存失败!\n");
		exit(0);
	}

	else if(head == NULL)//创建第一个头节点的时候，头指针为空，将头指针指向头节点；创建第二个节点之后，头指针不再为空。
	{
		head = p;
	}

	else
	{
		while(pr->next != NULL)//因为每次进入该函数，pr指针都会指向头节点，所以通过轮询的方式将pr指向尾节点。
		{
			pr = pr->next;
		}
		pr->next = p;//尾节点连接新开辟的节点空间的节点空间。
	}

	p->val = val;//填充新开辟的节点内存空间。
	p->next = NULL;//此时新开辟的节点为尾节点，将next指针指向空。

	return head;//返回链表头指针

}

/*打印链表*/
void display_list(struct linked *head)
{
	struct linked *ptr = NULL;//ptr保存当前节点的地址
	

	if(head == NULL)
	{
		printf("链表不存在!\n");
		exit(0);
	}
	ptr = head;
	while(ptr != NULL)
	{
		printf("打印第%d个节点的地址：%p\n",ptr->val,ptr);
		ptr = ptr->next;
	}
	printf("打印节点结束\n");
}

/*释放内存*/
void delete_list(struct linked *head)
{
	struct linked *p,*pr = NULL;
	p = head;

	while(p != NULL)
	{
		pr = p;
		p = p->next;
		printf("释放第%d个节点的内存：%p\n",pr->val,pr);
		free(pr);
	}
	printf("释放内存成功!\n");
}


/*前插法创建链表
  head:链表头
  num:节点个数
*/
struct linked *front_add_node(struct linked *head,int num)
{
	struct linked *p,*headnode;
	int            i;

	p = (struct linked *)malloc(sizeof(struct linked));//创建头节点
	if(p == NULL)
	{
		printf("分配内存失败!\n");
		exit(0);//安全退出程序
	}

	else if(head == NULL)
	{
		head = p;//将头指针指向头节点，头指针主要作用是链表的头，用于函数返回。
		headnode = p;//将头节点指针指向头节点
		headnode->next = NULL;//初始话头节点next,下面步骤中就可以顺利将第一个节点作为尾节点了
	}

	/*创建链表*/
	for(i = 0;i < num;i ++)
	{
		p = (struct linked *)malloc(sizeof(struct linked));//创建节点
		p->val = i+1;
		p->next = headnode->next;
		headnode->next = p;

	}
	printf("前插法创建链表成功\n");

	return head;

}


/*删除某个节点
  head:链表头指针
  del_node:需要删除第几个节点
*/
void delete_node(struct linked *head, int del_node )
{
	struct linked *p = head,*pr = head;
	int           i = 0;
	while(i < del_node && p != NULL)
	{
		pr = p;//pr指向前一个节点
		p  = p->next;//p指向下一个节点
		i++;
	}
	
	if(p == NULL)
	{
		printf("节点不存在!\n");
	}
	else
	{
		pr->next = p->next;
		free(p);
	}
}

/*插入某个节点
  head:链表头指针
  ins_local:插入位置
*/
void insert_node(struct linked *head,int ins_local)
{
	struct linked *pr = head,*p = head,*ptr = NULL;
	int           i   = 0;

	ptr = (struct linked *)malloc(sizeof(struct linked));
	if(ptr == NULL)
	{
		printf("分配内存失败!\n");
		exit(0);
	}
	else
	{
		ptr->val = 6;
	}

	while(i < ins_local && p != NULL)
	{
		pr = p;
		p = p->next;
		i++;
	}
	if(p == NULL)
	{
		printf("节点位置不存在!\n");
	}
	else
	{
		pr->next = ptr;
		ptr->next = p;
	}


}

/*
   功能：链表逆序输出。
   参数：head:链表头

*/
struct linked *reversed_order(struct linked *head)
{
	struct linked *pr = NULL,*ptr = NULL,*tmp = NULL;//pr:保存前一个节点的地址；ptr:保存当前节点的地址；tmp:保存下一个节点的地址
	if(head == NULL)
	{
		printf("无链表!\n");
		return NULL;
	}
	else
	{
		pr = head;//pr指向头节点
		tmp = pr->next;//tmp指向下一个节点
		ptr = tmp;//ptr也指向第二个节点
		pr->next = NULL;//头节点作为尾节点
		while(ptr != NULL)
		{
			tmp = ptr->next;//指向下一个节点
			ptr->next = pr;//第二个节点指前一个节点
			pr = ptr;//pr向后移一个节点
			ptr = tmp;//ptr指向下一个节点
		}
		head = pr;//如果是最后一个节点，则作为头节点
		return head;

	}
}
