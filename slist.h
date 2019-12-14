/*================================================================
*   Copyright (C) 2019 belonging to YangZhengQing. All rights reserved.
*   
*   文件名称：slist.h
*   创 建 者：YangZhengQing
*   创建日期：2019年12月01日
*   描    述：
*
*================================================================*/


#ifndef _SLIST_H_

#define _SLIST_H_

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

/*头文件声明*/

struct linked *add_node(struct linked *head,int val);
struct linked *front_add_node(struct linked *head,int num);
void display_list(struct linked *head);
void delete_list(struct linked *head);
void insert_node(struct linked *head,int ins_local);
void delete_node(struct linked *head,int del_node);
struct linked *reversed_order(struct linked *head);
#endif
