/*****************************************************************/
/*****************************************************************/
/***************		Author: Alyaa Mohamed	******************/
/***************		Layer: HAL				******************/
/***************		SWC: SSD				******************/
/***************		Date: 6-9-2020			******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/
#include"STD_TYPES.h"
#include"DIO_interface.h"
#include"SSD_config.h"
#include"SSD_interface.h"

void SSD_u8SSDON(SSD_T* CopySSD){
	if(CopySSD->SSD_TYPE==SSD_CATHODE)
	DIO_u8SetPinValue(CopySSD->SSD_EnablePort,CopySSD->SSD_EnablePin,DIO_u8PIN_LOW);
else if(CopySSD->SSD_TYPE==SSD_ANODE)
		DIO_u8SetPinValue(CopySSD->SSD_EnablePort,CopySSD->SSD_EnablePin,DIO_u8PIN_HIGH);
}

void SSD_u8SSDOFF(SSD_T* CopySSD){
	if(CopySSD->SSD_TYPE==SSD_CATHODE)
	DIO_u8SetPinValue(CopySSD->SSD_EnablePort,CopySSD->SSD_EnablePin,DIO_u8PIN_HIGH);
else if(CopySSD->SSD_TYPE==SSD_ANODE)
		DIO_u8SetPinValue(CopySSD->SSD_EnablePort,CopySSD->SSD_EnablePin,DIO_u8PIN_LOW);
}


void SSD_u8SSDSetNumber(SSD_T* CopySSD,u8 Copy_u8Number){
static	u8 SSDArr[10]={0b00111111,0b00000110,0b01011011,0b01001111,0b01100110,0b01101101,0b01111101,0b00000111,0b01111111,0b01101111};

if(CopySSD->SSD_TYPE==SSD_CATHODE)
	DIO_u8SetPortValue(CopySSD->SSD_PORT,SSDArr[Copy_u8Number]);
else if(CopySSD->SSD_TYPE==SSD_ANODE)
	DIO_u8SetPortValue(CopySSD->SSD_PORT,~SSDArr[Copy_u8Number]);

}
