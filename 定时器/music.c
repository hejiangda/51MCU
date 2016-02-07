#include <reg52.h>
#include "music.h"
#include "delay.h"
#include "sheet.h"
unsigned char Timer0_H,Timer0_L,Time;
sbit SPK=P1^2;
unsigned char k,i;
void music(void)
{
  TMOD|=0x01; //置定时器0工作方式1
  EA=1;       //打开全局中断
  ET0=1;      //打开定时0中断


while(1)
     {
      i=0;
      while(i<100)
         {         //音乐数组长度 ，唱完从头再来
           k=MUSIC1[i]+7*MUSIC1[i+1]-1;//去音符振荡频率所需数据
           Timer0_H=FREQH[k];
           Timer0_L=FREQL[k];
           Time=MUSIC1[i+2];          //节拍时长
           i=i+3;
           Song();
          }
      }
 }


void delay(unsigned char t)
{
    unsigned char i;
	for(i=0;i<t;i++)
	    DelayMs(250);
    TR0=0;
 }

void Song()
{
 TH0=Timer0_H;//赋值定时器时间，决定频率
 TL0=Timer0_L;
 TR0=1;       //打开定时器
 delay(Time); //延时所需要的节拍
 }

 void TIM0_ISR() interrupt 1
 {
  TR0=0;
  SPK=!SPK;
  TH0=Timer0_H;
  TL0=Timer0_L;
  TR0=1;
  }
