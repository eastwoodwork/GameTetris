#ifndef __MOVE_H
#define __MOVE_H
#include"myConfig.h"
#include"Can.h"
#include"updateLightLayer.h"
#include"CalculateCps.h"
#include"PublicDef.h"
#include"server.h"

bit rotateTrialAndError(void);
void moveLeftACell(void);
void moveRightACell(void);
bit dropACell(void);
static void rotateClockwise(unsigned char array[4]);
#endif