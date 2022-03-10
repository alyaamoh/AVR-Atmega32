/*****************************************************************/
/*****************************************************************/
/***************		Author: Alyaa Mohamed	******************/
/***************		Layer: MCAL				******************/
/***************		SWC: WATCH DOG			******************/
/***************		Date: 1-10-2020			******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "WATCHDOG_interface.h"
#include "WATCHDOG_register.h"
#include "WATCHDOG_config.h"
#include "WATCHDOG_private.h"

void WDT_voidEnable(void){
	SET_BIT(WDTCR,WDTCR_WDE);
}


void WDT_voidDisable(void){
	WDTCR = (1<<WDTCR_WDTOE) | (1<<WDTCR_WDE);
	WDTCR = 0;
}


u8 WDT_u8Sleep(u8 Copy_u8SleepTime){
	u8 Local_u8ErrorState=OK;

	if(Copy_u8SleepTime<8){

		WDTCR &= 0b11111000;
		WDTCR |= Copy_u8SleepTime;
	}
	else Local_u8ErrorState=NOK;
	return Local_u8ErrorState;
}