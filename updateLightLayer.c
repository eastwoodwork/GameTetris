#include"updateLightLayer.h"

/**
  * @brief  update (LightLayer).
  * @param  None
  * @retval None
	*	@note		By decoding blocks' source code to lightlayer, based on coordinate Y.
            _lightLayer should be cleared before usage.
	* @date		
  */
void updateLightLayer(signed char y,unsigned char _lightLayer[SEG][4],unsigned char fairy[4]) { 
	unsigned char i;
	unsigned char modeY,segment;
  
	modeY = y % MCUBITS;
  segment = y / MCUBITS;
	
	/*Clear old Layer*/
  clearArray(_lightLayer[0],SEG*4);
  
  /*set value of uper section*/
  if(modeY!=(MCUBITS-1)){//no need to clear again
    if((y >= MCUBITS) && (y < ROW + MCUBITS)){//or _lightLayer will out of range
      for(i=0;i<4;i++){
        _lightLayer[segment-1][i] = fairy[i] << (modeY+1);
      }
    }
  }
  
  /*Across the border, deal with the section that the bottom row of the fairy on*/
  if(y<ROW){//or _lightLayer will out of range
    for(i=0;i<4;i++){
      _lightLayer[segment][i] = fairy[i] >> (MCUBITS-1-modeY);
    }
  }
}

