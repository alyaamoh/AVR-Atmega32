/*****************************************************************/
/*****************************************************************/
/***************		Author: Alyaa Mohamed	******************/
/***************		Layer: HAL				******************/
/***************		SWC: SWITCH				******************/
/***************		Date: 1-9-2020			******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/
#include "STD_TYPES.h"
#include "SWITCH_config.h"
#include "SWITCH_interface.h"
#include "DIO_interface.h"

u8 SWITCH_u8Debouncing(SWITCH_t* Copy_Switch){
u8 press=0,Copy_pu8Value;
static u32 press_level=0,realised_level=0;

//set the pull up
DIO_u8SetPinValue(Copy_Switch->port,Copy_Switch->pin,DIO_u8PIN_HIGH);

//get the value of the button
DIO_u8GetPinValue(Copy_Switch->port,Copy_Switch->pin,&Copy_pu8Value);

if(Copy_pu8Value != SWITCH_PULL){
	press_level++;
	if(press_level>=MAX_PRESS_LEVEL){  //if number of zeros reached to the max so the key is pressed
	  if(press==0)
	  {
			press=1;
			
	  }
	  press_level=0;
	  return press;
	}
}
else
  {   realised_level++;
	  if(realised_level>=MAX_REALISED_LEVEL){  //if number of ones reached to the max so the key is not pressed
	  press=0;
	  realised_level=0;
	  }
  }

return press;
}
