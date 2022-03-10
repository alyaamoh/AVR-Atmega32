/*****************************************************************/
/*****************************************************************/
/***************		Author: Alyaa Mohamed	******************/
/***************		Layer: MCAL				******************/
/***************		SWC: TIMER				******************/
/***************		Date: 24-9-2020			******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER_interface.h"
#include "TIMER_register.h"
#include "TIMER_config.h"
#include "TIMER_private.h"

//global pointer to func to hold the call back func address
//timer0

static void (*TIMER0_pvCompMatchCallBackFunc)(void) = NULL;


void Timer0_voidInit(void){

    	//initialize waveform generation mode to work as CTC mode
		CLR_BIT(TCCR0,TCCR0_WGM00);
		SET_BIT(TCCR0,TCCR0_WGM01);

		//set the req match value
		OCR0=TIMER0_u8COMP_MATCH_VAL;

		//timer0 comp match interrupt enable
		SET_BIT(TIMSK,TIMSK_OCIE0);


    	//set the required prescaler
	    TCCR0 &= TIMER0_PRESCALER_MASK;
	    TCCR0 |= TIMER0_u8PRESCALER;
}




u8 Timer0_u8CompmatchSetCallBack(void (*Copy_pvCallBackFunc)(void)){
	u8 Local_u8ErrorState=OK;

		if(Copy_pvCallBackFunc != NULL){
			TIMER0_pvCompMatchCallBackFunc=Copy_pvCallBackFunc;
		}
		else Local_u8ErrorState=NULL_POINTR;

		return Local_u8ErrorState;
}



void Timer0_voidCompMatch(u8 Copy_u8Value){
	  OCR0=Copy_u8Value;

}


//timer0 ISR CTC mode 
void __vector_10(void)  __attribute__((signal));
void __vector_10(void){

	if(TIMER0_pvCompMatchCallBackFunc != NULL){
		TIMER0_pvCompMatchCallBackFunc();
	}
	else {
		//nothing
	}
}







