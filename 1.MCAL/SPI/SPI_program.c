/*****************************************************************/
/*****************************************************************/
/***************		Author: Alyaa Mohamed	******************/
/***************		Layer: MCAL				******************/
/***************		SWC: SPI    			******************/
/***************		Date: 8-10-2020			******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SPI_interface.h"
#include "SPI_register.h"
#include "SPI_config.h"
#include "SPI_private.h"


static void(*SPI_pvNotificationFunc)(void)=NULL;
static u8* SPI_pu8DataSend=NULL;
static u8* SPI_pu8DataReceive=NULL;
u8 SPI_u8DataSize;

void SPI_voidIntit(u8 Copy_u8Role){
	switch(Copy_u8Role){
	case MASTER:
		SET_BIT(SPCR,SPCR_MSTR);
		SPCR &= CLOCK_RATE_MASK;
		SPCR |= CLOCK_RATE;
		break;
	case SLAVE:
		CLR_BIT(SPCR,SPCR_MSTR);
		break;
	}
#if DATA_ORDER==MSB
	CLR_BIT(SPCR,SPCR_DORD);

#elif DATA_ORDER==LSB
	SET_BIT(SPCR,SPCR_DORD);
#else
#error "wrong DATA_ORDER config"
#endif


#if CLOCK_PHASE==SAMPLE
	CLR_BIT(SPCR,SPCR_CPHA);
#elif CLOCK_PHASE==SETUP
	SET_BIT(SPCR,SPCR_CPHA);
#else
#error "wrong CLOCK_PHASE config"
#endif


#if CLOCK_POLARITY==LOW_IN_IDLE
	CLR_BIT(SPCR,SPCR_CPOL);
#elif CLOCK_POLARITY==HIGH_IN_IDLE
	SET_BIT(SPCR,SPCR_CPOL);
#else
#error "wrong CLOCK_POLARITY config"
#endif

	//enable SPI
	SET_BIT(SPCR,SPCR_SPE);
}


u8 SPI_u8TransceiveSynch(u8 Copy_u8DataSend,u8* Copy_pu8DataReceive){

	u8 Local_u8ErrorState=OK;
	u32 Local_u32Counter=0;

	//send data
	SPDR=Copy_u8DataSend;

	//wait until the transfer is complete
	while((GET_BIT(SPSR,SPSR_SPIF)==0)&&(Local_u32Counter<SPI_u32TIME_OUT)){
		Local_u32Counter++;
	}

	if(Local_u32Counter==SPI_u32TIME_OUT) Local_u8ErrorState=TIMEOUT_STATE;
	else{
	//get the received data
	*Copy_pu8DataReceive=SPDR;
	}

	return Local_u8ErrorState;
}

u8 SPI_u8TransceiveBufferSynch(u8* Copy_pu8DataSendBuffer,u8* Copy_pu8DataReceiveBuffer,u8 Copy_u8BufferSize){
	 u8 Local_u8ErrorState=OK;
	 u8 Local_u8Counter=0;

	 if((Copy_pu8DataReceiveBuffer != NULL)&&(Copy_pu8DataSendBuffer != NULL)){

		 for(Local_u8Counter=0;Local_u8Counter<Copy_u8BufferSize;Local_u8Counter++){
			 SPI_u8TransceiveSynch(Copy_pu8DataSendBuffer[Local_u8Counter],Copy_pu8DataReceiveBuffer[Local_u8Counter]);
		 }
	 }
	 else Local_u8ErrorState=NULL_POINTR;
	 return Local_u8ErrorState;
}



u8 SPI_u8TransceiveBufferASynch(u8* Copy_pu8DataSendBuffer,u8* Copy_pu8DataReceiveBuffer,u8 Copy_u8BufferSize,void (*Copy_pvNotificFunc)(void)){

	u8 Local_u8ErrorState=OK;
	if((Copy_pu8DataReceiveBuffer != NULL)&&(Copy_pu8DataSendBuffer != NULL)&&(Copy_pvNotificFunc != NULL)){
		SPI_pu8DataReceive=Copy_pu8DataReceiveBuffer;
		SPI_pu8DataSend=Copy_pu8DataSendBuffer;
		SPI_pvNotificationFunc=Copy_pvNotificFunc;
		SPI_u8DataSize=Copy_u8BufferSize;
        
		SPDR=Copy_pu8DataSendBuffer[0];

		//enable the interrupt
		SET_BIT(SPCR,SPCR_SPIE);
	}
	else Local_u8ErrorState=NULL_POINTR;
	return Local_u8ErrorState;

}

void __vector_12(void)    __attribute__((signal));
void __vector_12(void){

	static u8 Local_u8Counter=0;
	if((SPI_pu8DataReceive != NULL)&&(SPI_pu8DataSend != NULL)&&(SPI_pvNotificationFunc != NULL)){

        SPI_pu8DataReceive[Local_u8Counter]=SPDR;
		Local_u8Counter++;

		if(Local_u8Counter == SPI_u8DataSize){
            CLR_BIT(SPCR,SPCR_SPIE);
			Local_u8Counter=0;
			SPI_pvNotificationFunc();
			
		}
		else {
			SPDR=SPI_pu8DataSend[Local_u8Counter];
			
		}
	}
}
