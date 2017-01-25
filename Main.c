/**
  ******************************************************************************
  * @author  ChangYanjing
  * @date     24-1-2017
  * @brief   This file contains the main function for Tetris game based on 16 x 8 LED
             Matrix. If you want to change the matix size or MCU type, please refer to
             "myConfig.h" and modify the corresponding micro definitions.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2017 www.eastwood.work</center></h2>
  *
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.eastwood.work
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 
#include<reg52.h>
#include"main.h"
#include"Interrupt.h"
#include"KeyDecode.h"
#include"updateLightLayer.h"
#include"CalculateCps.h"
#include"Can.h"
#include"Move.h"
#include"battleover.h"
#include"myConfig.h"
 
void main(void){
  /*config Timer0*/
	config_TIM0();	
  /*config EXT1*/
  config_EXT1();
  /*enable all interruption*/
 	EN_ALL_INT;
  
  /*waiting for (any) key's pressing,to get a random blocks*/
  while(KeyCode == keyNULL);
  KeyCode = keyNULL;
	newBattle();
  newBattle();
  
	while(1){
    if(IsAutoDropFlag){
      IsAutoDropFlag = 0;
      autoDropping();
    }
    
    DISABLE_EXT1;
    KeyDecode();
    EN_EXT1;
	} 
}
	

