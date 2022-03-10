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

u8 Timer0_u8OverFlowSetCallBack(void (*Copy_pvCallBackFunc)(void));

u8 Timer0_u8CompmatchSetCallBack(void (*Copy_pvCallBackFunc)(void));

void Timer0_voidSetPreload(u8 Copy_u8Preload);

void Timer0_voidCompMatchPWM(u8 Copy_u8Value);






void Timer1_voidInit(void);

void Timer1_voidSetChannelACompValue(u16 Copy_u8Value);

void Timer1_voidSetPreloadValue(u16 Copy_u16Value);

u16 Timer1_u16ReadTimer1Value(void);


void ICU_voidInit(void);

u8 ICU_u8SetCallBack(void (*Copy_pvCallBackFunc)(void));

u8 ICU_u8SetTrigger(u8 Copy_u8TriggerSource);

u16 ICU_u16ReadInputCapture(void);

void ICU_voidInterruptDisable(void);





void Timer2_voidInit(void);

u8 Timer2_u8OverFlowSetCallBack(void (*Copy_pvCallBackFunc)(void));

u8 Timer2_u8CompmatchSetCallBack(void (*Copy_pvCallBackFunc)(void));


void Timer2_voidSetPreload(u8 Copy_u8Preload);

void Timer2_voidCompMatchPWM(u8 Copy_u8Value);

#endif
