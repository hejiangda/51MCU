#include <reg52.h>
sbit KEY1=P3^6;  //定义按键输入端口
sbit KEY2=P3^7;  //定义按键输入端口
sbit      SPK=P1^2;
unsigned char Timer0_H,Timer0_L,Time;
char happy;

void DelayUs2x(unsigned char t)
{
 while(--t);
}

void DelayMs(unsigned int t)
{

 while(t--)
 {
     DelayUs2x(245);
	 DelayUs2x(245);
 }
}
void DelayMin(unsigned int t){
  while(t--){
    DelayMs(60000);
  }
}

void music();
void key();

void main() {
  /* code */
  P0=0x00;
  P2=0x00;
   /* while(1){
    SPK=0;
     DelayUs2x(100);
     SPK=1;
     DelayUs2x(100);
  }*/
  

  key();
  P0=0xff;
  P2=0xff;


  if(happy==0){
    P0=0xfe;
    DelayMin(25);
  }else if (happy==1){
    P2=0xfe;
    DelayMin(10);
  }
  P0=0xff;
  P2=0xff;
  // DelayMin(1);
  // DelayMs(6000);
  // music();
  while(1){
    SPK=0;
     DelayUs2x(100);
     SPK=1;
     DelayUs2x(100);
  }
  
  // DelayMin(1);
}


// ------------------------------------------------*/
void delay(unsigned char t)
{
    unsigned char i;
  for(i=0;i<t;i++)
      DelayMs(250);
    TR0=0;
 }
/*------------------------------------------------
               定时器0中断
------------------------------------------------*/
void TIM0_ISR() interrupt 1
{
 TR0=0;
 SPK=!SPK;
 TH0=Timer0_H;
 TL0=Timer0_L;
 TR0=1;
 }
/*------------------------------------------------
                歌曲处理函数
------------------------------------------------*/
void Song()
{
 TH0=Timer0_H;//赋值定时器时间，决定频率
 TL0=Timer0_L;
 TR0=1;       //打开定时器
 delay(Time); //延时所需要的节拍
 }


void music(){


  code unsigned char MUSIC[]={          6,2,3,      5,2,1,      3,2,2,    5,2,2,    1,3,2,    6,2,1,    5,2,1,
                                        6,2,4,      3,2,2,      5,2,1,    6,2,1, 	  5,2,2, 	3,2,2, 	  1,2,1,
                                        6,1,1,      5,2,1,      3,2,1, 	2,2,4, 	  2,2,3, 	3,2,1,    5,2,2,
                                        5,2,1,      6,2,1,      3,2,2, 	2,2,2,    1,2,4, 	5,2,3, 	  3,2,1,
                                        2,2,1,      1,2,1,      6,1,1, 	1,2,1, 	  5,1,6, 	0,0,0
                                        };
                           // 音阶频率表 高八位
  code unsigned char FREQH[]={
                                  0xF2,0xF3,0xF5,0xF5,0xF6,0xF7,0xF8,
                                  0xF9,0xF9,0xFA,0xFA,0xFB,0xFB,0xFC,0xFC, //1,2,3,4,5,6,7,8,i
                                  0xFC,0xFD,0xFD,0xFD,0xFD,0xFE,
                                  0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFF,
                                 } ;
                           // 音阶频率表 低八位
  code unsigned char FREQL[]={
                                   0x42,0xC1,0x17,0xB6,0xD0,0xD1,0xB6,
                                   0x21,0xE1,0x8C,0xD8,0x68,0xE9,0x5B,0x8F, //1,2,3,4,5,6,7,8,i
                                   0xEE,0x44, 0x6B,0xB4,0xF4,0x2D,
                                   0x47,0x77,0xA2,0xB6,0xDA,0xFA,0x16,
                                  };
  /*---------------------------*/
   {

   unsigned char k,i;
   TMOD|=0x01; //置定时器0工作方式1
   EA=1;       //打开全局中断
   ET0=1;      //打开定时0中断
   while(1)
        {
          if(happy==0){
            P0=0xaa;
          }else if(happy==1){
            P2=0xd7;
          }
         i=0;
         while(i<100)
  	        {         //音乐数组长度 ，唱完从头再来
              k=MUSIC[i]+7*MUSIC[i+1]-1;//去音符振荡频率所需数据
              Timer0_H=FREQH[k];
              Timer0_L=FREQL[k];
              Time=MUSIC[i+2];          //节拍时长
              i=i+3;
              Song();
              // P0=0xff;
             }
         }
    }
}

void key ()
{

  KEY1=1;
  KEY2=1;

  while (1)         //主循环
    {
      if(!KEY1)  //如果检测到低电平，说明按键按下
        {
    	 DelayMs(10); //延时去抖，一般10-20ms
         if(!KEY1)     //再次确认按键是否按下，没有按下则退出
    	   {
            while(!KEY1);//如果确认按下按键等待按键释放，没有释放则一直等待
    	       {
    	      //  LED=!LED;//释放则执行需要的程序
            happy=0;
            goto a;
          }}}

    if(!KEY2)  //如果检测到低电平，说明按键按下
      {
  	 DelayMs(10); //延时去抖，一般10-20ms
       if(!KEY2)     //再次确认按键是否按下，没有按下则退出
  	   {
          while(!KEY2);//如果确认按下按键等待按键释放，没有释放则一直等待
  	       {
  	      //  LED=!LED;//释放则执行需要的程序
          happy=1;
          goto a;
        }
      }
    }
  }

a:;
}
