#include <reg51.h>
#include <stdio.h>

void main(void)
{
    SCON = 0x50; //串口方式1,允许接收
    TMOD = 0x20; //定时器1定时方式 2
    TCON = 0x40; //设定定时器开始计数   � � 
    TH1 = 0xE8;  //11.0592MHz 1200波特率
    TL1 = 0xE8;
    TI = 1;
    TR1 = 1;     //启动定时器 
    
    while(1)
    {
        printf ("Hello World!\n"); //显示Hello World
    }
}
