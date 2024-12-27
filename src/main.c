#include"lcd.h"
#include"bmp.h"
#include"jpg.h"
#include"ts.h"
#include"node.h"
#include<pthread.h>

int ts_fd;
// 按钮
int btn_l = FALSE;
int btn_r = FALSE;
// 触摸屏输入的值
int TOUCH_EVENT = MOVE_EMPTY;
Head_Node *H = NULL;

void *thread_touch_click()
{
    while (1)
    {
        get_user_input_click(ts_fd);
    }
    
}

int main(int argc, char *argv[])
{
    // LCD初始化
    lcd_init();
    //清屏
    lcd_draw_rect(0,0,WIDTH,HEIGHT,WHITE);

    //初始化图片链表
    H = init_Node();

    //读取目录
    DIR *dir = opendir(argv[1]);
    readdirent(dir,argv[1]);

    //定义一个指针指向图片链表
    Node *ptr = H->pic_list;

    //显示开始的图片
    bmp_display("startup.bmp",0,0);
    
    //显示两个按钮
    jpg_displasy("left.jpg",0,600);
    jpg_displasy("right.jpg",560,600);

    //初始化触摸屏
    ts_fd = touch_init();

    //开启一个线程检测触摸
    pthread_t ts;
    int res = pthread_create(&ts,NULL,thread_touch_click,NULL);
    if (res != 0)
    {
        perror("Failed to create pthread");
        exit(res);
    }

    //上一张 下一张图片具体实现
    while (1)
    {
        if (TRUE == btn_l)
        {
            lcd_draw_rect(0,0,WIDTH,HEIGHT,WHITE);
            // 上一张
            ptr = ptr->prev;
            display(ptr->pathname,0,0);
            btn_l = FALSE;
            jpg_displasy("left.jpg",0,600);
            jpg_displasy("right.jpg",560,600);
        }
        
        if (TRUE == btn_r)
        {
            lcd_draw_rect(0,0,WIDTH,HEIGHT,WHITE);
            // 下一张
            ptr = ptr->next;
            display(ptr->pathname,0,0);
            btn_r = FALSE;
            jpg_displasy("left.jpg",0,600);
            jpg_displasy("right.jpg",560,600);
        }   
    }

    while (1)
    {
        /* code */
    }
    
    //关闭LCD屏幕
    close(lcd_fd);

    return 0;
}