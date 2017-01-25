#ifndef __MAIN_H
#define __MAIN_H
#include"myConfig.h"
bit IsAutoDropFlag=0;
bit AutoDropEnable=1;

signed char autoDropPeriod = 55;//
unsigned char Score=0;
unsigned char KeyCode = keyNULL;
//--------------------------------Core Structure-----------------------------------								 
unsigned char code Src_Blocks[7][3]={			   
  {0x00,0x07,0x02},//T
  {0x00,0x03,0x06},//Z
  {0x00,0x06,0x06},//O
  {0x02,0x03,0x01},//S
  {0x00,0x0F,0x00},//I
  {0x00,0x07,0x04},//L
  {0x00,0x04,0x07}//J
};
/*Mapping of Matrix to Array
           BG[i][0]        BG[i][COL-1]
           COL0            COL-1
LSB  ROW0 o---------------> CoorX
          |
          |
          |
MSB       .  (ROW x COL LED MATRIX)
LSB       .
          .
          |
MSB  ROW-1|
          V
         CoorY
*/
typedef struct {//Record the coordinate of the present playing Src_Blocks, all the parameters draw a picture of "current layer".
		char CoorX;//x axis value
		char CoorY; //y axis value
    unsigned char Blocks[4];//Current blocks code
		unsigned char IdxNext;//index of the following blocks
		unsigned char CpsLeft,CpsRight,CpsDrop;//compensation for move range judgement. Is the blank speace in Blocks[]
}TETRIS;
TETRIS F={3,4,{0x00,0x0F,0x00,0x00},6,0,0,0};

unsigned char LightLayer[SEG][4]={0};
unsigned char BG[SEG][COL]={0};

#endif
