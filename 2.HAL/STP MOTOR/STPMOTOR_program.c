/*****************************************************************/
/*****************************************************************/
/***************		Author: Alyaa Mohamed	******************/
/***************		Layer: HAL				******************/
/***************		SWC: STP MOTOR			******************/
/***************		Date: 13-9-2020			******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/

#include <util\delay.h>
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "STPMOTOR_config.h"
#include "STPMOTOR_interface.h"
#include "STPMOTOR_private.h"

void STPMOTOR_voidSetAngel(u16 Copy_u16Angel){
	u16  Local_u16Steps,Local_u16Counter;

		Local_u16Steps=(2048UL*(u32)Copy_u16Angel)/360UL;
		for(Local_u16Counter=0;Local_u16Counter<Local_u16Steps;Local_u16Counter++){
			if(Local_u16Counter%4==0){
				DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN0,DIO_u8PIN_LOW);
				DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN1,DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN2,DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN3,DIO_u8PIN_HIGH);
				_delay_ms(2);
			}
			else if(Local_u16Counter%4==1){
				DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN0,DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN1,DIO_u8PIN_LOW);
				DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN2,DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN3,DIO_u8PIN_HIGH);
				_delay_ms(2);
			}
			else if(Local_u16Counter%4==2){
				DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN0,DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN1,DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN2,DIO_u8PIN_LOW);
				DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN3,DIO_u8PIN_HIGH);
				_delay_ms(2);
			}
			else{
				DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN0,DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN1,DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN2,DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN3,DIO_u8PIN_LOW);
				_delay_ms(2);
			}

		}
}

void STPMOTOR_voidRCW(void){
	DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN0,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN1,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN2,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN3,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN0,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN1,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN2,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN3,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN0,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN1,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN2,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN3,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN0,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN1,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN2,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN3,DIO_u8PIN_LOW);
	_delay_ms(2);

}
void STPMOTOR_voidRCCW(void){
	    DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN0,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN1,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN2,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN3,DIO_u8PIN_LOW);
		_delay_ms(2);
		DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN0,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN1,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN2,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN3,DIO_u8PIN_HIGH);
		_delay_ms(2);
		DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN0,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN1,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN2,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN3,DIO_u8PIN_HIGH);
		_delay_ms(2);
		DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN0,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN1,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN2,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STPMOTOR_PORT,STPMOTOR_PIN3,DIO_u8PIN_HIGH);
		_delay_ms(2);
}
