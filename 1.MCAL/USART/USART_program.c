/*****************************************************************/
/*****************************************************************/
/***************		Author: Alyaa Mohamed	******************/
/***************		Layer: MCAL				******************/
/***************		SWC: USART   			******************/
/***************		Date: 6-10-2020			******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "USART_interface.h"
#include "USART_register.h"
#include "USART_config.h"
#include "USART_private.h"


static void(*USART_pvReceiveNotificationFunc)(void)=NULL;
static void(*USART_pvSendNotificationFunc)(void)=NULL;
static u8* USART_u8pu8ReceiveData=NULL;
static u8* USART_u8pu8SendData=NULL;
u8 USART_u8DataSize;


void USART_voidInit(void){

	//local variable to hold the required value of UCSRC register
	u8 Local_u8UCSRCVal=0;
	u8 Local_u8BaudValue;

	//choose the UCSRC register
	SET_BIT(Local_u8UCSRCVal,UCSRC_URSEL);

	//character size
	Local_u8UCSRCVal &= CHARSIZE_MASK;
#if CHARSIZE == CHARSIZE_9BIT
	SET_BIT(UCSRB,UCSRB_UCSZ2);
	Local_u8UCSRCVal |= CHARSIZE;
#else
	CLR_BIT(UCSRB,UCSRB_UCSZ2);
	Local_u8UCSRCVal |= CHARSIZE;
#endif



#if USART_MODE == ASYNCHRONOUS
	CLR_BIT(Local_u8UCSRCVal,UCSRC_UMSEL);
#elif USART_MODE == SYNCHRONOUS
	SET_BIT(Local_u8UCSRCVal,UCSRC_UMSEL);
#endif

//parity mode
Local_u8UCSRCVal &= PARITY_MASK;
Local_u8UCSRCVal |= PARITY_MODE;



#if STOP_BIT == STOP_BIT_1
	CLR_BIT(Local_u8UCSRCVal,UCSRC_USBS);
#elif  STOP_BIT == STOP_BIT_2
	SET_BIT(Local_u8UCSRCVal,UCSRC_USBS);
#endif


	//Assign the UCSRC required value in one operation
	UCSRC=Local_u8UCSRCVal;


	//Baud Rate Setting
#if CHARSIZE == CHARSIZE_9BIT
	Local_u8BaudValue=(FOSC/(8UL * BAUD_RATE))-1;
		UBRRL=(u8)Local_u8BaudValue;
		UBRRH=(u8)(Local_u8BaudValue<<8);
#else
	Local_u8BaudValue=(FOSC/(16UL * BAUD_RATE))-1;
		UBRRL=(u8)Local_u8BaudValue;
		UBRRH=(u8)(Local_u8BaudValue<<8);
#endif


#if USART_TRANSMITTER_STATE==ENABLE
	SET_BIT(UCSRB,UCSRB_TXEN);
#elif USART_TRANSMITTER_STATE==DISABLE
	CLR_BIT(UCSRB,UCSRB_TXEN);
#else
#error "wrong USART_TRANSMITTER_STATE config"
#endif

#if USART_RECEIVER_STATE==ENABLE
	SET_BIT(UCSRB,UCSRB_RXEN);
#elif USART_RECEIVER_STATE==DISABLE
	CLR_BIT(UCSRB,UCSRB_RXEN);
#else
#error "wrong USART_RECEIVER_STATE config"
#endif

}

u8 USART_u8SendData(u8 Copy_u8Data){

	u32 Local_u32Counter=0;
	u8 Local_ErrorState=OK;
	//wait until the transmit buffer is empty  and ready or  the timeout is reached
	while((GET_BIT(UCSRA,UCSRA_UDRE)==0)&&(Local_u32Counter<USART_u32TIME_OUT)){
		Local_u32Counter++;
	}

	if(Local_u32Counter==USART_u32TIME_OUT) Local_ErrorState=TIMEOUT_STATE;
	else{
	     //send the data
	     UDR=Copy_u8Data;
	}
	return Local_ErrorState;
}

u8 USART_u8ReceiveData(u8* Copy_u8Data){

	u32 Local_u32Counter=0;
    u8 Local_ErrorState=OK;
	
	//wait until receive complete event happens
	while((GET_BIT(UCSRA,UCSRA_RXC)==0)&&(Local_u32Counter<USART_u32TIME_OUT)){
	Local_u32Counter++;
	}

	if(Local_u32Counter==USART_u32TIME_OUT) Local_ErrorState=TIMEOUT_STATE;
		else{
			*Copy_u8Data=UDR;
		}
	return Local_ErrorState;
}

u8 USART_u8SendStringSynch(const u8* Copy_pchString){

	u8 Local_u8ErrorState=OK;
	u8 Local_u8Counter=0;
	if(Copy_pchString != NULL){
	while(Copy_pchString[Local_u8Counter] != '\0'){
		USART_u8SendData(Copy_pchString[Local_u8Counter]);
		Local_u8Counter++;
	}
	}
	else Local_u8ErrorState=NULL_POINTR;
	return Local_u8ErrorState;
}

u8 USART_u8SendStringASynch(const u8* Copy_pchString,void (*Copy_pvNotificFunc)(void)){

	u8 Local_u8ErrorState=OK;
	if((Copy_pchString != NULL)&& (Copy_pvNotificFunc != NULL)){
		USART_pvSendNotificationFunc=Copy_pvNotificFunc;
		USART_u8pu8SendData=Copy_pchString;
		SET_BIT(UCSRB,UCSRB_UDRIE);
	}
	else Local_u8ErrorState=NULL_POINTR;
	return Local_u8ErrorState;
}

u8 USART_u8ReceiveBufferSynch(u8* Copy_pchString,u8 Copy_u8BufferSize){

	u8 Local_u8ErrorState=OK;
	u8 Local_u8Counter=0;

	if(Copy_pchString != NULL){

		for(Local_u8Counter=0;Local_u8Counter<Copy_u8BufferSize;Local_u8Counter++){
			USART_u8ReceiveData(&Copy_pchString[Local_u8Counter]);
		}
	}
	else Local_u8ErrorState = NULL_POINTR;
	return Local_u8ErrorState;
}

u8 USART_u8ReceiveBufferASynch(u8* Copy_pchString,u8 Copy_u8BufferSize,void (*Copy_pvNotificFunc)(void)){

	u8 Local_u8ErrorState=OK;
	if((Copy_pchString != NULL)&&(Copy_pvNotificFunc != NULL)){
		USART_pvReceiveNotificationFunc=Copy_pvNotificFunc;
		USART_u8pu8ReceiveData=Copy_pchString;
		USART_u8DataSize=Copy_u8BufferSize;
		SET_BIT(UCSRB,UCSRB_RXCIE);
	}
	else Local_u8ErrorState=NULL_POINTR;
	return Local_u8ErrorState;
}

// USR: USART, Rx Complete
void __vector_13(void)    __attribute__((signal));
void __vector_13(void){

	static u8 Local_u8Counter=0;
	if((USART_pvReceiveNotificationFunc != NULL)&&(USART_u8pu8ReceiveData != NULL)){

            USART_u8pu8ReceiveData[Local_u8Counter]=UDR;
			Local_u8Counter++;
			
		if (Local_u8Counter==USART_u8DataSize){
			CLR_BIT(UCSRB,UCSRB_RXCIE);
			Local_u8Counter=0;
			USART_pvReceiveNotificationFunc();
		}
		
	}
}



void __vector_14(void)    __attribute__((signal));
void __vector_14(void){

	static u8 Local_u8Counter=0;
	if((USART_pvSendNotificationFunc != NULL)&& (USART_u8pu8SendData != NULL)){

		if(USART_u8pu8SendData[Local_u8Counter] != '\0'){
			UDR=USART_u8pu8SendData[Local_u8Counter];
			Local_u8Counter++;
		}
		else{
			CLR_BIT(UCSRB,UCSRB_UDRIE);
			Local_u8Counter=0;
			USART_pvSendNotificationFunc();
		}
	}
}
