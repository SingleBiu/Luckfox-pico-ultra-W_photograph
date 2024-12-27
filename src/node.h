/*
 * @Author: SingleBiu
 * @Date: 2021-07-01 18:55:21
 * @LastEditors: SingleBiu
 * @LastEditTime: 2021-07-28 19:29:55
 * @Description: 双向链表头文件
 */
#if !defined(__Node_H__)
#define __Node_H__

#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

// typedef int ElemType;

typedef struct Node
{
    char   *pathname;
    struct Node *prev;
    struct Node *next;
    
}Node;

typedef struct Head_Node
{
    int len;
    struct Node *pic_list;
    
}Head_Node;

Head_Node *init_Node();
int readdirent(DIR *dir,char *path);
Head_Node *insert_Node(Head_Node *h,Node *p);

#endif // __Node_H__
