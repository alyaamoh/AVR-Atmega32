/*****************************************************************/
/*****************************************************************/
/***************		Author: Alyaa Mohamed	******************/
/***************		Layer: MCAL				******************/
/***************		SWC: SPI    			******************/
/***************		Date: 8-10-2020			******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

#define MASTER  1
#define SLAVE   0

void SPI_voidIntit(u8 Copy_u8Role);

u8 SPI_u8TransceiveSynch(u8 Copy_u8DataSend,u8* Copy_pu8DataReceive);

u8 SPI_u8TransceiveBufferSynch(u8* Copy_pu8DataSendBuffer,u8* Copy_pu8DataReceiveBuffer,u8 Copy_u8BufferSize);

u8 SPI_u8TransceiveBufferASynch(u8* Copy_pu8DataSendBuffer,u8* Copy_pu8DataReceiveBuffer,u8 Copy_u8BufferSize,void (*Copy_pvNotificFunc)(void));


#endif
