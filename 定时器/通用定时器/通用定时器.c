#include <reg52.h>
#include "delay.h"
#include "music.h"

sbit KEY1=P3^6;  //模式-时间
sbit KEY2=P3^7;  //应用确认
char apply_key=0;
unsigned char mode_key=2;
unsigned char num_key=25;
char flag=0;
char flag1=0;
char LED[]={0xff,0xfd,0xf7,0xdf,0x7f,0xfe,0xfb,0xef,0xbf};
char LED1[]={0x7f,0xbf,0x3f};

void Init_Timer1(void)
{
 TMOD |= 0x10;	  //使用模式1，16位定时器，使用"|"符号可以在使用多个定时器时不受影响
 TH1=0x00;	      //给定初值，这里使用定时器最大值从0开始计数一直到65535溢出
 TL1=0x00;
 EA=1;            //总中断打开
 ET1=1;           //定时器中断打开
 TR1=1;           //定时器开关打开
}

void main(){
  Init_Timer1();
  KEY1=1;
  KEY2=1;
  P0=LED[mode_key];
  P2=255-num_key;
  P2=~P2;
  P2|=~LED1[apply_key];
  P2=~P2;
  while (2!=apply_key) {
    if(!KEY1){
      DelayMs(10);
      if(!KEY1){
        while(!KEY1);{
          if(0==apply_key){
            mode_key+=1;//1,秒;2分;3小时;
            if(5==mode_key){
              mode_key=1;
            }
            P0=LED[mode_key];
          }else if(1==apply_key){
            if(0==flag1){
              flag1=1;
              num_key=0;
            }
            num_key+=1;
            if (60==num_key){
              num_key=0;
            }
            P2=255-num_key;
            P2=~P2;
            P2|=~LED1[apply_key];
            P2=~P2;
          }
          goto end0;
        }
      }
    }
      end0:
    if(!KEY2){
      DelayMs(10);
      if(!KEY2){
        while(!KEY2);{
          apply_key+=1;//0,模式;1,时间数;2,退出选择
          if(4==mode_key){
            apply_key=2;
          }
          // if(2==mode_key&&25==num_key){
          //   apply_key=2;
          // }
          P2=255-num_key;
          P2=~P2;
          P2|=~LED1[apply_key];
          P2=~P2;
          goto end1;
        }
      }
    }
    end1:;
  }
  P0=0xff;
  P2=0xff;
  if(1==mode_key){
    DelaySec(num_key);
  }else if (2==mode_key){
    DelayMin(num_key);
  }else if (3==mode_key){
    DelayHor(num_key);
  }else if (4==mode_key){
    num_key=10;
    P2=255-num_key;
    P2=~P2;
    P2|=~LED1[apply_key];
    P2=~P2;
    P0=LED[2];
    P0=0xff;
    P2=0xff;
    DelayMin(10);
  }
  flag=1;
  music();
}

/*------------------------------------------------
                 定时器中断子程序
------------------------------------------------*/
void Timer1_isr(void) interrupt 3 using 1
{
  char j;
 TH1=0x00;		 //重新赋值
 TL1=0x00;
 if (1==flag){
   j++;
   P0=LED[j];       //LED闪烁
   P2=LED[j];
   if(8==j){
     j=0;
   }
  }
}
