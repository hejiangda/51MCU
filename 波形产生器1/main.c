#include <reg52.h>

sbit OUT=P1^2;
void time_init(void);
void main(void){
  time_init();
  while(1);
}

void time_init(void){
  TMOD|=0x01;
  TH0=(65536-500)/256;
  TL0=(65536-500)%256;
  EA=1;
  ET0=1;
  TR0=1;
}

void timer0 (void) interrupt 1 using 1{
  TH0=(65536-500)/256;
  TL0=(65536-500)%256;
  OUT=~OUT;
}