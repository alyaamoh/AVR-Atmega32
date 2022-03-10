/*****************************************************************/
/*****************************************************************/
/***************		Author: Alyaa Mohamed	******************/
/***************		Layer: MCAL				******************/
/***************		SWC: EXTI   			******************/
/***************		Date: 15-9-2020			******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/
#ifndef EXTI_CONFIG_H_
#define EXTI_CONFIG_H_

//interrupt trigger. Options: 1-LOW_LEVEL  2-ON_CHANGE 3-FALLING_EDGE 4-RISING_EDGE
#define EXTI_INT0_SENSE        RISING_EDGE
#define EXTI_INT1_SENSE        FALLING_EDGE
#define EXTI_INT2_SENSE        FALLING_EDGE

//enable initial state. 1-ENABLED  2-DISABLED
#define EXTI_INT0_INTIAL_STATE  ENABLED
#define EXTI_INT1_INTIAL_STATE  ENABLED
#define EXTI_INT2_INTIAL_STATE  ENABLED

#endif
