// 题目三    信号发生器
// 何江达    2016/3/24/14:56
#include <reg52.h>
sbit KEY1=P3^6;  //加
sbit KEY2=P3^7;  //减
sbit OUT=P1^0;  //输出
unsigned int n=0;
void Init_Timer1(void);
void Init_Timer0(void);
void DelayUs2x(unsigned char t);
void DelayMs(unsigned int t);
unsigned int t1;
unsigned int t2;
unsigned int a=500;
unsigned int sum=1000;

void main(void){
  while(1){
    P2=~n;
    t1=(65536-(sum-a)*n)/256;
    t2=(65536-a*n)%256;
    if(!KEY1){
      DelayMs(10);
        if(!KEY1){
          while(!KEY1);
          if(n!=100){
            n++;
            Init_Timer0();
          }else{
            n=1;
          }
        }else {
        DelayMs(500);
        if(!KEY1){
          while(!KEY1);
            a=a+100;
            if(a==1100){
              a=0;
            }
          }
        }
      }
    if(!KEY2){
      DelayMs(10);
      if(!KEY2){
        while(!KEY2);
        if(n!=1){
          n--;
          Init_Timer0();
        }else{
          n=100;
        }
      }else DelayMs(500);
      if(!KEY2){
        a=a-100;
        if(a==0){
          a=1000;
        }
      }
    }
  }
}

void Init_Timer0(void){
  TMOD|=0x01;
  TH0=t1;
  TL0=t2;
  EA=1;
  ET0=1;
  TR0=1;
}

void Timer0_isr(void) interrupt 1 using 1{
  TH0=t1;
  TL0=t2;
  OUT=~OUT;
}

void DelayUs2x(unsigned char t){
  while(--t);
}

void DelayMs(unsigned int t){
  while(t--){
     //大致延时1mS
   DelayUs2x(245);
	 DelayUs2x(245);
  }
}
void key(void){

}
