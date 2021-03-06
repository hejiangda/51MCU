#ifndef __SHEET_H__
#define __SHEET_H__
//世上只有妈妈好数据表
extern code unsigned char MUSIC1[]={
            6,2,3,      5,2,1,      3,2,2,    5,2,2,    1,3,2,    6,2,1,    5,2,1,
             6,2,4,      3,2,2,      5,2,1,    6,2,1, 	  5,2,2, 	3,2,2, 	  1,2,1,
             6,1,1,      5,2,1,      3,2,1, 	2,2,4, 	  2,2,3, 	3,2,1,    5,2,2,
             5,2,1,      6,2,1,      3,2,2, 	2,2,2,    1,2,4, 	5,2,3, 	  3,2,1,
             2,2,1,      1,2,1,      6,1,1, 	1,2,1, 	  5,1,6, 	0,0,0
             };
// 音阶频率表 高八位
extern code unsigned char FREQH[]={
       0xF2,0xF3,0xF5,0xF5,0xF6,0xF7,0xF8,
       0xF9,0xF9,0xFA,0xFA,0xFB,0xFB,0xFC,0xFC, //1,2,3,4,5,6,7,8,i
       0xFC,0xFD,0xFD,0xFD,0xFD,0xFE,
       0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFF,
      } ;
// 音阶频率表 低八位
extern code unsigned char FREQL[]={
        0x42,0xC1,0x17,0xB6,0xD0,0xD1,0xB6,
        0x21,0xE1,0x8C,0xD8,0x68,0xE9,0x5B,0x8F, //1,2,3,4,5,6,7,8,i
        0xEE,0x44, 0x6B,0xB4,0xF4,0x2D,
        0x47,0x77,0xA2,0xB6,0xDA,0xFA,0x16,
       };
#endif
