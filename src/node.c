/*
 * @Author: SingleBiu
 * @Date: 2021-07-01 18:55:31
 * @LastEditors: SingleBiu
 * @LastEditTime: 2022-01-19 14:03:03
 * @Description: 不带头结点的双向链表
 */
#include"node.h"

extern Head_Node *H;

/**
 * @description: 初始化双向链表的头结点
 * @param {*}
 * @return {Head_Node *}  返回双向循环链表的头结点
 */
Head_Node *init_Node()
{
    H = (Head_Node*)malloc(sizeof(H));
    H->len = 0;
    return H;
}


/**
 * @description: 读取指定路径下的文件 并将bmp jpg文件的文件名加入到双向循环链表中去
 * @param {DIR} *dir
 * @param {char} *path  传入的路径
 * @return {int} (0) 正常退出
 */
int readdirent(DIR *dir,char *path)
{
    int total_size = 0;     //所有图片文件的总大小
    int i = 0;              //bmp图片的数量
    int j = 0;              //jpg图片的数量
    int k = 0;              //子目录的数量
    
    struct dirent *p = NULL;
    
    while (p = readdir(dir))
    {
        // 保存文件名的数组
        char filename[64];
        sprintf(filename,"%s%s",path, p->d_name);
        // printf("%s\n", filename);
    
        struct stat st;
        stat(filename, &st);

        // 是普通文件
        if (S_ISREG(st.st_mode))
        {
            // 以 .bmp 结尾的文件
            if ( (strstr(p->d_name,".bmp")) != NULL)
            {
                Node *node = malloc(sizeof(node));
                node->next = NULL;
                node->prev = NULL;
                node->pathname = malloc(sizeof(char)*64);
                stpcpy(node->pathname,filename);
                H = insert_Node(H,node);
                i++;
            }
            // 以 .jpg 结尾的文件
            else if ( (strstr(p->d_name,".jpg")) != NULL)
            {
                Node *node = malloc(sizeof(node));
                node->next = NULL;
                node->prev = NULL;
                node->pathname = malloc(sizeof(char)*64);
                stpcpy(node->pathname,filename);
                H = insert_Node(H,node);
                j++;
            }
        }
        // 是目录
        else if(S_ISDIR(st.st_mode))
        {
            k++;
        }
        // 图片文件大小累加
        total_size += st.st_size;
        printf("\n|| %s ||\n",filename);
    }
    printf("这个目录下面有 %d 个bmp文件  %d 个jpg文件 %d 个子目录 总大小为 %d KB\n", i,j,k,total_size/1024);

    return 0;
}

/**
 * @description: 向带头结点的双向循环链表插入一个结点
 * @param {Head_Node} *h 双向循环链表的头结点
 * @param {node} *p      待插入的结点
 * @return {Head_Node*}  返回双向循环链表的头结点
 */
Head_Node *insert_Node(Head_Node *h,Node *p)
{
    if (h->len == 0)
    {
        h->pic_list = p;
        h->len++;
        h->pic_list->next = h->pic_list->prev = h->pic_list;
        return h;
    }
    else
    { 
        Node *tmp = h->pic_list;
        while (tmp->next != h->pic_list)
        {
            tmp = tmp->next;
        }
        tmp->next = p;
        p->prev = tmp;
        p->next = h->pic_list;
        h->pic_list->prev = p;
        // free(tmp);
    }
    h->len++;
    return h;
}