/*****************************************************************/
/*****************************************************************/
/***************		Author: Alyaa Mohamed	******************/
/***************		Layer: MCAL				******************/
/***************		SWC: ADC				******************/
/***************		Date: 20-9-2020			******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#define ADC_DIVISION_BY_2    1
#define ADC_DIVISION_BY_4    2
#define ADC_DIVISION_BY_8    3
#define ADC_DIVISION_BY_16   4
#define ADC_DIVISION_BY_32   5
#define ADC_DIVISION_BY_64   6
#define ADC_DIVISION_BY_128  7

#define CHANNEL_MASK         0b11100000
#define PRESCALER_MASK       0b11111000

#define SINGLE_CONVERSION     0
#define CHAIN_CONVERSION      1

#endif
