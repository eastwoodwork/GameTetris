/**
  * @brief  Timers config.
	*	@note		Priority of interruption(Nature):
            INT0
            T/C0
            INT1
            T/C1
            Serial
	* @date		
  */
#include<reg52.h>
#include"Interrupt.h"

/**
  * @brief  Timer0 INT server, matrix scanning & generate auto-drop flag
  * @param  None
  * @retval None
	*	@note		
	* @date		
  */
void InterruptT0(void) interrupt 1{ //using 0	 
	static unsigned char i=0,j=0;
	unsigned char iLow= getRangeX_Low(),iHigh= getRangeX_High();
  
  /*reload timer*/
	TH0 = 0xf8;
	TL0 = 0X55;   
  
  /*matrix driver£¬ output = BG | LightLayer*/
	PORT_SEG0 = 0x00;//turn off before shift columns
  PORT_SEG1 = 0x00;
  
	PORT_SCAN = ~(((unsigned char)0x80)>>i);//Columns scanning

	PORT_SEG0 = BG[0][i];//display BG (firstly)
	PORT_SEG1 = BG[1][i];
  /*merge with LightLayer if necessary*/
  if((i>=iLow)&&(i<=iHigh)){
    PORT_SEG0 |= LightLayer[0][i-F.CoorX];	
		PORT_SEG1 |= LightLayer[1][i-F.CoorX];		
	}
	
  /*auto droping flag generator*/
  if((++i) == COL){
		i=0;
    if(AutoDropEnable){
      if((++j) == autoDropPeriod){
        j=0;
        IsAutoDropFlag = 1;	
      }
    }
  }
}  

/**
  * @brief  get keys value though EXT1
  * @param  None
  * @retval None
	*	@note		
	* @date		
  */
void EXINT1(void) interrupt	2{
	KeyCode = PORT_KEYS & KEYS_MASK;
  /*optimization for droping*/
  if(KeyCode == keyDrop)
		AutoDropEnable=0;

}

/**
  * @brief  Timer0 config.
  * @param  None
  * @retval None
	*	@note		50Hz @ 8MHz CRYSTAL
	* @date		
  */ 
void config_TIM0(void){  //[1]
  TMOD=0x01;//16 bits	timer,mode 1
  TH0 = 0xf8;//about 60Hz @ Crystal 12MHz & COL=8
	TL0 = 0X55; //     
  ET0=1;   //in IE		,enable T0
  TR0=1;	   //in TCON, T0 start running
} 

/**
  * @brief  EXT1 config.
  * @param  None
  * @retval None
	*	@note		
	* @date		
  */
void config_EXT1(void){	//[3]initial INT0 & INT1. INt0: for Power on/Off & pause; INT1: For key-sensor
  IT1=1;//1->0 trig
  EX1=1; //in IE,external interruption enable
  
} 

