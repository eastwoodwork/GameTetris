/**
  * @brief  to move/rotate.
	*	@note		work with matrix scanning method (@TIM0_INT server function)
	* @date		
  */ 
#include"Move.h"
/**
  * @brief  move left one step.
  * @param  None
  * @retval None
	*	@note		By decreasing the coordinateX, matrix scanning will manage the rest.
	* @date		
  */ 
void moveLeftACell(void){
		F.CoorX--;
}
/**
  * @brief  move right one step.
  * @param  None
  * @retval None
	*	@note		By increasing the coordinateX, matrix scanning will manage the rest.
	* @date		
  */ 	 
void moveRightACell(void){
		F.CoorX++;
}
/**
  * @brief  drop one step.
  * @param  None
  * @retval if can drop, return 1.
	*	@note		By increasing the coordinateY,then update LightLayer.
	* @date		
  */ 		 
bit dropACell(void){
    unsigned char temp[SEG][4]={0};
  
		if(F.CoorY+1>(ROW-1)+F.CpsDrop) return 0;

    updateLightLayer(F.CoorY+1,temp,F.Blocks);
		if(!hasObstacle(0,temp)){
      F.CoorY++;
      copyArray(LightLayer[0],temp[0],SEG*4);//updateLightLayer(F.CoorY,LightLayer,F.Blocks);
      
      return 1;
    }
    
    return 0;

}

/**
  * @brief  rotate 90 degree clockwise.
  * @param  None
  * @retval None
	*	@note		
	* @date		
  */ 	
bit rotateTrialAndError(void){
		unsigned char temp_L,temp_R,temp_D;
		unsigned char tempArr[SEG][4]={0};//must!
    unsigned char	f[4]={0};
      
		rotateClockwise(f);//FairyRotate(tempArr[2]);
		updateCps(&temp_L,&temp_R,&temp_D,f);//updateCps(&temp_L,&temp_R,&temp_D,tempArr[2]);
    updateLightLayer(F.CoorY,tempArr,f);//updateLightLayer(F.CoorY,tempArr);

    if((F.CoorX+(4-temp_R)>COL)  
      || (F.CoorX+(temp_L)<0)
      || ((F.CoorY)>(ROW-1)+temp_D)
			|| hasObstacle(0,tempArr)){
			 return 0;
		}else{//update LightLayer and Cpss.
        copyArray(F.Blocks,f,4);
        copyArray(LightLayer[0],tempArr[0],SEG*4); 
      
        F.CpsLeft=temp_L;
        F.CpsRight=temp_R;
        F.CpsDrop=temp_D;
        return 1;//no need to implement "rotate" again.
		}
}


/**
  * @brief  rotate a 4x4 bits matrix in F.Blocks, save results to a length=4 array.
  * @param  None
  * @retval None
	*	@note		
	* @date		
  */ 	
static void rotateClockwise(unsigned char array[4]){	   //4x4 cell
	char i,j,a;
	unsigned char b,c,d;	
	
	for(j=0;j<4;j++){	  
		for(i=0;i<4;i++){
			a=3-i-j;
			//fcode[j]|=(F.Blocks[i]&(0x08>>j))>>a; //this is original algorithm
			b=0x08>>j;
			c=F.Blocks[i]&b;
						
			if(a>0) d=c>>a;
			else		d=c<<(-a);
			array[j]|=d;			
		}			        
	}
}


