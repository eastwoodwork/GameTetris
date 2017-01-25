#include"CalculateCps.h"	
/**
  * @brief  counts (F.Blocks[])'s left/right/bottom blank spaces,
            extends the range a blocks can move.
  * @param  
  * @retval None
	*	@note		example(T-type blocks):
  F.Blocks [0] ,, [3]
  --------------------------->
            0 0 0 0 (LSB)
            0 1 1 1
            0 0 1 0
            0 0 0 0
            0 0 0 0
            0 0 0 0
            0 0 0 0
            0 0 0 0 (MSB)
--------------------------->
CpsLeft = 1;
CpsRight = 0;
CpsDrop = 5;
	* @date		
  */
void updateCps(unsigned char *leftNullCol,unsigned char *rightNullCol,unsigned char *bottomNullRow,unsigned char _blocks[4]){
	signed char i;
  unsigned char t;
	unsigned char left=0,right = 0, bot=0;
  
  /*left*/
  for(i=0;i<4;i++){																		
	  if(_blocks[i]==0)													
	    left++;																																									
	  else break;       
  }
  /*right*/
  for(i=3;i>=0;i--){																		
	  if(_blocks[i]==0)															
	    right++;																																									
	  else break;     
  }
  /*bottom*/
  t = mergeArray(_blocks,4);
  
	for(i=0;i<MCUBITS;i++){
		if(((t<<i) & 0x80) == 0){
			bot++;
		}
		else break;
	}
  
  *leftNullCol=left;
  *rightNullCol=right;
  *bottomNullRow=bot;
	
}																							
