/**
  * @brief  Estimation of the conditions wether can move or not.
	*	@note		
	* @date		
  */
#include"Can.h"

/**
  * @brief  to judge if can move left one step.
  * @param  None
  * @retval None
	*	@note		
	* @date		
  */ 
bit canMoveLeftACell(){//every rotation together with the update of Cps_F_CODE
		if(F.CoorX + F.CpsLeft<=0) return 0;	 
		return !hasObstacle(-1,LightLayer);
}
/**
  * @brief  to judge if can move right one step.
  * @param  None
  * @retval None
	*	@note		
	* @date		
  */  
bit canMoveRightACell(){
		if(F.CoorX > (COL-1)-4+F.CpsRight) return 0;
		return !hasObstacle(1,LightLayer);
}  
/**
  * @brief  to judge if has obstacles after moving/rotating.
  * @param  preIncX: pre-increase/decrease F.CoorX,
                      value = (1,0,-1) is reasonable.
            _lightLayer: the lightLayer
  * @retval None
	*	@note		
	* @date		
  */ 	
bit hasObstacle(char preIncX,unsigned char _lightLayer[SEG][4]){
		unsigned char temp=0;
		char i,j,x = F.CoorX + preIncX;
		unsigned char iLow = x<0?0:x;
		unsigned char iHigh = x+3>(COL-1)?(COL-1):x+3;
	
		for(j=0;j<SEG;j++){
			for(i=iLow;i<=iHigh;i++){
				temp|=(BG[j][i] & _lightLayer[j][i-x]);
			}
		}
    
		if(temp!=0){
       return 1;
    }
		return 0;
	 
}