#ifndef __MYCONFIG_H
#define __MYCONFIG_H
#include<reg52.h>
//MCU @12MHz
/*you can change ROW/COL value to suit your LED matrix size.*/
#define ROW 16
#define COL 8

/*you can change MCUBITS value based on the MCU you use.*/
#define MCUBITS 8//is 8-bits MCU
#define SEG (((ROW-1)/MCUBITS)+1)//for BG[],LightLayer[] definition

/*Hardware mapping*/
#define PORT_SEG0 P2
#define PORT_SEG1 P1
#define PORT_SCAN P0
#define PORT_KEYS P3
typedef enum{
  KEYS_MASK = (unsigned char)0xf0,
  keyDrop = (unsigned char)0xE0,
  keyLeft = (unsigned char)0xD0,
  keyRight = (unsigned char)0xB0,
  keyRotate = (unsigned char)0x70,
  keyPause = ~((~keyLeft)|(~keyRight)),//two keys pressing at the same time
  keyNULL = (unsigned char)0x00
};

#define EN_ALL_INT (EA=1)//enable all interruption
#define EN_EXT1 (EX1=1)//enable EXT1
#define DISABLE_EXT1 (EX1=0)//disable EXT1
#define isWarOver (F.CoorY==0)
#define getRangeX_Low() (F.CoorX<0?0:F.CoorX)
#define getRangeX_High() (F.CoorX+3>(COL-1)?(COL-1):F.CoorX+3)


#endif



