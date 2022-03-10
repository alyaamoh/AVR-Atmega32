/*****************************************************************/
/*****************************************************************/
/***************		Author: Alyaa Mohamed	******************/
/***************		Layer: MCAL				******************/
/***************		SWC: TIMER				******************/
/***************		Date: 24-9-2020			******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/
#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

#define FALLING_EDGE 0
#define RISING_EDGE  1


void Timer0_voidInit(void);



u8 Timer0_u8CompmatchSetCallBack(void (*Copy_pvCallBackFunc)(void));



void Timer0_voidCompMatch(u8 Copy_u8Value);


#endif
