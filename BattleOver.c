/**
  * @brief  Manage the actions when battle/war is over.
	*	@note		battle over: start a battle again
            war over: game over
	* @date		
  */
#include"BattleOver.h"
/**
  * @brief  War over management
  * @param  None
  * @retval None
	*	@note		
	* @date		
  */
void clearBattleField(void){
  battleOver();
  if(isWarOver){//is War Over
    warOver();
  }else{ 
    newBattle();
  }
}

/**
  * @brief  War over management
  * @param  None
  * @retval None
	*	@note		
	* @date		
  */
static void warOver(void){
	AutoDropEnable=0;
	
	KeyCode=0;
	EX1=1;
	while(KeyCode==0);/*stop here until key is pressed*/
}
/**
  * @brief  Battle over management
  * @param  None
  * @retval None
	*	@note		
	* @date		
  */
static void battleOver(void){
  //delay_x2(100);
  updateBG(LightLayer);
	clearArray(LightLayer[0],SEG*4); /*lightLayerClear*/
  fullRowsCheckTwinkleDel();
  
}

/**
  * @brief  start a new battle
  * @param  None
  * @retval None
	*	@note		
	* @date		
  */
void newBattle(void){		
		/*old parameters reset*/
		F.CoorX=2;
		F.CoorY=4;//1
		AutoDropEnable=1;
    /*new blocks*/
    clearArray(LightLayer[0],SEG*4); /*lightLayerClear*/
    updateBlocksCode();
    updateCps(&F.CpsLeft,&F.CpsRight,&F.CpsDrop,F.Blocks);
    updateLightLayer(F.CoorY,LightLayer,F.Blocks);
}
/**
  * @brief  Update (LightLayer) to BG(Background Array)
  * @param  None
  * @retval None
	*	@note		
	* @date		
  */
static void updateBG(unsigned char _lightLayer[SEG][4]){
	char i,j,temp;
  unsigned char iLow=getRangeX_Low(),iHigh=getRangeX_High();

  for(j=0;j<SEG;j++){
    for(i=iLow;i<=iHigh;i++){
      temp = i-F.CoorX;
      BG[j][i] |= _lightLayer[j][temp];
    }
  }
}
/**
  * @brief  Update blocks code and generate new index of the following.
  * @param  None
  * @retval None
	*	@note		
	* @date		
  */
static void updateBlocksCode(void){

  copyArray(F.Blocks,Src_Blocks[F.IdxNext],3);
  F.Blocks[3] = 0;
  /*Generate "the next" src code*/
  F.IdxNext = TL0%7;
} 

/**
  * @brief  get the FULL-ROW flag, then delete and twinkle a FULL-ROW
  * @param  None
  * @retval None
	*	@note		scanning from up to down (LSB  to MSB)
	* @date		
  */
static void fullRowsCheckTwinkleDel(void){//return the full row compact identification
		unsigned char i,j,temp;
		
		for(j=0;j<SEG;j++){
      temp = 0xff;
			for(i=0;i<COL;i++){     
				temp &= BG[j][i]; 
			}
			if(temp!=0x00){
				twinkleFullRows(j,temp);
				delFullRows(j,temp);
			}
			
		}    
}
/**
  * @brief  the way to twinkle a FULL-ROW
  * @param  segment: point to BG[segment][]
            fullLineCode: char-type, bit = 1 means its corresponding row is a FULL-ROW
  * @retval None
	*	@note		
	* @date		
  */
static void twinkleFullRows(unsigned char segment,unsigned char fullLineCode){
	char flag,i,times=4;//twinkle 2 times

	flag=1;//
  while(times){ //while twinkle-time isn't over
    if(flag){
      flag=0;//clear falg,waitting for next twinkling
      
      for(i=0;i<COL;i++){	      
        BG[segment][i]^=fullLineCode; 												
      }
      times--;
    }
    delay_x2(100);
    flag=1;
  }
  
}
/**
  * @brief  the way to delate ALL the FULL-ROWs
  * @param  segment: point to BG[segment][]
            fullLineCode: char-type, bit = 1 means its corresponding row is a FULL-ROW
  * @retval None
	*	@note		
	* @date		
  */
static void delFullRows(unsigned char segment,unsigned char fullLineCode){
  unsigned char i;
  for(i=0;i<8;i++){
    if(((fullLineCode>>i)&0x01)!=0){
			DeleteSingleRow(segment,i);//call for function to delete one full_line
			scoreManager();	  
		}
  }
}

/**
  * @brief  the way to delate a FULL-ROW
  * @param  segment: point to BG[segment][]
            bitX: the bitX-th row to be deleted(corespongding to fullLineCode=(0x01<<bitX))
  * @retval None
	*	@note		
	* @date		
  */
static void DeleteSingleRow(unsigned char segment,unsigned char bitX){//if BG[]'s bit X is "1", bitX=X
	char i,j;
  signed char temp1;
	unsigned char temp2;
  signed char t=0x80;//t must be "signed char"!  
	/*Within a section: the lines above full bitX dorp down a cell*/
	if(bitX<7){  
		for(i=0;i<COL;i++){
			temp2=(t>>(6-bitX));//below mask 111..0B
			temp1=(~temp2)>>1;//uper mask 000..1B	
        
			BG[segment][i]=(BG[segment][i]&temp2)|((BG[segment][i]&temp1)<<1);//New BG = below lines | above lines
    }
	}else{	//if(bitX==7)
		for(i=0;i<COL;i++)
		  BG[segment][i] <<= 1;//BG= above bitX
  }
	/*All the uper section(s) should also drop a cell; A row cross the border of sections*/
	 if(segment!=0){								 
	   for(j=segment;j>0;j--){					  
	      for(i=0;i<COL;i++){				  
		   	 BG[j][i]|=(BG[j-1][i]>>7);	
		   	 BG[j-1][i]=(BG[j-1][i]<<1);		  
        }									
	   }									
	 }										  
}	

/**
  * @brief  records the score, cotrol dropping speed
  * @param  None
  * @retval None
	*	@note		
	* @date		
  */
static void scoreManager(void){
	Score++;
	//change droping speed
	autoDropPeriod -= ((Score/10)<<2);
	if(autoDropPeriod<10) 
		autoDropPeriod=10;
}
