#include <reg52.h>
void sendString(unsigned char *s);
void InitUART(void);
void main(void){
  InitUART();
  ES=0;
  sendString("123456789\n");
  ES=1;//打开串口中断
  // while(1){
  //
  // }
}

void sendByte(unsigned char dat){
  SBUF=dat;//缓冲器
  while(!TI);
  TI=0;//发送中断标志位

}
void sendString(unsigned char *s){
  while(*s!='\0'){
    sendByte(*s);
    s++;
  }
}

void InitUART(void){
  PCON=0X80;//电源控制寄存器
  SCON=0X50;//串口控制寄存器
  TMOD|=0X20;//模式控制寄存器
  TH1=0XF3;//定时器一高八位
  // 0xf3,fosc=12MHZ,baud rate=2400
  TR1=1;//打开定时器一
  EA=1;//打开总中断
  // ES=1;
}

void UART_SER(void) interrupt 4{
  if(RI){
    RI=0;//接收中断标志位
  }
  if(TI){
    TI=0;
  }
}
