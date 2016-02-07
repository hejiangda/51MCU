#include <reg52.h>
#include "delay.h"

/*------------------------------------------------
 uS延时函数，含有输入参数 unsigned char t，无返回值
 unsigned char 是定义无符号字符变量，其值的范围是
 0~255 这里使用晶振12M，精确延时请使用汇编,大致延时
 长度如下 T=tx2+5 uS
------------------------------------------------*/
void DelayUs2x(unsigned char t)
{
 while(--t);
}
/*------------------------------------------------
 mS延时函数，含有输入参数 unsigned char t，无返回值
 unsigned char 是定义无符号字符变量，其值的范围是
 0~255 这里使用晶振12M，精确延时请使用汇编
------------------------------------------------*/
void DelayMs(unsigned int t)
{

 while(t--)
 {
     //大致延时1mS
     DelayUs2x(245);
	 DelayUs2x(245);
 }
}

void DelayMin(unsigned char t){
  while(t--){
    DelayMs(60000);
  }
}
void DelaySec(unsigned char t){
  while(t--){
    DelayMs(1000);
  }
}
void DelayHor(unsigned char t){
  while(t--){
    DelayMin(60);
  }
}
