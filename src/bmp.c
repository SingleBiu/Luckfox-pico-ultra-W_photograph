/*
 * @Author: SingleBiu
 * @Date: 2021-07-23 10:15:58
 * @LastEditors: SingleBiu
 * @LastEditTime: 2021-07-28 19:41:27
 * @Description: file content
 */
#include"bmp.h"
#include"lcd.h"



int bmp_display(const char *bmp_file,int x0,int y0)
{
    // 已只读方式打开bmp文件
    int bmp_fd = open(bmp_file, O_RDONLY);
    if (bmp_fd == -1)
    {
        printf("open bmp: %s error\n",bmp_file);
        return -1;
    }

    int width, height;
    short depth;
    uchar buf[4];

    // 获取bmp图片的位深
    lseek(bmp_fd, 0x1c, SEEK_SET);
    read(bmp_fd,buf,2);
    depth = (buf[1] << 8) | (buf[0]);
    if (!(depth == 24 || depth == 32))
    {
        printf("bmp file: %s \n depth not support!\n");
        close(bmp_fd);
        return -1;
    }
    
    // 获取bmp图片的宽
    lseek(bmp_fd, 0x12, SEEK_SET);
    read(bmp_fd,buf,4);
    width = (buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | (buf[0]);

    // 获取bmp图片的高
    lseek(bmp_fd, 0x16, SEEK_SET);
    read(bmp_fd,buf,4);
    height = (buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | (buf[0]);

    printf("%s\t\t%d * %d depth:%d\n",bmp_file,width,height,depth);

    if (abs(width) > WIDTH || abs(height) > HEIGHT)
    {
        printf("Wrong size out of range\n");
        return -1;
    }
    
    int line_valid_bytes; // 一行中有效数据量
    int laizi = 0;        // 一行中赖子的数量
    int line_total_bytes; // 一行总字节数
    int total_bytes;      // 整个像素数组的字节数

    line_valid_bytes = abs(width) * (depth/8);
    if (line_valid_bytes % 4)
    {
        laizi = 4 - line_valid_bytes % 4;
    }
    // 一行的总字节数
    line_total_bytes = line_valid_bytes + laizi;

    // 得到文件的总字节数
    total_bytes = line_total_bytes * abs(height);
    // 为像素数组分配空间
    unsigned char *piexls = malloc(total_bytes);
    // 从bmp文件的第54字节开始读  
    lseek(bmp_fd,54,SEEK_SET);
    // 将total_bytes个字节读入到像素数组piexls里
    read(bmp_fd, piexls, total_bytes);

        
    uchar a,r,g,b;
    int color;
    int x1,y1; // 像素点对应在显示屏上的坐标
    int x,y;   // 循环控制变量

    int i = 0; 
    for (y = 0; y < abs(height); y++)
    {
        for (x = 0; x < abs(width); x++)
        {
            b = piexls[i++];
            g = piexls[i++];
            r = piexls[i++];
            if (depth == 32)
            {
                a = piexls[i++];
            }
            else
            {
                a = 0;
            }
            color = (a << 24) | (r << 16) | (g << 8) | (b);
            
            x1 = width  > 0 ? x0 + x                : x0 + abs(width)-x-1;
            y1 = height > 0 ? y0 + abs(height)-y-1  : y0 + y;

            lcd_draw_point(x1,y1,color);
        }
        i += laizi;
        
    }
    // 释放像素数组
    free(piexls);
    // 关闭bmp文件
    close(bmp_fd);

    return 0;
}
