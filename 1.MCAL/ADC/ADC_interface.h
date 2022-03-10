/*****************************************************************/
/*****************************************************************/
/***************		Author: Alyaa Mohamed	******************/
/***************		Layer: MCAL				******************/
/***************		SWC: ADC				******************/
/***************		Date: 20-9-2020			******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

typedef struct{
	u8*  ChainChannel;
	u16* ChainResult;
	u8*  CahinSize;
	void (*ChainNotificationFunc)(void);
}Chain_t;

void ADC_voidInt(void);

u8 ADC_u8StartConversionSync(u8 Copy_u8Channel,u16* Copy_pu16Result);


/*
 * preconditions: function needs enable the global interrupt
 * */
u8 ADC_u8StartConversionAsync(u8 Copy_u8Channel,u16* Copy_pu16Result,void (*Copy_pvNotificationFunc)(void));

/*
 * preconditions: function needs enable the global interrupt
 * */
u8 ADC_u8StartChainConversionAsynch(Chain_t* Copy_Chain);

#endif
