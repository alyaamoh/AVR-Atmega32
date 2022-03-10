/*****************************************************************/
/*****************************************************************/
/***************		Author: Alyaa Mohamed	******************/
/***************		Layer: MCAL				******************/
/***************		SWC: SPI    			******************/
/***************		Date: 8-10-2020			******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/

#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_


#define DIVIDE_BY_4      0
#define DIVIDE_BY_16     1
#define DIVIDE_BY_64     2
#define DIVIDE_BY_128    3
#define CLOCK_RATE_MASK  0b11111100

#define MSB              1
#define LSB              0

#define SAMPLE           0
#define SETUP            1

#define LOW_IN_IDLE      0
#define HIGH_IN_IDLE     1

#define SPI_u32TIME_OUT  10000UL


#endif
