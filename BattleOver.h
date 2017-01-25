
#include<reg52.h>
#include"updateLightLayer.h"
#include"CalculateCps.h"
void clearBattleField(void);
static void warOver(void);
static void battleOver(void);
void newBattle(void);
static void updateBG(unsigned char _lightLayer[SEG][4]);
static void updateBlocksCode(void);
static void fullRowsCheckTwinkleDel(void);
static void twinkleFullRows(unsigned char segment,unsigned char fullLineCode);
static void delFullRows(unsigned char segment,unsigned char fullLineCode);
static void DeleteSingleRow(unsigned char segment,unsigned char bitX);
static void scoreManager(void);

