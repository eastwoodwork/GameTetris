#include"KeyDecode.h"
/**
  * @brief  Response to key-pressing.
  * @param  None
  * @retval None
	*	@note		
	* @date		
  */ 
void KeyDecode(void){
	switch (KeyCode){ 
		case keyPause:	
				AutoDropEnable = !AutoDropEnable;//switch between pause and continue
				break;	
		
		case keyLeft:
				if(canMoveLeftACell())
					moveLeftACell();
				break;
				
		case keyRight:
				if(canMoveRightACell())
					moveRightACell();
				break;
				
		case keyRotate:
				rotateTrialAndError();
				break;
	
		case keyDrop://falling down continually.
				while(dropACell()){
        }
        
        clearBattleField();

		}
    KeyCode = keyNULL;
}
/**
  * @brief  Auto dropping.
  * @param  None
  * @retval None
	*	@note		Drivered by Timer.
	* @date		
  */ 
void autoDropping(void){
  
    if(!dropACell()){
      clearBattleField();
      
    }
}
