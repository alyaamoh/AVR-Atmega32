/*****************************************************************/
/*****************************************************************/
/***************		Author: Alyaa Mohamed	******************/
/***************		Layer: MCAL				******************/
/***************		SWC: ADC				******************/
/***************		Date: 20-9-2020			******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "ADC_register.h"
#include "ADC_config.h"
#include "ADC_interface.h"
#include "ADC_private.h"

//global pointer to hold the conv. result
static u16* ADC_pu16ConversionResult=NULL;

//global pointer to hold the notification function
static void(*ADC_pvNotificationFunc)(void)=NULL;

//global variable to indicate for ADCperipheral state
static u8 ADC_u8BusyState=IDLE;

//global flag to indicate for the reason why ISR comes
static u8 ADC_u8ISRSource;

static u8* ADC_u8puChainChannel=NULL;

static u8 ADC_u8ChainSize;

static u8 ADC_u8ChainIndex;

void ADC_voidInt(void){

	//REFERENCE: AVCC 
	SET_BIT(ADMUX,REFS0);
	CLR_BIT(ADMUX,REFS1);

	//LEFT ADJUST
	SET_BIT(ADMUX,ADLAR);

	//PRESCALER SETTING
	ADCSRA&=PRESCALER_MASK;
	ADCSRA|=PRESCALER_MASK;

	//ENABLE
	SET_BIT(ADCSRA,ADEN);

}


u8 ADC_u8StartConversionSync(u8 Copy_u8Channel,u16* Copy_pu16Result){

	u8 Local_u8ErrorState=OK;
	u32 Local_u32Counter=0;

	if(Copy_pu16Result != NULL){

		if(ADC_u8BusyState==IDLE){

			ADC_u8BusyState=BUSY;


	//SET THE REQUIRED CHANNEL
	ADMUX&=CHANNEL_MASK;
	ADMUX|=Copy_u8Channel;

	//START CONVERSION
	SET_BIT(ADCSRA,ADSC);

	//POLLING WITH BLOCKING FOR ADC CONV. COMPLETE FLAG OR THE TIME OUT IS REACHED
	while((GET_BIT(ADCSRA,ADIF) == 0)&&(Local_u32Counter<ADC_u32TIMEOUT)){
		Local_u32Counter++;
	}

	//check the reason of the while loop is broken
	if(Local_u32Counter==ADC_u32TIMEOUT) {
		Local_u8ErrorState=TIMEOUT_STATE; }
	else {
		SET_BIT(ADCSRA,ADIF); //clear the flag

		//8 bit ADCH ,10 bit ADC.............
			*Copy_pu16Result= ADCH;


	}
	ADC_u8BusyState=IDLE;
		}
		else Local_u8ErrorState=BUSY_STATE;

	}
	else Local_u8ErrorState=NULL_POINTR;

	return Local_u8ErrorState;
}

u8 ADC_u8StartConversionAsync(u8 Copy_u8Channel,u16* Copy_pu16Result,void (*Copy_pvNotificationFunc)(void)){

	u8 Local_u8ErrorState=OK;
	if((Copy_pu16Result!=NULL)&&(Copy_pvNotificationFunc != NULL)){

		//check if it is busy with another conv.
		if(ADC_u8BusyState==IDLE){
			//ADC now is busy
			ADC_u8BusyState=BUSY;

			ADC_u8ISRSource=SINGLE_CONVERSION;

		//initialize the global pointer to point to result
		ADC_pu16ConversionResult=Copy_pu16Result;

		//initialize the global pointer to point to notification function
		ADC_pvNotificationFunc=Copy_pvNotificationFunc;

		    //SET THE REQUIRED CHANNEL
			ADMUX&=CHANNEL_MASK;
			ADMUX|=Copy_u8Channel;

			//START CONV.
			SET_BIT(ADCSRA,ADSC);

			//EENABLE ADC CONV. COMPLETE INTERRUPT
			SET_BIT(ADCSRA,ADIE);
		}
		else Local_u8ErrorState=BUSY_STATE;

	}
	else Local_u8ErrorState=NOK;
	return Local_u8ErrorState;
}

void __vector_16(void)    __attribute__((signal));
void __vector_16(void){

	if(ADC_u8ISRSource==SINGLE_CONVERSION){

	//read the conv. result
	*ADC_pu16ConversionResult=ADCH;

	//release the ADC busy state,ADC is now idle
	ADC_u8BusyState=IDLE;

	//disable the conv. complete interrupt enable
		CLR_BIT(ADCSRA,ADIE);

	//invoke the call back notification
	if(ADC_pvNotificationFunc!=NULL) ADC_pvNotificationFunc();

	}

	else{ //chain conversion

		//read the conv. result
		ADC_pu16ConversionResult[ADC_u8ChainIndex]=ADCH;

		ADC_u8ChainIndex++;

		if(ADC_u8ChainIndex == ADC_u8ChainSize){

			//chain is finished

			ADC_u8BusyState=IDLE;

			//disable the conv. complete interrupt enable
			CLR_BIT(ADCSRA,ADIE);

			//invoke the call back notification
			if(ADC_pvNotificationFunc!=NULL) ADC_pvNotificationFunc();

		}
		else {

			//SET THE REQUIRED CHANNEL
			ADMUX&=CHANNEL_MASK;
			ADMUX|=ADC_u8puChainChannel[ADC_u8ChainIndex];

			//START CONV.
			SET_BIT(ADCSRA,ADSC);
		}


	}
}


u8 ADC_u8StartChainConversionAsynch(Chain_t* Copy_Chain){

	u8 Local_u8ErrorState=OK;

	if((Copy_Chain != NULL)&&(Copy_Chain->ChainChannel != NULL)&&(Copy_Chain->CahinSize!=NULL)&&(Copy_Chain->ChainNotificationFunc!=NULL)){

		if(ADC_u8BusyState==IDLE){

			ADC_u8BusyState=BUSY;

			ADC_u8ISRSource=CHAIN_CONVERSION;

			ADC_u8puChainChannel=Copy_Chain->ChainChannel;
			ADC_pu16ConversionResult=Copy_Chain->ChainResult;
			ADC_u8ChainSize=Copy_Chain->CahinSize;
			ADC_pvNotificationFunc=Copy_Chain->ChainNotificationFunc;

			ADC_u8ChainIndex=0;

			 //SET THE REQUIRED CHANNEL
			 ADMUX&=CHANNEL_MASK;
			 ADMUX|=ADC_u8puChainChannel[ADC_u8ChainIndex];

			//START CONV.
			SET_BIT(ADCSRA,ADSC);

			//EENABLE ADC CONV. COMPLETE INTERRUPT
			SET_BIT(ADCSRA,ADIE);

		}
		else Local_u8ErrorState=BUSY_STATE;
	}
	else Local_u8ErrorState=NULL_POINTR;

	return Local_u8ErrorState;
}
