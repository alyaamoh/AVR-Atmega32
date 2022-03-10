/*****************************************************************/
/*****************************************************************/
/***************		Author: Alyaa Mohamed	******************/
/***************		Layer: MCAL				******************/
/***************		SWC: TIMER				******************/
/***************		Date: 24-9-2020			******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/

#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_

#define TIMER0_u8PRESCALER        DIVIDE_BY_8
#define TIMER1_u8PRESCALER        DIVIDE_BY_8
#define TIMER2_u8PRESCALER        DIVIDE_BY_8



/*mode:
 * 1-TIMER0_NORMAL_MODE
 * 2-TIMER0_CTC_MODE
 * 3-TIMER0_FAST_PWM_MODE */
#define TIMER0_MODE               TIMER0_FAST_PWM_MODE

#define TIMER0_u8PRELOAD_VAL      192
#define TIMER0_u8COMP_MATCH_VAL   64

#define TIMER1_MODE               TIMER1_NORMAL_MODE

#define TIMER2_MODE               TIMER2_FAST_PWM_MODE

#define TIMER2_u8PRELOAD_VAL      192
#define TIMER2_u8COMP_MATCH_VAL   250

#endif
