/*****************************************************************/
/*****************************************************************/
/***************		Author: Alyaa Mohamed	******************/
/***************		Layer: MCAL				******************/
/***************		SWC: EXTI   			******************/
/***************		Date: 14-9-2020			******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/
#ifndef EXIT_INTERFACE_H_
#define EXIT_INTERFACE_H_

#define LOW_LEVEL    1
#define ON_CHANGE    2
#define FALLING_EDGE 3
#define RISING_EDGE  4

#define EXTI_INT0    0
#define EXTI_INT1    1
#define EXTI_INT2    2

void EXTI_voidInT0Init(void);
void EXTI_voidInT1Init(void);
void EXTI_voidInT2Init(void);

//description: change sense control of the require interrupt
//input: 1-Copy_u8IntNumber: the required interrupt number to change sense control
//options: 1-EXTI_INT0 2-EXTI_INT1 3-EXTI_INT2
//2-Copy_u8sense:the required sense control for the EXTI
//options: 1-LOW_LEVEL 2-ON_CHANGE 3-FALLING_EDGE 4-RISING_EDGE
//output:Error State
//options: 1-OK 2-NOK
u8 EXTI_u8SetSenseControl(u8 Copy_u8IntNumber,u8 Copy_u8Sense);

u8 EXTI_u8EnableInterrupt(u8 Copy_u8IntNumber);
u8 EXTI_u8DisableInterrupt(u8 Copy_u8IntNumber);

u8 EXTI_u8INTSetCallBack(void (*Copy_pvCallBackFunc(void)),u8 Copy_u8IntNumber);

#endif
