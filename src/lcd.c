/*
 * @Author: SingleBiu
 * @Date: 2021-07-22 17:11:17
 * @LastEditors: SingleBiu
 * @LastEditTime: 2021-07-28 19:30:23
 * @Description: LCD函数文件
 */
#include"lcd.h"
#include"node.h"
#include"bmp.h"
#include"jpg.h"

/**
 * @description: LCD屏幕初始化
 * @param {*}
 * @return {*}
 */
void lcd_init()
{
    // 打开LCD文件
    lcd_fd = open(LCD_FILE, O_RDWR);
	if (lcd_fd == -1)
	{
		perror("open LCD error");
		return ;
	}

    // 使plcd指向帧缓冲区的首地址
    plcd = mmap(NULL, WIDTH*HEIGHT*4, 
	           PROT_READ | PROT_WRITE,
			   MAP_SHARED,
			   lcd_fd,
			   0);
}

/**
 * @description: 在LCD屏幕上画一个color颜色的点
 * @param {int} x 屏幕的x坐标
 * @param {int} y 屏幕的y坐标
 * @param {int} color 要填充的颜色
 * @return {*}
 */
void lcd_draw_point(int x, int y, int color)
{
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	*(plcd + y*WIDTH + x) = color;
}

/**
 * @description: 在LCD的任意位置 显示一个任意大小的任意颜色的矩形
 * @param {uint} x0 矩形起始的x坐标
 * @param {uint} y0 矩形起始的y坐标
 * @param {uint} w  矩形的宽
 * @param {uint} h  矩形的高
 * @param {int} color  要填充的颜色
 * @return {*}
 */
void lcd_draw_rect(int x0, int y0, int w, int h, int color)
{
	int x, y;
	for (y = y0; y < y0 + h && y < HEIGHT; y++)
	{
		for (x = x0; x < x0 + w && x < WIDTH; x++)
			lcd_draw_point(x, y, color);
	}
}

/**
 * @description: 检测LCD屏幕有无坏点
 * @param {*}
 * @return {*}
 */
void lcd_color_check()
{
    while(1)
    {
        lcd_draw_rect(0,0,WIDTH,HEIGHT,BLACK);
        sleep(3);
        lcd_draw_rect(0,0,WIDTH,HEIGHT,RED);
        sleep(3);
        lcd_draw_rect(0,0,WIDTH,HEIGHT,GREEN);
        sleep(3);
        lcd_draw_rect(0,0,WIDTH,HEIGHT,BLUE);
        sleep(3);
        lcd_draw_rect(0,0,WIDTH,HEIGHT,YELLOW);
        sleep(3);
        lcd_draw_rect(0,0,WIDTH,HEIGHT,WHITE);
        sleep(3);
    }
}


/**
 * @description: 根据文件名进行判断 选择合适的显示方式
 * @param {char} *ptr  指向图片文件名的指针
 * @param {int} x  图片显示的起始x坐标
 * @param {int} y  图片显示的起始y坐标
 * @return {*}
 */
void display(char *ptr,int x,int y)
{
    // 以 .bmp结尾的文件用bmp_dispaly进行显示
    if ( (strstr(ptr,".bmp")) != NULL)
    {
        bmp_display(ptr,x,y);
    }
    // 以 .jpg结尾的文件用jpg_dispaly进行显示
    else if ( (strstr(ptr,".jpg")) != NULL)
    {
        jpg_displasy(ptr,x,y);
    }
}