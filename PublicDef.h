#include"myConfig.h"
/*For varibles, must use "Extern" declaration (main.h has defined) */
extern unsigned char KeyCode;
extern bit IsAutoDropFlag;
extern bit AutoDropEnable;

extern signed char autoDropPeriod;
extern unsigned char Score;
//--------------------------------Core Structure-----------------------------------								 
extern unsigned char code Src_Blocks[7][3];
extern struct{//Record the coordinate of the present playing Src_Blocks, all the parameters draw a picture of "current layer".
		char CoorX;//right-moved cells
		char CoorY; //the distance of Src_Blocks dropping 
    
    unsigned char Blocks[4];
		unsigned char IdxNext;//save the following fairy source code
		unsigned char CpsLeft,CpsRight,CpsDrop;//for Uper Limit modification. To restrict fairy on 10x20 LED-Matrix.
}F;

extern unsigned char LightLayer[SEG][4];
extern unsigned char BG[SEG][COL];