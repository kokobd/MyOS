#include <stdio.h>
#include <stdbool.h>
#define UP_BOUND 2
#define DOWN_BOUND 13
#define LEFT_BOUND 0
#define RIGHT_BOUND 39

void _start() 
{
    putchar(0, 79, '3');
    int x = LEFT_BOUND;
    int y = UP_BOUND;  //字符的横纵坐标

    int vx = 1;
    int vy = 1; //字符的速度

    char obj = 'A'; //字符

    bool flag = false; //控制前景色深浅
    enum Color fColor = 0; //控制前景色
    enum Color bColor = 1; //控制背景色

    for (int i = 0; i < 50; ++i)
    {
        putchar(y, x, obj);
        changeAttribute(y, x, true, flag, fColor, bColor);

        // 改坐标
        y += vy;
        x += vx;

        //改速度
        if (y == DOWN_BOUND || y == UP_BOUND)
        {
            vy = -vy;
        }
        if (x == RIGHT_BOUND || x == LEFT_BOUND)
        {
            vx = -vx;
        }

        //改字符颜色
        if (false == flag)
        {

        }
        else if (flag && fColor == 7)
        {
            fColor = 0;
        }
        else
        {
            fColor++;
        }
        flag = !flag;

        //改背景色
        if (bColor == 7)
        {
            bColor = 0;
        }
        else
        {
            bColor++;
        }

        //改字符
        if ('Z' == obj)
        {
            obj = 'A';
        }
        else
        {
            obj++;
        }

    }
    
}