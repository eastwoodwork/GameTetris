#ifndef __CAN_H
#define __CAN_H
#include"PublicDef.h"
#include"updateLightLayer.h"
#include"myConfig.h"

bit canMoveLeftACell();
bit canMoveRightACell();
bit hasObstacle(char preCps_X,unsigned char _lightLayer[SEG][4]);
#endif