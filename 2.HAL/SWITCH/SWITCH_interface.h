/*****************************************************************/
/*****************************************************************/
/***************		Author: Alyaa Mohamed	******************/
/***************		Layer: HAL				******************/
/***************		SWC: DIO				******************/
/***************		Date: 1-9-2020			******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/
#ifndef SWITCH_INTERFACE_H_
#define SWITCH_INTERFACE_H_
typedef struct{
	u8 port;
	u8 pin;
}SWITCH_T;

u8 SWITCH_u8Debouncing(SWITCH_t* Copy_Switch);



#endif