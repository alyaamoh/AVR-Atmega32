/*****************************************************************/
/*****************************************************************/
/***************		Author: Alyaa Mohamed	******************/
/***************		Layer: HAL				******************/
/***************		SWC: DAC				******************/
/***************		Date: 20-9-2020			******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/

#include "STD_TYPES"
#include "DAC_interface.h"
#include "DAC_config.h"
#include "DAC_private.h"


u8 DAC_u8SetAnalogVolt(u16 Copy_u16AnalogVolt){

u8 counter,num=1;

for(counter=0;counter<RESOLUTION;counter++){
	num=num*2;
}

return Copy_u16AnalogVolt/(REFERENCE/num);
	
}