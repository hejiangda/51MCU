#include <reg52.h>
#define SUM 100
//#define NUM 10
sbit OUT=P2^2;
sbit KEY=P3^6;
void delayUS(unsigned char);
void delayMS(unsigned char);
void init(void);
int NUM=10;
int main(void) {
  int key=0,count=0;
  init();
  while(1){
    key=KEY;
    if(key){
      delayMS(10);
      key=KEY;
      if(key){
        if(count==0){
          NUM+=10;
          if(NUM==100){
            count=1;
          }
        }else{
          NUM-=10;
          if(NUM==0){
            count=0;
          }
        }

      }
      while(key){
        key=KEY;
      }
    }
  };
  return 0;
}

void init(void){
  TMOD|=0X01;
  TH0=(65536-50)/256;
  TL0=(65536-50)%256;
  EA=1;
  ET0=1;
  TR0=1;
}
void timer0 (void) interrupt 1 using 1{
  static count=0;
  TH0=(65536-50)/256;
  TL0=(65536-50)%256;
  count++;
  if(count<=NUM){
    OUT=0;
  }else{
    OUT=1;
  }
  if(NUM>100){
    NUM=0;
  }
  if(count==SUM){
    // n++;
    // NUM=n;
    count=0;
  }
}
void delayUS(unsigned char t){
  while(--t);
}
void delayMS(unsigned char t){
  while(--t){
    delayUS(245);
    delayUS(245);
  }
}
