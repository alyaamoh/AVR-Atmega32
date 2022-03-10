/*****************************************************************/
/*****************************************************************/
/***************		Author: Alyaa Mohamed	******************/
/***************		Layer: HAL				******************/
/***************		SWC: DIO				******************/
/***************		Date: 25-8-2020			******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/
#include"STD_TYPES.h"
#include<util/delay.h>
#include"DIO_interface.h"
#include"CLCD_config.h"
#include"CLCD_interface.h"
#include"CLCD_private.h"
void CLCD_voidSendCommand(u8 Copy_u8Command){

//set RS to low for command
DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_LOW);

//set RW pin to low for write
DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);

//send the command
DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Command);

//send the enable puls
DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
_delay_ms(2);
DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);

}


void CLCD_voidSendData(u8 Copy_u8Data){

	//set RS high for data
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_HIGH);

	//set RW pin to low for write
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);

	//send the data
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Data);

	//send the enable puls
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);
}

void CLCD_voidInit(void){
//delay more than 30 msec
_delay_ms(40);

//function set for 2 lines & 5*7 size
CLCD_voidSendCommand(0b00111000);

//display on/off control: display on,cursor on, blink on
CLCD_voidSendCommand(0b00001100);

//display clear
CLCD_voidSendCommand(1);

}

void CLCD_voidSendString(const char* Copy_pchString){
	u8 Local_u8counter;
	for(Local_u8counter=0;Copy_pchString[Local_u8counter]!='\0';Copy_pchString++){
			CLCD_voidSendData(Copy_pchString[Local_u8counter]);
		}
}

void CLCD_voidWriteNumber(u32 Copy_u32number){
	u32 Local_resultDiv,Local_numDiv=1000000000;
	u8 i=0;
	if(Copy_u32number==0){
		CLCD_voidSendData('0');
	return;
	}
	do{
		Local_resultDiv=Copy_u32number/Local_numDiv;
		Copy_u32number=Copy_u32number%Local_numDiv;

		if((Local_resultDiv==0)&&(i!=0)){CLCD_voidSendData('0');}

		if((Local_resultDiv!=0)){
			CLCD_voidSendData(Local_resultDiv+'0');
			++i;
		}
		Local_numDiv=Local_numDiv-0.9*Local_numDiv;


	}while(Local_numDiv!= 0);

}

void CLCD_voidGoToXY(u8 Copy_u8XPos,u8 Copy_u8YPos){
	u8 Local_u8DDRAMAddress;
	if(Copy_u8YPos==0){
		Local_u8DDRAMAddress=Copy_u8XPos;
	}
	else if(Copy_u8YPos==1){
		Local_u8DDRAMAddress=0x40+Copy_u8XPos;
	}
	//Local_u8DDRAMAddress=0x40*Copy_u8YPos+Copy_u8XPos;
	//set bit 7 for SetDDRAM address command then send the command
	CLCD_voidSendCommand(Local_u8DDRAMAddress+128);
}

void CLCD_voidWriteSpecialCharacter(u8* Copy_pu8Pattern,u8 Copy_u8PatternNumber,u8 Copy_u8XPos,u8 Copy_u8YPos){
	u8 Local_u8CGRAMAddress,Local_u8Counter;
	/*calculate the CGRAM address knowing that every pattern consume 8 bytes*/
	Local_u8CGRAMAddress=Copy_u8PatternNumber*8;
   /*send CGRAM command to set bit6 and claer bit7*/
	CLCD_voidSendCommand(Local_u8CGRAMAddress+64);
   /*write the pattern into the CGRAM*/
   for(Local_u8Counter=0;Local_u8Counter<8;Local_u8Counter++){
	   CLCD_voidSendData(Copy_pu8Pattern[Local_u8Counter]);
   }
   /*back to DDRAM to display the pattern*/
   CLCD_voidGoToXY(Copy_u8XPos,Copy_u8YPos);
   /*display the required pattern in CGRAM*/
   CLCD_voidSendData(Copy_u8PatternNumber);
}
