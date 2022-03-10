/*****************************************************************/
/*****************************************************************/
/***************		Author: Alyaa Mohamed	******************/
/***************		Layer: MCAL				******************/
/***************		SWC: USART   			******************/
/***************		Date: 6-10-2020			******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

void USART_voidInit(void);

u8 USART_u8SendData(u8 Copy_u8Data);

u8 USART_u8ReceiveData(u8* Copy_u8Data);

u8 USART_u8SendStringSynch(const u8* Copy_pchString);

u8 USART_u8SendStringASynch(const u8* Copy_pchString,void (*Copy_pvNotificFunc)(void));

u8 USART_u8ReceiveBufferSynch(u8* Copy_pchString,u8 Copy_u8BufferSize);

u8 USART_u8ReceiveBufferASynch(u8* Copy_pchString,u8 Copy_u8BufferSize,void (*Copy_pvNotificFunc)(void));

#endif
