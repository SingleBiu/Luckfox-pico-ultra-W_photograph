/*
 * @Author: SingleBiu
 * @Date: 2021-07-26 15:16:18
 * @LastEditors: SingleBiu
 * @LastEditTime: 2021-07-28 19:40:57
 * @Description: 用于显示jpg文件
 */
#include<stdio.h>
#include<stdlib.h>
#include"jpeglib.h"
#include"lcd.h"



/**
 * @description: 显示jpg图片
 * @param {const char} *jpgfile jpg文件名
 * @param {int} x0  图片开始显示的x坐标
 * @param {int} y0  图片开始显示的y坐标
 * @return {*}
 */
void jpg_displasy(const char *jpgfile, int x0, int y0)
{

    //(1) 分配并初始化一个Jpeg解压对象
    struct jpeg_decompress_struct dinfo;//定义一个jpeg decompress对象
    struct jpeg_error_mgr error; //定义一个出错对象

    //jpeg_std_error用来初始化一个“出错对象的”，返回一个出错对象
    dinfo.err = jpeg_std_error(&error);
    jpeg_create_decompress(&dinfo); //初始化dinfo对象

    //(2)指定要解压缩的数据的来源
    FILE *fp = fopen(jpgfile, "r");
    if (fp == NULL)
    {
        
    }
    
    jpeg_stdio_src(&dinfo, fp);

    //(3) 调用jpeg_read_header获取图像头信息
    jpeg_read_header(&dinfo, TRUE);
    

    //(4) 调用 jpeg_start_decompress启动解压过程
    jpeg_start_decompress(&dinfo);

    //(5)
    //在调用完 jpeg_start_decompress后，往往需要为解压后的扫描线上所有像素点分配空间
    //buf用来保存一行的解压后的数据!!
    unsigned char *buf = malloc(dinfo.output_width * dinfo.output_components);

    // 输出读取到的jpg文件 文件名 宽 高
    printf("%s\t\t%d * %d\n",jpgfile,dinfo.output_width,dinfo.output_height);

    //(6) 读取一行或者多行扫描线上数据，处理的代码通常是这样子的
    while (dinfo.output_scanline <  dinfo.output_height)
    {

        jpeg_read_scanlines(
                    &dinfo, //解压对象
                    &buf, //char**, 保存解压后数据的二级指针
                    1  //读取多少行数据

        );
        // dinfo.output_scanlines + 1
        // 每一行解压后的数据的从左至右的像素点的   (A) R G B  ... buffer
        unsigned char a = 0, r, g, b;
        unsigned int color;
        int x;
        int i = 0;

        for (x = 0; x < dinfo.output_width; x++)
        {
            if (dinfo.output_components == 4)
            {
                a = buf[i++];
            }
            r = buf[i++];
            g = buf[i++];
            b = buf[i++];
            color = (a << 24) | (r << 16) | (g << 8) | (b);
            //lcd_draw_point(x0 + x, y0 + dinfo.output_scanline -1, color);
            lcd_draw_point(x0 + x, y0 + dinfo.output_scanline -1, color);
        }

    }


   // (7) 调用jpeg_finish_decompress 完成解压过程

    jpeg_finish_decompress(&dinfo);

    //(8) 调用jpeg_destroy_decompress 释放jpeg解压对象及其他的空间

    jpeg_destroy_decompress(&dinfo);
    free(buf);
    fclose(fp);

    return ;
}


