/*****************************************************************/
/*****************************************************************/
/***************		Author: Alyaa Mohamed	******************/
/***************		Layer: MCAL				******************/
/***************		SWC: USART   			******************/
/***************		Date: 6-10-2020			******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/

#ifndef USART_PRIVATE_H_
#define USART_PRIVATE_H_

#define CHARSIZE_5BIT  0
#define CHARSIZE_6BIT  1
#define CHARSIZE_7BIT  2
#define CHARSIZE_8BIT  3
#define CHARSIZE_9BIT  7
#define CHARSIZE_MASK  0b11111001

#define ASYNCHRONOUS   0
#define SYNCHRONOUS    1

#define PARITY_DISABLED 0
#define EVEN_PARITY     2
#define ODD_PARITY      3
#define PARITY_MASK     0b11001111

#define STOP_BIT_1      0
#define STOP_BIT_2      1

#define USART_u32TIME_OUT 10000UL

#define ENABLE  1
#define DISABLE 0

#endif
