/*****************************************************************/
/*****************************************************************/
/***************		Author: Alyaa Mohamed	******************/
/***************		Layer: HAL				******************/
/***************		SWC: MOTOR				******************/
/***************		Date: 3-9-2020			******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/
#include "STD_TYPES.h"
#include "PORT_interface.h"
#include "DIO_interface.h"
#include "MOTOR_interface.h"
#include "MOTOR_config.h"
#include "MOTOR_private.h"

void MOTOR_voidRCW(void){
	DIO_u8SetPinValue(MOTOR_PORT,MOTOR_PINB,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(MOTOR_PORT,MOTOR_PINA,DIO_u8PIN_HIGH);
}
void MOTOR_voidRCCW(void){
	DIO_u8SetPinValue(MOTOR_PORT,MOTOR_PINA,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(MOTOR_PORT,MOTOR_PINB,DIO_u8PIN_HIGH);
}
void MOTOR_voidStop(void){
	DIO_u8SetPinValue(MOTOR_PORT,MOTOR_PINB,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(MOTOR_PORT,MOTOR_PINA,DIO_u8PIN_LOW);

}
