#include <reg52.h>

void Init(void);
void delayUs(unsigned char);
void delayMs(unsigned char);
void main(void){
	P1=0xff;
	Init();
	while(1);
}
void Init(void){
	EA=1;
	EX0=1;
	IT0=1;
}

void interruptTest(void) interrupt 0 using 1{
	if(!INT0){
		delayMs(1);
		if(!INT0){
			P1=~P1;
		}
	}
}

void delayUs(unsigned char t){
	while(--t);
}
void delayMs(unsigned char t){
	while(--t){
		delayUs(245);
		delayUs(245);
	}
}