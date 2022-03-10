/*****************************************************************/
/*****************************************************************/
/***************		Author: Alyaa Mohamed	******************/
/***************		Layer: MCAL				******************/
/***************		SWC: TIMER				******************/
/***************		Date: 24-9-2020			******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/

#ifndef TIMER_REGISTER_H_
#define TIMER_REGISTER_H_

#define  TIMSK         *((volatile u8*)0x59)    //timer mask register
#define  TIMSK_TOIE0   0                        //timer overflow interrupt enable
#define  TIMSK_OCIE0   1                        //timer compare match enable
#define  TIMSK_OCIE1A  4
#define  TIMSK_OCIE1B  3
#define  TIMSK_TICIE1  5

//timer0
#define  OCR0          *((volatile u8*)0x5c)    //output compare match register

#define  TCCR0         *((volatile u8*)0x53)    //timer counter control register 0
#define  TCCR0_WGM00   6                        //waveform generation mode bit 0
#define  TCCR0_WGM01   3                        //waveform generation mode bit 1
#define  TCCR0_COM00   4
#define  TCCR0_COM01   5


#define  TCNT0         *((volatile u8*)0x52)    //timer counter 0 register


//timer1
#define  OCR1A           *((volatile u16*)0x4A)

#define  ICR1            *((volatile u16*)0x46)

#define  OCR1B           *((volatile u16*)0x48)

#define  TCCR1A          *((volatile u8*)0x4F)    //timer counter control register 2
#define  TCCR1A_WGM10    0                        //waveform generation mode bit 0
#define  TCCR1A_WGM11    1                        //waveform generation mode bit 1
#define  TCCR1A_COM1A1   7
#define  TCCR1A_COM1A0   6
#define  TCCR1A_COM1B1   5
#define  TCCR1A_COM1B0   4

#define  TCCR1B          *((volatile u8*)0x4E)
#define  TCCR1B_WGM13    4                        //waveform generation mode bit 0
#define  TCCR1B_WGM12    3                        //waveform generation mode bit 1
#define  TCCR1B_ICNC1    7
#define  TCCR1B_CS10     0
#define  TCCR1B_CS11     1
#define  TCCR1B_CS12     2
#define  TCCR1B_ICES1    6

#define  TCNT1           *((volatile u16*)0x4C)


//timer2
#define  OCR2          *((volatile u8*)0x43)

#define  TCCR2         *((volatile u8*)0x45)    //timer counter control register 2
#define  TCCR2_WGM00   6                        //waveform generation mode bit 0
#define  TCCR2_WGM01   3                        //waveform generation mode bit 1
#define  TCCR2_COM00   4
#define  TCCR2_COM01   5

#define  TCNT2         *((volatile u8*)0x44)


#endif
