/*
 * @Author: SingleBiu
 * @Date: 2021-07-26 15:27:24
 * @LastEditors: SingleBiu
 * @LastEditTime: 2024-10-15 12:59:49
 * @Description: file content
 */

#include "ts.h"

extern int TOUCH_EVENT;
extern int btn_l;
extern int btn_r;

int touch_init()
{
	int fd = open("/dev/input/event0", O_RDWR);
	if (fd == -1)
	{
		printf("failed to open /dev/input/event0\n");
		return -1;
	}
	return fd;
}

/**
 * @description:获取用户移动的方向
 * @param {*}
 * @return {int}	MOVE_LEFT    //向左
					MOVE_RIGHT   //向右
					MOVE_UP    	 //向上
			    	MOVE_DOWN    //向下
					MOVE_EMPTY   //没有操作
 */
void* get_user_input(int _ts_fd)
{
	// 触摸屏文件描述符
	int fd = _ts_fd;

	int x1 = -1, y1 = -1; //一次滑动过程中的，起点的坐标
	int x2, y2; //一次滑动过程中的，终点的坐标
	struct input_event ev;

	while (1)
	{
		int r = read(fd, &ev, sizeof(ev));
		if (r != sizeof(ev))
		{
			continue;
		}

		//ev是一个x轴坐标事件
		if (ev.type == EV_ABS &&  ev.code == ABS_X)
		{	
			if (x1 == -1)
			{	
				x1 = ev.value ; //就是x轴的坐标值
				// x1 = 1.0*800/1024*x1;
			}
			x2 = ev.value;
		}

		
		//ev是一个y轴坐标事件
		if (ev.type == EV_ABS &&  ev.code == ABS_Y)
		{	
			if (y1 == -1)
			{	
				y1 = ev.value ; //就是x轴的坐标值
				// y1 = 1.0*480/600*y1;
			}
			y2 = ev.value;
		}
		
		// // 查看触摸点的位置 测试用
		// printf("\nx1:%d y1:%d\n",x1,y1);

		//弹起事件

		if(ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0)
		{
			int delt_x = abs(x2 - x1);
			int delt_y = abs(y2 - y1);

			if (delt_x > 2 *delt_y)
			{
				// close(fd);
				if (x2 > x1)
				{
					TOUCH_EVENT = MOVE_RIGHT;
				}
				else
				{
					TOUCH_EVENT = MOVE_LEFT;
				}
			}
			else if (delt_y > 2*delt_x)
			{
				// close(fd);
				if (y2 > y1)
				{
					TOUCH_EVENT = MOVE_DOWN;
				}
				else
				{
					TOUCH_EVENT = MOVE_UP;
				}
			}
			else
			{
				x1 = -1;
				y1 = -1;
			}
			
			// // 查看触摸点的位置 测试用
			// printf("\nx2:%d y2:%d\n",x2,y2);
			// printf("\ndelt_x:%d delt_y:%d\n",abs(x2 - x1),abs(y2 - y1));
			
			/**
			 * @brief 输出滑动的方向
			 * 	3：左滑 
			 *  4：右滑
			 */
			printf("\n TOUCH_EVENT = %d\n",TOUCH_EVENT);
			
			break;
		}
	}
}

/**
 * @description:获取用户的点击
 * @param {*}
 * @return {*}
 */
void* get_user_input_click(int _ts_fd)
{
	// 触摸屏文件描述符
	int fd = _ts_fd;

	int x1, y1;
	struct input_event ev;

	while (1)
	{
		int r = read(fd, &ev, sizeof(ev));
		if (r != sizeof(ev))
		{
			continue;
		}

		//判断事件类型是否为触摸屏的x轴，并且获取x轴坐标
        if(ev.type == EV_ABS && ev.code == ABS_MT_POSITION_X)
        {
            x1 = ev.value; 
        }
        //判断事件类型是否为触摸屏的y轴，并且获取y轴坐标
        if(ev.type == EV_ABS && ev.code == ABS_MT_POSITION_Y)
        {
            y1 = ev.value; 
        }
        //判断是否松手
        if(ev.type == EV_ABS && ev.code == ABS_MT_TRACKING_ID && ev.value == -1)
        {
            //打印坐标值
            printf("X:%d,Y:%d\n", x1, y1);
			//左按钮
			if (x1 > 0 && x1 < 160 && y1 < 720 && y1 > 600)
			{
				btn_l = TRUE;
			}
			//右按钮
			if (x1 > 560 && x1 < 720 && y1 < 720 && y1 > 600)
			{
				btn_r = TRUE;
			}
			x1 = -1;
			y1 = -1;
            break;
        }			
		break;
	}
}
