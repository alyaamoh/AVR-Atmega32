/*****************************************************************/
/*****************************************************************/
/***************		Author: Alyaa Mohamed	******************/
/***************		Layer: HAL				******************/
/***************		SWC: KPD				******************/
/***************		Date: 1-9-2020			******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/
#include "STD_TYPES.h"

#include "DIO_interface.h"

#include "KPD_config.h"
#include "KPD_interface.h"
#include "KPD_private.h"

u8 KPD_u8GetPressedKey(void){

	u8 Local_u8ColIdx, Local_u8RowIdx, Local_u8KeyPressed=NO_PRESSED_KEY, Local_u8PinState;
	u8 Local_KPDARR[ROW_NUMBER][COLUMN_NUMBER]=KPD_BUTTONS_VAL;
	u8 Local_u8ColArr[COLUMN_NUMBER]={COLUMN_PIN0,COLUMN_PIN1,COLUMN_PIN2,COLUMN_PIN3};
	u8 Local_u8RowArr[ROW_NUMBER]={ROW_PIN0,ROW_PIN1,ROW_PIN2,ROW_PIN3};

	for(Local_u8ColIdx=0;Local_u8ColIdx<COLUMN_NUMBER;Local_u8ColIdx++)
	{
		//activate the current column
		DIO_u8SetPinValue(KPD_PORT,Local_u8ColArr[Local_u8ColIdx],DIO_u8PIN_LOW);
		for(Local_u8RowIdx=0;Local_u8RowIdx<ROW_NUMBER;Local_u8RowIdx++)
		{
			//read the current row
			DIO_u8GetPinValue(KPD_PORT,Local_u8RowArr[Local_u8RowIdx],&Local_u8PinState);
			if(Local_u8PinState==DIO_u8PIN_LOW)
			{
				Local_u8KeyPressed=Local_KPDARR[Local_u8RowIdx][Local_u8ColIdx];

				//wait (polling and blocking) until the released the key
				while(Local_u8PinState==DIO_u8PIN_LOW){
					DIO_u8GetPinValue(KPD_PORT,Local_u8RowArr[Local_u8RowIdx],&Local_u8PinState);
				}

				return Local_u8KeyPressed;
			}
		}

		//deactivate the current column
		DIO_u8SetPinValue(KPD_PORT,Local_u8ColArr[Local_u8ColIdx],DIO_u8PIN_HIGH);

	}

return Local_u8KeyPressed;
}
