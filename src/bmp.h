/*
 * @Author: SingleBiu
 * @Date: 2021-07-23 10:16:21
 * @LastEditors: SingleBiu
 * @LastEditTime: 2021-07-23 15:26:12
 * @Description: file content
 */
#if !defined(__BMP_H__)
#define __BMP_H__

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<math.h>

typedef unsigned int uint;
typedef unsigned char uchar;


int bmp_display(const char *bmp_file,int x0,int y0);



#endif // __BMP_H__
