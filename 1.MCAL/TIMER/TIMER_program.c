/*****************************************************************/
/*****************************************************************/
/***************		Author: Alyaa Mohamed	******************/
/***************		Layer: MCAL				******************/
/***************		SWC: TIMER				******************/
/***************		Date: 24-9-2020			******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER_interface.h"
#include "TIMER_register.h"
#include "TIMER_config.h"
#include "TIMER_private.h"

//global pointer to func to hold the call back func address
//timer0
static void (*TIMER0_pvOverFlowCallBackFunc)(void) = NULL;

static void (*TIMER0_pvCompMatchCallBackFunc)(void) = NULL;

//timer2
static void (*TIMER2_pvOverFlowCallBackFunc)(void) = NULL;

static void (*TIMER2_pvCompMatchCallBackFunc)(void) = NULL;

//ICU
static void (*ICU_pvCallBackFunc)(void) = NULL;




void Timer0_voidInit(void){

 #if TIMER0_MODE==TIMER0_NORMAL_MODE
	//initialize waveform generation mode to work as normal mode
	CLR_BIT(TCCR0,TCCR0_WGM00);
	CLR_BIT(TCCR0,TCCR0_WGM01);
	
	//set the required preload
	TCNT0=TIMER0_u8PRELOAD_VAL;

	//timer0 over flow interrupt enable
	SET_BIT(TIMSK,TIMSK_TOIE0);

	//set the req match value
	 OCR0=TIMER0_u8COMP_MATCH_VAL;

	 //set the required prescaler
	 TCCR0 &= TIMER0_PRESCALER_MASK;
	 TCCR0 |= TIMER0_u8PRESCALER;

#elif TIMER0_MODE==TIMER0_CTC_MODE
    	//initialize waveform generation mode to work as CTC mode
		CLR_BIT(TCCR0,TCCR0_WGM00);
		SET_BIT(TCCR0,TCCR0_WGM01);

		//set the req match value
		OCR0=TIMER0_u8COMP_MATCH_VAL;

		//timer0 comp match interrupt enable
		SET_BIT(TIMSK,TIMSK_OCIE0);


    	//set the required prescaler
	    TCCR0 &= TIMER0_PRESCALER_MASK;
	    TCCR0 |= TIMER0_u8PRESCALER;


#elif TIMER0_MODE==TIMER0_FAST_PWM_MODE
	    //initialize waveform generation mode to work as Fast PWM mode
	    SET_BIT(TCCR0,TCCR0_WGM00);
	    SET_BIT(TCCR0,TCCR0_WGM01);


	    //Set on top clear on comp
	    CLR_BIT(TCCR0,TCCR0_COM00);
	    SET_BIT(TCCR0,TCCR0_COM01);

	    //set the req match value
	    OCR0=TIMER0_u8COMP_MATCH_VAL;


	   //set the required prescaler
	   TCCR0 &= TIMER0_PRESCALER_MASK;
	   TCCR0 |= TIMER0_u8PRESCALER;

#else
#error "wrong mode"
#endif
}

u8 Timer0_u8OverFlowSetCallBack(void (*Copy_pvCallBackFunc)(void)){
	u8 Local_u8ErrorState=OK;

	if(Copy_pvCallBackFunc != NULL){
		TIMER0_pvOverFlowCallBackFunc=Copy_pvCallBackFunc;
	}
	else Local_u8ErrorState=NULL_POINTR;
	
	return Local_u8ErrorState;
}


u8 Timer0_u8CompmatchSetCallBack(void (*Copy_pvCallBackFunc)(void)){
	u8 Local_u8ErrorState=OK;

		if(Copy_pvCallBackFunc != NULL){
			TIMER0_pvCompMatchCallBackFunc=Copy_pvCallBackFunc;
		}
		else Local_u8ErrorState=NULL_POINTR;

		return Local_u8ErrorState;
}




void Timer0_voidSetPreload(u8 Copy_u8Preload){
	TCNT0=Copy_u8Preload;
}


void Timer0_voidCompMatchPWM(u8 Copy_u8Value){
	  OCR0=Copy_u8Value;

}

//timer0 ISR over flow mode
void __vector_11(void)  __attribute__((signal));
void __vector_11(void){

	if(TIMER0_pvOverFlowCallBackFunc != NULL){
		TIMER0_pvOverFlowCallBackFunc();
	}
	else {
		//nothing
	}
}


//timer0 ISR CTC mode & Fast PWM mode
void __vector_10(void)  __attribute__((signal));
void __vector_10(void){

	if(TIMER0_pvCompMatchCallBackFunc != NULL){
		TIMER0_pvCompMatchCallBackFunc();
	}
	else {
		//nothing
	}
}








//timer1
void Timer1_voidInit(void){

#if TIMER1_MODE==TIMER1_NORMAL_MODE
	//Waveform Generation Mode work as normal mode
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1B,TCCR1B_WGM12);
	CLR_BIT(TCCR1B,TCCR1B_WGM13);


	//Prescaler divide by 8
	CLR_BIT(TCCR1B,TCCR1B_CS12);
	SET_BIT(TCCR1B,TCCR1B_CS11);
	CLR_BIT(TCCR1B,TCCR1B_CS10);


#elif TIMER1_MODE==TIMER1_FAST_PWM_MODE

	//compare match output mode;set on top , clear on compare
	SET_BIT(TCCR1A,TCCR1A_COM1A1);
	CLR_BIT(TCCR1A,TCCR1A_COM1A0);

	//Waveform Generation Mode work as Fast PWM mode with ICR1 as top value
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);

	//set top value
	ICR1=20000;

	//compare match value:range between 750 to 2500
	OCR1A=750;

	//Prescaler divide by 8
	CLR_BIT(TCCR1B,TCCR1B_CS12);
	SET_BIT(TCCR1B,TCCR1B_CS11);
	CLR_BIT(TCCR1B,TCCR1B_CS10);

#else
#error "wrong mode"
#endif

}


void Timer1_voidSetChannelACompValue(u16 Copy_u8Value){

	OCR1A= Copy_u8Value;
}

void Timer1_voidSetPreloadValue(u16 Copy_u16Value){
TCNT1=Copy_u16Value;
}

u16 Timer1_u16ReadTimer1Value(void){
	return TCNT1;
}







//ICU in Timer1

void ICU_voidInit(void){
	//set trigger to rising edge initially
	SET_BIT(TCCR1B,TCCR1B_ICES1);

	//enable the ICU interrupt
	SET_BIT(TIMSK,TIMSK_TICIE1);
}

u8 ICU_u8SetCallBack(void (*Copy_pvCallBackFunc)(void)){
	u8 Local_u8ErrorState=OK;

	if(Copy_pvCallBackFunc != NULL){
		ICU_pvCallBackFunc = Copy_pvCallBackFunc;
	}
	else Local_u8ErrorState=NOK;
	return Local_u8ErrorState;
}

u8 ICU_u8SetTrigger(u8 Copy_u8TriggerSource){
	u8 Local_u8ErrorState=OK;
	switch(Copy_u8TriggerSource){
	case FALLING_EDGE: CLR_BIT(TCCR1B,TCCR1B_ICES1); break;
	case RISING_EDGE:  SET_BIT(TCCR1B,TCCR1B_ICES1); break;
	default: Local_u8ErrorState=NOK; break;

	}
	return Local_u8ErrorState;

}

u16 ICU_u16ReadInputCapture(void){
	return ICR1;
}

void ICU_voidInterruptDisable(void){
CLR_BIT(TIMSK,TIMSK_TICIE1);
}


void __vector_6(void) __attribute((signal));
void __vector_6(void){
	if(ICU_pvCallBackFunc != NULL){
		ICU_pvCallBackFunc();
	}
	else{
		//nothing
	}
}










//timer2
void Timer2_voidInit(void){
#if TIMER2_MODE==TIMER2_NORMAL_MODE
	//initialize waveform generation mode to work as normal mode
	CLR_BIT(TCCR2,TCCR2_WGM00);
	CLR_BIT(TCCR2,TCCR2_WGM01);

	//set the required preload
	TCNT2=TIMER0_u8PRELOAD_VAL;

	//timer0 over flow interrupt enable
	SET_BIT(TIMSK,TIMSK_TOIE0);

	//set the req match value
	 OCR2=TIMER0_u8COMP_MATCH_VAL;

	 //set the required prescaler
	 TCCR2 &= TIMER2_PRESCALER_MASK;
	 TCCR2 |= TIMER02_u8PRESCALER;

#elif TIMER2_MODE==TIMER2_CTC_MODE
   	//initialize waveform generation mode to work as CTC mode
		CLR_BIT(TCCR2,TCCR0_WGM00);
		SET_BIT(TCCR2,TCCR0_WGM01);

		//set the req match value
		OCR2=TIMER2_u8COMP_MATCH_VAL;

		//timer0 comp match interrupt enable
		SET_BIT(TIMSK,TIMSK_OCIE0);


   	//set the required prescaler
	    TCCR2 &= TIMER2_PRESCALER_MASK;
	    TCCR2 |= TIMER2_u8PRESCALER;


#elif TIMER2_MODE==TIMER2_FAST_PWM_MODE
	    //initialize waveform generation mode to work as Fast PWM mode
	    SET_BIT(TCCR2,TCCR0_WGM00);
	    SET_BIT(TCCR2,TCCR0_WGM01);

	    //set the req match value
	  //  OCR0=TIMER0_u8COMP_MATCH_VAL;

	    //Set OC0 on compare match, clear OC0 at TOP
	    SET_BIT(TCCR2,TCCR0_COM00);
	    SET_BIT(TCCR2,TCCR0_COM01);

	    //timer0 comp match interrupt enable
	    SET_BIT(TIMSK,TIMSK_OCIE0);


	   //set the required prescaler
	   TCCR2 &= TIMER0_PRESCALER_MASK;
	   TCCR2 |= TIMER0_u8PRESCALER;

#else
#error "wrong mode"
#endif
}

u8 Timer2_u8OverFlowSetCallBack(void (*Copy_pvCallBackFunc)(void)){
	u8 Local_u8ErrorState=OK;

		if(Copy_pvCallBackFunc != NULL){
			TIMER2_pvOverFlowCallBackFunc=Copy_pvCallBackFunc;
		}
		else Local_u8ErrorState=NULL_POINTR;

		return Local_u8ErrorState;
}

u8 Timer2_u8CompmatchSetCallBack(void (*Copy_pvCallBackFunc)(void)){
	u8 Local_u8ErrorState=OK;

			if(Copy_pvCallBackFunc != NULL){
				TIMER2_pvCompMatchCallBackFunc=Copy_pvCallBackFunc;
			}
			else Local_u8ErrorState=NULL_POINTR;

			return Local_u8ErrorState;
}


void Timer2_voidSetPreload(u8 Copy_u8Preload){
	TCNT2=Copy_u8Preload;
}

void Timer2_voidCompMatchPWM(u8 Copy_u8Value){
	 OCR2=Copy_u8Value;
}

//timer0 ISR over flow mode
void __vector_5(void)  __attribute__((signal));
void __vector_5(void){

	if(TIMER2_pvOverFlowCallBackFunc != NULL){
		TIMER2_pvOverFlowCallBackFunc();
	}
	else {
		//nothing
	}
}


//timer0 ISR CTC mode & Fast PWM mode
void __vector_4(void)  __attribute__((signal));
void __vector_4(void){

	if(TIMER2_pvCompMatchCallBackFunc != NULL){
		TIMER2_pvCompMatchCallBackFunc();
	}
	else {
		//nothing
	}
}
