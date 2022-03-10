/*****************************************************************/
/*****************************************************************/
/***************		Author: Alyaa Mohamed	******************/
/***************		Layer: HAL				******************/
/***************		SWC: LED				******************/
/***************		Date: 6-9-2020			******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/
#include "STD_TYPES.h"
#include "LED_interface.h"
#include "LED_config.h"
#include "DIO_interface.h"

u8 LED_u8LEDON(LED_t* Copy_u8LED){
	u8 Local_u8ErrorState= OK;
		if(Copy_u8LED->LED_PIN <= DIO_u8PIN7)
		{
			if(Copy_u8LED->LED_TYPE==LED_Source)
			    DIO_u8SetPinValue(Copy_u8LED->LED_PORT,Copy_u8LED->LED_PIN,DIO_u8PIN_HIGH);
			else if(Copy_u8LED->LED_TYPE==LED_Sink)
				DIO_u8SetPinValue(Copy_u8LED->LED_PORT,Copy_u8LED->LED_PIN,DIO_u8PIN_LOW);
		}
		else
		{
			Local_u8ErrorState=NOK;
		}
		return Local_u8ErrorState;

}

u8 LED_u8LEDOFF(LED_t* Copy_u8LED){
	u8 Local_u8ErrorState= OK;
			if(Copy_u8LED->LED_PIN <= DIO_u8PIN7)
			{
				if(Copy_u8LED->LED_TYPE==LED_Source)
				    DIO_u8SetPinValue(Copy_u8LED->LED_PORT,Copy_u8LED->LED_PIN,DIO_u8PIN_LOW);
				else if(Copy_u8LED->LED_TYPE==LED_Sink)
					DIO_u8SetPinValue(Copy_u8LED->LED_PORT,Copy_u8LED->LED_PIN,DIO_u8PIN_HIGH);
			}
			else
			{
				Local_u8ErrorState=NOK;
			}
			return Local_u8ErrorState;
}

u8 LED_u8LEDToggle(LED_t* Copy_u8LED){
	u8 Local_u8ErrorState= OK;
				if(Copy_u8LED->LED_PIN <= DIO_u8PIN7)
				{
					DIO_u8TogglePin(Copy_u8LED->LED_PORT,Copy_u8LED->LED_PIN);
				}
				else
				{
					Local_u8ErrorState=NOK;
				}
				return Local_u8ErrorState;

}
